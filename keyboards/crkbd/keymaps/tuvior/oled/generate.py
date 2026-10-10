#!/usr/bin/env python3
"""Generate Corne OLED firmware assets and exact paired-screen previews."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import re
import sys
from io import BytesIO
from pathlib import Path
from typing import Any

try:
    from PIL import Image, ImageDraw, ImageFont
except ImportError:  # Preview generation is optional for firmware checks.
    Image = ImageDraw = ImageFont = None

OLED_DIR = Path(__file__).resolve().parent
KEYMAP_DIR = OLED_DIR.parent
REPO_ROOT = KEYMAP_DIR.parents[3]
LAYOUT_PATH = OLED_DIR / "layout.json"
ICONS_PATH = OLED_DIR / "icons.json"
HEADER_PATH = OLED_DIR / "layout.generated.h"
PREVIEW_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_preview.png"
STATE_MATRIX_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_state_matrix.png"
MODIFIER_MATRIX_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_modifier_matrix.png"
PERFORMANCE_MATRIX_PATH = REPO_ROOT / ".build" / "crkbd_tuvior_oled_performance_matrix.png"
FONT_PATH = KEYMAP_DIR / "glcdfont.c"

STATE_ORDER = ("off_off", "on_off", "off_on", "on_on")

MICRO_FONT = {
    "A": (".#.", "#.#", "###", "#.#", "#.#"),
    "B": ("##.", "#.#", "##.", "#.#", "##."),
    "C": (".##", "#..", "#..", "#..", ".##"),
    "D": ("##.", "#.#", "#.#", "#.#", "##."),
    "E": ("###", "#..", "##.", "#..", "###"),
    "I": ("###", ".#.", ".#.", ".#.", "###"),
    "J": ("..#", "..#", "..#", "#.#", ".#."),
    "K": ("#.#", "#.#", "##.", "#.#", "#.#"),
    "L": ("#..", "#..", "#..", "#..", "###"),
    "M": ("#.#", "###", "###", "#.#", "#.#"),
    "O": (".#.", "#.#", "#.#", "#.#", ".#."),
    "P": ("##.", "#.#", "##.", "#..", "#.."),
    "Q": (".#.", "#.#", "#.#", ".##", "..#"),
    "R": ("##.", "#.#", "##.", "#.#", "#.#"),
    "S": (".##", "#..", ".#.", "..#", "##."),
    "T": ("###", ".#.", ".#.", ".#.", ".#."),
    "U": ("#.#", "#.#", "#.#", "#.#", ".#."),
    "W": ("#.#", "#.#", "###", "###", "#.#"),
    "X": ("#.#", "#.#", ".#.", "#.#", "#.#"),
    "Y": ("#.#", "#.#", ".#.", ".#.", ".#."),
}

ORIGINAL_ASSET_HASHES = {
    "corne_logo": "39e449d14c6b7ab327f50a040b35663a706baf0855fc4a7cfaf90f3cae903318",
    "layer/default": "3239c700bdcbe4cd84123dc18f354b74c5b82f724a0304d895752571e68ea62f",
    "layer/raise": "6f10ef9c587fce18e1c9ad2025f93de5fcc53d70c22ffb684ab02138a79b6875",
    "layer/lower": "8d6f32e256f2b4c0de2f68a2a71081bc296796fa04c19e4fbdb8f0179534ec96",
    "layer/adjust": "2336bdd76f9d88c6010c029fbc4bdde7494114994b20872af4fcebefae3d2d44",
    "gui_alt/off_off": "ea44c22d7c761c46a178b2cfe1c7a635d2f0830cbbc981fc677c5ec56e8364cc",
    "gui_alt/on_off": "d0650c2cca5c53d36aff537578851bc7816247564f95c9dd51fa7095805cc063",
    "gui_alt/off_on": "647b99b57ec0fb7b32a96bd95e845f6a078c59c91c926434e6740b6825733e58",
    "gui_alt/on_on": "ede349a9884ef20e7d30c514fe014968371008737e8aeed3c74d5771360ae2c1",
    "ctrl_shift/off_off": "ca8189a3f994b347a9ccf9b24032d2ed131ea8760cdcb300ae9f53dfbcb25a36",
    "ctrl_shift/on_off": "6ff3f6fefa63c3dc4481752c8ee8ed730966ce6054009dc4c6a6709f9605c788",
    "ctrl_shift/off_on": "1add103e2d16baefae2b35e35f23d321b441fb621c0171f613231a8e1e26d16a",
    "ctrl_shift/on_on": "5b775f755e66049f361773d3f4b9c29d894b1aa57e98f7c8257e1005a9e55459",
}


def load_layout() -> dict[str, Any]:
    layout = json.loads(LAYOUT_PATH.read_text(encoding="utf-8"))
    icon_data = json.loads(ICONS_PATH.read_text(encoding="utf-8"))
    grid = icon_data["grid"]
    display_width = layout["display"]["pixel_width"]
    if (grid["width"], grid["height"]) != (24, 24):
        raise ValueError("host icons must use the 24 by 24 workbench grid")
    if tuple(icon_data["icons"]) != ("linux", "windows", "macos"):
        raise ValueError("host icons must be ordered linux, windows, macos")
    horizontal_padding = (display_width - grid["width"]) // 2
    if horizontal_padding < 0 or horizontal_padding * 2 + grid["width"] != display_width:
        raise ValueError("host icon grid must center exactly on the OLED width")
    for name, icon in icon_data["icons"].items():
        rows = icon["rows"]
        if len(rows) != grid["height"]:
            raise ValueError(f"host icon {name} must have exactly {grid['height']} rows")
        padded_rows = []
        for row_number, row in enumerate(rows):
            if len(row) != grid["width"] or set(row) - {".", "#"}:
                raise ValueError(f"host icon {name} row {row_number} is not a valid {grid['width']}-pixel row")
            padded_rows.append("." * horizontal_padding + row + "." * horizontal_padding)
        layout.setdefault("pixel_art", {})[f"os_{name}"] = padded_rows
    return layout


def micro_glyph(character: str) -> tuple[str, ...]:
    rows = MICRO_FONT[character]
    occupied = [column for column in range(3) if any(row[column] == "#" for row in rows)]
    return tuple(row[min(occupied):max(occupied) + 1] for row in rows)


def micro_text_rows(text: str, width: int = 32) -> list[str]:
    text = text.upper()
    unsupported = set(text) - set(MICRO_FONT)
    if unsupported:
        raise ValueError(f"micro label uses unsupported characters: {sorted(unsupported)}")
    glyphs = [micro_glyph(character) for character in text]
    text_width = sum(len(glyph[0]) for glyph in glyphs) + max(0, len(glyphs) - 1)
    if text_width > width:
        raise ValueError(f"micro label {text!r} is {text_width} pixels wide; expected at most {width}")
    start_x = width // 2 - text_width // 2
    pixels = [[False] * width for _ in range(8)]
    x = start_x
    for glyph in glyphs:
        for y, row in enumerate(glyph):
            for offset, pixel in enumerate(row):
                pixels[y][x + offset] = pixel == "#"
        x += len(glyph[0]) + 1
    return ["".join("#" if pixel else "." for pixel in row) for row in pixels]


def glyph_pixel_rows(font: list[list[int]], glyphs: list[int], columns: int) -> list[str]:
    width = columns * 6
    rows = (len(glyphs) + columns - 1) // columns
    pixels = [[False] * width for _ in range(rows * 8)]
    for offset, codepoint in enumerate(glyphs):
        cell_x = (offset % columns) * 6
        cell_y = (offset // columns) * 8
        for x, byte in enumerate(font[codepoint]):
            for y in range(8):
                pixels[cell_y + y][cell_x + x] = bool(byte & (1 << y))
    return ["".join("#" if pixel else "." for pixel in row) for row in pixels]


def prepare_pixel_assets(layout: dict[str, Any], font: list[list[int]]) -> None:
    columns = layout["display"]["columns"]
    logo = parse_glyph_rows(layout["assets"]["corne_logo"], columns, "Corne logo")
    layout["pixel_art"]["corne_logo"] = glyph_pixel_rows(font, logo, columns)
    for name, label in layout["labels"].items():
        layout["pixel_art"][f"label_{name}"] = micro_text_rows(label)

    digit_font = {}
    for digit in "0123456789":
        native = glyph_pixel_rows(font, [ord(digit)], 1)
        digit_font[digit] = [row[:5] for row in native[:7]]
    layout["digit_font"] = digit_font


def bitmap_digest(rows: list[str]) -> str:
    pixels = parse_pixel_art(rows, len(rows[0]), "protected asset")
    return hashlib.sha256(bytes(pack_bitmap(pixels))).hexdigest()


def validate_original_assets(layout: dict[str, Any], font: list[list[int]]) -> None:
    assets = {"corne_logo": layout["pixel_art"]["corne_logo"]}
    for layer_name, glyph_rows in layout["assets"]["layers"].items():
        glyphs = parse_glyph_rows(glyph_rows, 5, f"layer {layer_name}")
        assets[f"layer/{layer_name}"] = glyph_pixel_rows(font, glyphs, 5)
    for pair_name, states in layout["assets"]["modifier_pairs"].items():
        for state_name, glyph_rows in states.items():
            glyphs = parse_glyph_rows(glyph_rows, 5, f"{pair_name} {state_name}")
            assets[f"{pair_name}/{state_name}"] = glyph_pixel_rows(font, glyphs, 5)

    if set(assets) != set(ORIGINAL_ASSET_HASHES):
        raise ValueError("protected Corne OLED asset set changed")
    for name, rows in assets.items():
        if bitmap_digest(rows) != ORIGINAL_ASSET_HASHES[name]:
            raise ValueError(f"protected OLED asset {name} no longer matches the original bitmap")


def parse_glyph_rows(rows: list[str], columns: int, name: str) -> list[int]:
    result: list[int] = []
    for row_number, row in enumerate(rows):
        values = row.split()
        if len(values) != columns:
            raise ValueError(f"{name} row {row_number} has {len(values)} cells; expected {columns}")
        for value in values:
            codepoint = int(value, 16)
            if not 1 <= codepoint <= 0xDF:
                raise ValueError(f"{name} contains invalid glyph {value!r}")
            result.append(codepoint)
    return result


def parse_pixel_art(rows: list[str], width: int, name: str) -> list[list[bool]]:
    if not rows or len(rows) % 8:
        raise ValueError(f"{name} height must be a non-zero multiple of 8")
    pixels: list[list[bool]] = []
    for row_number, row in enumerate(rows):
        if len(row) != width:
            raise ValueError(f"{name} row {row_number} is {len(row)} pixels wide; expected {width}")
        invalid = set(row) - {".", "#"}
        if invalid:
            raise ValueError(f"{name} row {row_number} contains invalid pixels: {sorted(invalid)}")
        pixels.append([pixel == "#" for pixel in row])
    return pixels


def pack_bitmap(pixels: list[list[bool]]) -> list[int]:
    height = len(pixels)
    width = len(pixels[0])
    packed: list[int] = []
    for page in range(height // 8):
        for x in range(width):
            value = 0
            for bit in range(8):
                if pixels[page * 8 + bit][x]:
                    value |= 1 << bit
            packed.append(value)
    return packed


def c_array(name: str, values: list[int], *, terminator: bool = False) -> str:
    encoded = ", ".join(f"0x{value:02x}" for value in values)
    if terminator:
        encoded += ", 0"
    c_type = "char" if terminator else "uint8_t"
    return f"static const {c_type} PROGMEM {name}[] = {{{encoded}}};"


def digit_rows(layout: dict[str, Any]) -> list[list[int]]:
    digits: list[list[int]] = []
    for digit in range(10):
        rows = layout["digit_font"][str(digit)]
        if len(rows) != 7 or any(len(row) != 5 or set(row) - {".", "#"} for row in rows):
            raise ValueError(f"digit {digit} must be the OLED font's native 5 by 7 pixel glyph")
        digits.append([sum(1 << x for x, pixel in enumerate(row) if pixel == "#") for row in rows])
    return digits


def generate_header(layout: dict[str, Any]) -> str:
    display = layout["display"]
    columns = display["columns"]
    width = display["pixel_width"]
    if width != 32 or display["pixel_height"] != 128:
        raise ValueError("the renderer currently targets the Corne's rotated 32 by 128 OLED")

    lines = [
        "// Generated by oled/generate.py from oled/layout.json and oled/icons.json. Do not edit.",
        "#pragma once",
        "",
        f"#define OLED_LAYOUT_PIXEL_WIDTH {width}",
        f"#define OLED_LAYOUT_PIXEL_HEIGHT {display['pixel_height']}",
        "#define OLED_LAYOUT_HISTORY_SIZE 32",
        "#define OLED_LAYOUT_DIGIT_WIDTH 5",
        "#define OLED_LAYOUT_DIGIT_HEIGHT 7",
    ]

    for name, position in layout["positions"].items():
        macro = f"OLED_LAYOUT_{name.upper()}"
        for key, value in position.items():
            lines.append(f"#define {macro}_{key.upper()} {value}")

    lines.append("")
    for name, rows in layout["pixel_art"].items():
        bitmap_width = len(rows[0])
        pixels = parse_pixel_art(rows, bitmap_width, name)
        lines.append(f"#define OLED_BITMAP_{name.upper()}_WIDTH {bitmap_width}")
        lines.append(f"#define OLED_BITMAP_{name.upper()}_HEIGHT {len(pixels)}")
        lines.append(c_array(f"oled_bitmap_{name}", pack_bitmap(pixels)))

    lines.append("")
    for name, rows in layout["assets"]["layers"].items():
        lines.append(c_array(f"oled_layer_{name}", parse_glyph_rows(rows, columns, f"layer {name}"), terminator=True))

    for pair_name, states in layout["assets"]["modifier_pairs"].items():
        if tuple(states) != STATE_ORDER:
            raise ValueError(f"modifier pair {pair_name} must define states in this order: {STATE_ORDER}")
        for state, rows in states.items():
            lines.append(c_array(
                f"oled_{pair_name}_{state}",
                parse_glyph_rows(rows, columns, f"{pair_name} {state}"),
                terminator=True,
            ))

    lines.append("")
    lines.append("static const uint8_t PROGMEM oled_digit_rows[10][OLED_LAYOUT_DIGIT_HEIGHT] = {")
    for digit, rows in enumerate(digit_rows(layout)):
        encoded = ", ".join(f"0x{row:02x}" for row in rows)
        lines.append(f"    {{{encoded}}}, // {digit}")
    lines.append("};")
    return "\n".join(lines) + "\n"


def parse_font() -> list[list[int]]:
    source = FONT_PATH.read_text(encoding="utf-8")
    match = re.search(r"font\[\].*?=\s*\{(?P<body>.*?)\};", source, re.DOTALL)
    if not match:
        raise ValueError(f"could not find the font array in {FONT_PATH}")
    values = [int(value, 16) for value in re.findall(r"0x([0-9a-fA-F]{2})", match.group("body"))]
    if len(values) != 224 * 6:
        raise ValueError(f"font contains {len(values)} bytes; expected 1344")
    return [values[index:index + 6] for index in range(0, len(values), 6)]


def state_name(first: bool, second: bool) -> str:
    return f"{'on' if first else 'off'}_{'on' if second else 'off'}"


def draw_glyphs(canvas: "Image.Image", font: list[list[int]], column: int, row: int, glyphs: list[int], columns: int) -> None:
    for offset, codepoint in enumerate(glyphs):
        cell_column = (column + offset) % columns
        cell_row = row + (column + offset) // columns
        for pixel_x, byte in enumerate(font[codepoint]):
            for pixel_y in range(8):
                if byte & (1 << pixel_y):
                    canvas.putpixel((cell_column * 6 + pixel_x, cell_row * 8 + pixel_y), 1)


def draw_text(canvas: "Image.Image", font: list[list[int]], position: dict[str, int], text: str, columns: int) -> None:
    draw_glyphs(canvas, font, position["column"], position["row"], [ord(character) for character in text], columns)


def draw_pixel_art(canvas: "Image.Image", rows: list[str], position: dict[str, int]) -> None:
    for y, row in enumerate(rows):
        for x, pixel in enumerate(row):
            if pixel == "#":
                canvas.putpixel((position["x"] + x, position["y"] + y), 1)


def draw_large_number(canvas: "Image.Image", layout: dict[str, Any], value: int, position: dict[str, int]) -> None:
    text = str(min(value, 255))
    scale = 3 if len(text) <= 2 else 2
    digit_width = 5 * scale
    gap = 1
    total_width = len(text) * digit_width + (len(text) - 1) * gap
    start_x = position["x"] + (32 - total_width) // 2
    start_y = position["y"] + (24 - 7 * scale) // 2
    for character in text:
        rows = layout["digit_font"][character]
        for row_number, row in enumerate(rows):
            for column_number, pixel in enumerate(row):
                if pixel == "#":
                    for offset_y in range(scale):
                        for offset_x in range(scale):
                            canvas.putpixel(
                                (start_x + column_number * scale + offset_x, start_y + row_number * scale + offset_y),
                                1,
                            )
        start_x += digit_width + gap


def draw_chart(canvas: "Image.Image", values: list[int], position: dict[str, int]) -> None:
    if len(values) != position["width"]:
        raise ValueError(f"chart history must contain exactly {position['width']} samples")
    chart_bottom = position["y"] + position["height"] - 2
    chart_range = position["height"] - 3
    scale_max = max(60, max(values))
    for x in range(position["x"], position["x"] + position["width"], 2):
        canvas.putpixel((x, chart_bottom + 1), 1)
    points = []
    for index, value in enumerate(values):
        y = chart_bottom - min(value, scale_max) * chart_range // scale_max
        points.append((position["x"] + index, y))
    ImageDraw.Draw(canvas).line(points, fill=1, width=1)


def render_state_screen(layout: dict[str, Any], font: list[list[int]], preview: dict[str, Any]) -> "Image.Image":
    display = layout["display"]
    positions = layout["positions"]
    canvas = Image.new("1", (display["pixel_width"], display["pixel_height"]), 0)

    os_name = f"os_{preview['os']}"
    draw_pixel_art(canvas, layout["pixel_art"]["corne_logo"], positions["corne_logo"])
    draw_pixel_art(canvas, layout["pixel_art"][f"label_layout_{preview['layout']}"], positions["layout_label"])
    draw_pixel_art(canvas, layout["pixel_art"][os_name], positions["os_bitmap"])
    layer_name = preview["layer"] if preview["layer"] in layout["assets"]["layers"] else "default"
    draw_glyphs(
        canvas,
        font,
        positions["layer"]["column"],
        positions["layer"]["row"],
        parse_glyph_rows(layout["assets"]["layers"][layer_name], display["columns"], layer_name),
        display["columns"],
    )
    draw_pixel_art(canvas, layout["pixel_art"][f"label_layer_{layer_name}"], positions["layer_label"])
    gui_alt_state = state_name(preview["gui"], preview["alt"])
    draw_glyphs(
        canvas,
        font,
        positions["gui_alt"]["column"],
        positions["gui_alt"]["row"],
        parse_glyph_rows(layout["assets"]["modifier_pairs"]["gui_alt"][gui_alt_state], display["columns"], gui_alt_state),
        display["columns"],
    )
    ctrl_shift_state = state_name(preview["ctrl"], preview["shift"])
    draw_glyphs(
        canvas,
        font,
        positions["ctrl_shift"]["column"],
        positions["ctrl_shift"]["row"],
        parse_glyph_rows(layout["assets"]["modifier_pairs"]["ctrl_shift"][ctrl_shift_state], display["columns"], ctrl_shift_state),
        display["columns"],
    )
    return canvas


def render_performance_screen(layout: dict[str, Any], font: list[list[int]], preview: dict[str, Any]) -> "Image.Image":
    display = layout["display"]
    positions = layout["positions"]
    canvas = Image.new("1", (display["pixel_width"], display["pixel_height"]), 0)
    draw_large_number(canvas, layout, preview["wpm"], positions["wpm_number"])
    draw_pixel_art(canvas, layout["pixel_art"]["label_wpm"], positions["wpm_label"])
    draw_chart(canvas, preview["history"], positions["chart"])
    draw_pixel_art(canvas, layout["pixel_art"]["label_peak"], positions["peak_label"])
    draw_large_number(canvas, layout, preview["peak"], positions["peak_number"])
    return canvas


def generate_preview(layout: dict[str, Any]) -> "Image.Image":
    if Image is None:
        raise RuntimeError("preview generation needs Pillow: python3 -m pip install Pillow")

    font = parse_font()
    scale = 4
    bezel = 6
    screen_width = layout["display"]["pixel_width"] * scale
    screen_height = layout["display"]["pixel_height"] * scale
    pair_gap = 12
    padding = 14
    label_height = 28
    panel_width = padding * 2 + bezel * 4 + screen_width * 2 + pair_gap
    panel_height = padding * 2 + bezel * 2 + screen_height + label_height
    previews = layout["previews"]
    montage = Image.new("RGB", (panel_width * 2, panel_height * 2), "#ece8df")
    draw = ImageDraw.Draw(montage)
    label_font = ImageFont.load_default(size=14)

    for index, preview in enumerate(previews):
        panel_x = index % 2 * panel_width
        panel_y = index // 2 * panel_height
        label_box = draw.textbbox((0, 0), preview["name"], font=label_font)
        label_width = label_box[2] - label_box[0]
        draw.text((panel_x + (panel_width - label_width) / 2, panel_y + padding), preview["name"], fill="#252927", font=label_font)

        screens = (render_state_screen(layout, font, preview), render_performance_screen(layout, font, preview))
        for screen_index, screen in enumerate(screens):
            x = panel_x + padding + bezel + screen_index * (screen_width + pair_gap + 2 * bezel)
            y = panel_y + padding + label_height + bezel
            bezel_box = (x - bezel, y - bezel, x + screen_width + bezel, y + screen_height + bezel)
            draw.rounded_rectangle(bezel_box, radius=10, fill="#1c211f")
            enlarged = screen.resize((screen_width, screen_height), Image.Resampling.NEAREST)
            colored = Image.new("RGB", enlarged.size, "#07110f")
            colored.paste(Image.new("RGB", enlarged.size, "#9fffd5"), mask=enlarged)
            montage.paste(colored, (x, y))

    return montage


def colored_screen(screen: "Image.Image", scale: int) -> "Image.Image":
    enlarged = screen.resize((screen.width * scale, screen.height * scale), Image.Resampling.NEAREST)
    colored = Image.new("RGB", enlarged.size, "#07110f")
    colored.paste(Image.new("RGB", enlarged.size, "#9fffd5"), mask=enlarged)
    return colored


def contact_sheet(screens: list[tuple[str, "Image.Image"]], columns: int, scale: int) -> "Image.Image":
    padding = 12
    gap = 10
    label_height = 24
    bezel = 5
    label_font = ImageFont.load_default(size=13)
    screen_width = screens[0][1].width * scale
    screen_height = screens[0][1].height * scale
    cell_width = screen_width + 2 * (padding + bezel)
    cell_height = screen_height + 2 * (padding + bezel) + label_height
    rows = (len(screens) + columns - 1) // columns
    sheet = Image.new("RGB", (columns * cell_width + (columns - 1) * gap, rows * cell_height + (rows - 1) * gap), "#ece8df")
    draw = ImageDraw.Draw(sheet)

    for index, (label, screen) in enumerate(screens):
        cell_x = index % columns * (cell_width + gap)
        cell_y = index // columns * (cell_height + gap)
        label_box = draw.textbbox((0, 0), label, font=label_font)
        label_width = label_box[2] - label_box[0]
        draw.text((cell_x + (cell_width - label_width) / 2, cell_y + padding), label, fill="#252927", font=label_font)
        x = cell_x + padding + bezel
        y = cell_y + padding + label_height + bezel
        draw.rounded_rectangle((x - bezel, y - bezel, x + screen_width + bezel, y + screen_height + bezel), radius=8, fill="#1c211f")
        sheet.paste(colored_screen(screen, scale), (x, y))
    return sheet


def generate_state_matrix(layout: dict[str, Any]) -> "Image.Image":
    font = parse_font()
    screens: list[tuple[str, Image.Image]] = []
    layout_labels = {"qwerty": "QW", "colemak": "COL"}
    os_labels = {"macos": "MAC", "linux": "LNX", "windows": "WIN"}
    layer_labels = {"default": "BASE", "lower": "LOW", "raise": "RAI", "adjust": "ADJ", "nav": "N=B"}
    for layout_name in ("qwerty", "colemak"):
        for os_name in ("macos", "linux", "windows"):
            for layer_name in ("default", "lower", "raise", "adjust", "nav"):
                preview = {
                    "layout": layout_name,
                    "os": os_name,
                    "layer": layer_name,
                    "gui": False,
                    "alt": False,
                    "ctrl": False,
                    "shift": False,
                }
                label = f"{layout_labels[layout_name]}/{os_labels[os_name]} {layer_labels[layer_name]}"
                screens.append((label, render_state_screen(layout, font, preview)))
    return contact_sheet(screens, columns=5, scale=3)


def generate_modifier_matrix(layout: dict[str, Any]) -> "Image.Image":
    font = parse_font()
    screens: list[tuple[str, Image.Image]] = []
    names = (("G", "gui"), ("A", "alt"), ("C", "ctrl"), ("S", "shift"))
    for combination in range(16):
        preview = {"layout": "colemak", "os": "macos", "layer": "default"}
        active = []
        for bit, (short_name, field_name) in enumerate(names):
            enabled = bool(combination & (1 << bit))
            preview[field_name] = enabled
            if enabled:
                active.append(short_name)
        screen = render_state_screen(layout, font, preview).crop((0, 96, 32, 128))
        screens.append(("+".join(active) if active else "none", screen))
    return contact_sheet(screens, columns=4, scale=7)


def performance_history(value: int, phase: float) -> list[int]:
    if value == 0:
        return [0] * 32
    result = []
    for index in range(32):
        ramp = 0.25 + 0.75 * index / 31
        wave = 0.13 * math.sin(index * 0.72 + phase)
        result.append(max(0, min(240, round(value * (ramp + wave)))))
    result[-1] = value
    return result


def generate_performance_matrix(layout: dict[str, Any]) -> "Image.Image":
    font = parse_font()
    screens: list[tuple[str, Image.Image]] = []
    for index, value in enumerate((0, 7, 42, 68, 99, 100, 121, 240)):
        peak = min(240, max(value, round(value * 1.16)))
        preview = {"wpm": value, "peak": peak, "history": performance_history(value, index * 0.6)}
        screens.append((f"{value} WPM / {peak} max", render_performance_screen(layout, font, preview)))
    return contact_sheet(screens, columns=4, scale=4)


def write_or_check(path: Path, content: bytes, check: bool) -> bool:
    current = path.read_bytes() if path.exists() else None
    if current == content:
        return True
    if check:
        print(f"out of date: {path.relative_to(REPO_ROOT)}", file=sys.stderr)
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(content)
    print(f"wrote {path.relative_to(REPO_ROOT)}")
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="fail if the generated header is not up to date")
    args = parser.parse_args()

    try:
        layout = load_layout()
        font = parse_font()
        prepare_pixel_assets(layout, font)
        validate_original_assets(layout, font)
        header = generate_header(layout).encode("utf-8")
        if not args.check:
            preview = generate_preview(layout)
            state_matrix = generate_state_matrix(layout)
            modifier_matrix = generate_modifier_matrix(layout)
            performance_matrix = generate_performance_matrix(layout)
    except (KeyError, TypeError, ValueError, RuntimeError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    valid = write_or_check(HEADER_PATH, header, args.check)
    if not args.check:
        for path, image in (
            (PREVIEW_PATH, preview),
            (STATE_MATRIX_PATH, state_matrix),
            (MODIFIER_MATRIX_PATH, modifier_matrix),
            (PERFORMANCE_MATRIX_PATH, performance_matrix),
        ):
            preview_bytes = BytesIO()
            image.save(preview_bytes, format="PNG", optimize=True)
            write_or_check(path, preview_bytes.getvalue(), False)
    return 0 if valid else 1


if __name__ == "__main__":
    raise SystemExit(main())
