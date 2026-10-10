#!/usr/bin/env python3
"""Extract, edit, and compare exact 24x24 Corne OLED host icons."""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
from copy import deepcopy
from pathlib import Path
from typing import Any

try:
    from PIL import Image, ImageDraw, ImageFont, ImageOps
except ImportError:
    Image = ImageDraw = ImageFont = ImageOps = None

OLED_DIR = Path(__file__).resolve().parent
KEYMAP_DIR = OLED_DIR.parent
REPO_ROOT = KEYMAP_DIR.parents[3]
ICONS_PATH = OLED_DIR / "icons.json"
ICON_SHEET_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_os_icons.png"
COMPARISON_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_os_icon_workbench.png"
SWEEP_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_os_icon_thresholds.png"
ICON_ORDER = ("linux", "windows", "macos")
DISPLAY_NAMES = {"linux": "LINUX", "windows": "WINDOWS", "macos": "MACOS"}


def require_pillow() -> None:
    if Image is None:
        raise RuntimeError("icon workbench needs Pillow: python3 -m pip install Pillow")


def load_icons() -> dict[str, Any]:
    return json.loads(ICONS_PATH.read_text(encoding="utf-8"))


def validate_rows(rows: list[str], width: int, height: int, name: str) -> None:
    if len(rows) != height:
        raise ValueError(f"{name} has {len(rows)} rows; expected {height}")
    for row_number, row in enumerate(rows):
        if len(row) != width:
            raise ValueError(f"{name} row {row_number} is {len(row)} pixels wide; expected {width}")
        invalid = set(row) - {".", "#"}
        if invalid:
            raise ValueError(f"{name} row {row_number} contains invalid pixels: {sorted(invalid)}")


def validate_icons(data: dict[str, Any]) -> None:
    width = data["grid"]["width"]
    height = data["grid"]["height"]
    if (width, height) != (24, 24):
        raise ValueError("host icon grid must remain 24 by 24 pixels")
    if tuple(data["icons"]) != ICON_ORDER:
        raise ValueError(f"icons must be defined in this order: {ICON_ORDER}")
    for name, icon in data["icons"].items():
        validate_rows(icon["rows"], width, height, name)


def resolve_reference(data: dict[str, Any], override: str | None) -> Path:
    path = Path(override) if override else Path(data["reference"]["path"])
    if not path.is_absolute():
        path = REPO_ROOT / path
    if not path.is_file():
        raise ValueError(f"reference image not found: {path}")
    if override is None and data["reference"].get("sha256"):
        digest = hashlib.sha256(path.read_bytes()).hexdigest()
        if digest != data["reference"]["sha256"]:
            raise ValueError(f"reference checksum changed: {path}")
    return path


def foreground_mask(image: "Image.Image", threshold: int) -> "Image.Image":
    rgb = image.convert("RGB")
    return rgb.point(lambda value: 255 if value >= threshold else 0).convert("L").point(
        lambda value: 255 if value else 0
    )


def fitted_size(width: int, height: int, max_width: int, max_height: int) -> tuple[int, int]:
    scale = min(max_width / width, max_height / height)
    return max(1, round(width * scale)), max(1, round(height * scale))


def extract_icon(reference: "Image.Image", icon: dict[str, Any], grid: dict[str, int], threshold: float | None = None) -> tuple[list[str], "Image.Image"]:
    crop = reference.crop(tuple(icon["crop"]))
    mask = foreground_mask(crop, icon["foreground_threshold"])
    bounds = mask.getbbox()
    if not bounds:
        raise ValueError(f"no foreground pixels found in crop {icon['crop']}")
    mask = mask.crop(bounds)
    target_width, target_height = fitted_size(
        mask.width,
        mask.height,
        icon["max_width"],
        icon["max_height"],
    )
    reduced = mask.resize((target_width, target_height), Image.Resampling.LANCZOS)
    cutoff = round(255 * (icon["threshold"] if threshold is None else threshold))
    reduced = reduced.point(lambda value: 255 if value >= cutoff else 0, mode="1")

    canvas = Image.new("1", (grid["width"], grid["height"]), 0)
    x = (grid["width"] - target_width) // 2 + icon.get("offset_x", 0)
    y = (grid["height"] - target_height) // 2 + icon.get("offset_y", 0)
    canvas.paste(reduced, (x, y))
    rows = [
        "".join("#" if canvas.getpixel((column, row)) else "." for column in range(grid["width"]))
        for row in range(grid["height"])
    ]
    return rows, crop


def rows_to_image(rows: list[str]) -> "Image.Image":
    canvas = Image.new("1", (len(rows[0]), len(rows)), 0)
    for y, row in enumerate(rows):
        for x, pixel in enumerate(row):
            if pixel == "#":
                canvas.putpixel((x, y), 1)
    return canvas


def colorize(image: "Image.Image", scale: int) -> "Image.Image":
    enlarged = image.resize((image.width * scale, image.height * scale), Image.Resampling.NEAREST)
    colored = Image.new("RGB", enlarged.size, "#050908")
    colored.paste(Image.new("RGB", enlarged.size, "#9fffd5"), mask=enlarged)
    return colored


def centered_label(draw: "ImageDraw.ImageDraw", text: str, center_x: int, y: int, font: "ImageFont.ImageFont") -> None:
    box = draw.textbbox((0, 0), text, font=font)
    draw.text((center_x - (box[2] - box[0]) / 2, y), text, fill="#d9ddd9", font=font)


def render_icon_sheet(data: dict[str, Any], path: Path = ICON_SHEET_PATH) -> None:
    scale = 14
    padding = 28
    label_height = 28
    grid = data["grid"]
    cell_width = grid["width"] * scale + 2 * padding
    cell_height = grid["height"] * scale + 2 * padding + label_height
    sheet = Image.new("RGB", (cell_width * len(ICON_ORDER), cell_height), "#111613")
    draw = ImageDraw.Draw(sheet)
    font = ImageFont.load_default(size=15)
    for index, name in enumerate(ICON_ORDER):
        x = index * cell_width + padding
        y = padding + label_height
        centered_label(draw, DISPLAY_NAMES[name], index * cell_width + cell_width // 2, padding, font)
        sheet.paste(colorize(rows_to_image(data["icons"][name]["rows"]), scale), (x, y))
    path.parent.mkdir(parents=True, exist_ok=True)
    sheet.save(path)
    print(f"wrote {path.relative_to(REPO_ROOT)}")


def reference_panel(crop: "Image.Image", size: int) -> "Image.Image":
    panel = Image.new("RGB", (size, size), "#050908")
    contained = ImageOps.contain(crop.convert("RGB"), (size, size), Image.Resampling.LANCZOS)
    panel.paste(contained, ((size - contained.width) // 2, (size - contained.height) // 2))
    return panel


def render_comparison(data: dict[str, Any], reference: "Image.Image", path: Path = COMPARISON_PATH) -> None:
    tile = 288
    gap = 14
    label_height = 28
    width = tile * 2 + gap
    height = len(ICON_ORDER) * (tile + label_height + gap) - gap
    sheet = Image.new("RGB", (width, height), "#111613")
    draw = ImageDraw.Draw(sheet)
    font = ImageFont.load_default(size=15)
    for index, name in enumerate(ICON_ORDER):
        y = index * (tile + label_height + gap)
        centered_label(draw, f"{DISPLAY_NAMES[name]} REFERENCE", tile // 2, y, font)
        centered_label(draw, f"{DISPLAY_NAMES[name]} EXACT 24x24", tile + gap + tile // 2, y, font)
        crop = reference.crop(tuple(data["icons"][name]["crop"]))
        sheet.paste(reference_panel(crop, tile), (0, y + label_height))
        sheet.paste(colorize(rows_to_image(data["icons"][name]["rows"]), tile // 24), (tile + gap, y + label_height))
    path.parent.mkdir(parents=True, exist_ok=True)
    sheet.save(path)
    print(f"wrote {path.relative_to(REPO_ROOT)}")


def render_sweep(data: dict[str, Any], reference: "Image.Image", path: Path = SWEEP_PATH) -> None:
    thresholds = (0.30, 0.38, 0.46, 0.54, 0.62)
    scale = 10
    padding = 18
    label_height = 25
    icon_size = data["grid"]["width"] * scale
    cell_width = icon_size + 2 * padding
    cell_height = icon_size + 2 * padding + label_height
    sheet = Image.new("RGB", (cell_width * len(thresholds), cell_height * len(ICON_ORDER)), "#111613")
    draw = ImageDraw.Draw(sheet)
    font = ImageFont.load_default(size=14)
    for row, name in enumerate(ICON_ORDER):
        for column, threshold in enumerate(thresholds):
            rows, _ = extract_icon(reference, data["icons"][name], data["grid"], threshold)
            x = column * cell_width + padding
            y = row * cell_height + padding + label_height
            centered_label(
                draw,
                f"{DISPLAY_NAMES[name]} {threshold:.2f}",
                column * cell_width + cell_width // 2,
                row * cell_height + padding,
                font,
            )
            sheet.paste(colorize(rows_to_image(rows), scale), (x, y))
    path.parent.mkdir(parents=True, exist_ok=True)
    sheet.save(path)
    print(f"wrote {path.relative_to(REPO_ROOT)}")


def write_icons(data: dict[str, Any]) -> None:
    ICONS_PATH.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {ICONS_PATH.relative_to(REPO_ROOT)}")


def command_extract(data: dict[str, Any], args: argparse.Namespace) -> None:
    reference_path = resolve_reference(data, args.reference)
    reference = Image.open(reference_path)
    updated = deepcopy(data)
    names = ICON_ORDER if args.icon == "all" else (args.icon,)
    for name in names:
        rows, _ = extract_icon(reference, updated["icons"][name], updated["grid"], args.threshold)
        updated["icons"][name]["rows"] = rows
        if args.threshold is not None:
            updated["icons"][name]["threshold"] = args.threshold
    validate_icons(updated)
    render_sweep(updated, reference)
    render_icon_sheet(updated)
    render_comparison(updated, reference)
    if args.write:
        write_icons(updated)
    else:
        print("preview only; pass --write to make these grids authoritative")


def command_render(data: dict[str, Any], args: argparse.Namespace) -> None:
    validate_icons(data)
    render_icon_sheet(data)
    configured_path = Path(args.reference) if args.reference else Path(data["reference"]["path"])
    if not configured_path.is_absolute():
        configured_path = REPO_ROOT / configured_path
    if not configured_path.is_file() and args.reference is None:
        print(f"reference unavailable; skipped comparison outputs: {configured_path}")
        return
    reference = Image.open(resolve_reference(data, args.reference))
    render_comparison(data, reference)
    render_sweep(data, reference)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    render_parser = subparsers.add_parser("render", help="render authoritative icons and reference comparisons")
    render_parser.add_argument("--reference", help="override the configured reference image")
    extract_parser = subparsers.add_parser("extract", help="extract candidate grids from the selected reference")
    extract_parser.add_argument("--reference", help="override the configured reference image")
    extract_parser.add_argument("--icon", choices=("all",) + ICON_ORDER, default="all")
    extract_parser.add_argument("--threshold", type=float, help="override the configured 0..1 coverage threshold")
    extract_parser.add_argument("--write", action="store_true", help="replace authoritative rows in icons.json")
    args = parser.parse_args()

    try:
        require_pillow()
        data = load_icons()
        if args.command == "extract":
            command_extract(data, args)
        else:
            command_render(data, args)
    except (KeyError, OSError, TypeError, ValueError, RuntimeError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
