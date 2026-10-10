# Corne OLED layout

`layout.json` describes both OLEDs and their preview states. It contains the
labels, original glyph codepoints, exact region positions, and representative
states. It is the single source for both `layout.generated.h` and every preview,
so a rendered design cannot remain preview-only.

The top mark is the keymap's original 30 by 24 Corne glyph block from
`glcdfont.c`. `layout.json` records its original 15 codepoints, and the
generator reads their bytes directly. No resampling, tracing, cropping, or
replacement artwork is involved.

WPM values use the digit glyphs already present in this OLED's `glcdfont.c`.
The generator enlarges their native 5 by 7 pixels with integer
scaling: 3x for one or two digits, and 2x for three digits. This keeps the
numbers crisp, readable, and centered without introducing a second typeface.

Modifier state uses the complete original 30 by 32 glyph block: native 12 by 16
Command, Option, Control, and Shift off/on icons plus their original connector
glyphs. The generator reads the same codepoints and font bytes as the firmware;
no icon pixels are cropped, resized, or redrawn.

The four layer indicators also use their complete original 30 by 24 glyph
blocks. Hash checks cover every layer and every modifier state, and generation
fails if the logo, layer art, or modifiers no longer match those source pixels.

`icons.json` is the authoritative 24 by 24 source for the Linux, Windows, and
macOS host icons. Each icon is an explicit `#`/`.` bitmap. `generate.py`
centers those grids in the 32-pixel OLED region, so firmware and previews use
the same pixels.

## Host icon workbench

Render the authoritative icons, their source comparison, and a threshold
sweep:

```sh
python3 keyboards/crkbd/keymaps/tuvior/oled/icon_workbench.py render
```

The command writes three ignored files in `.build/`:

- `crkbd_tuvior_oled_os_icons.png`: the exact three 24 by 24 grids.
- `crkbd_tuvior_oled_os_icon_workbench.png`: reference beside exact output.
- `crkbd_tuvior_oled_os_icon_thresholds.png`: five extraction thresholds for
  each icon.

To try a new source image or extraction setting without modifying the source:

```sh
python3 keyboards/crkbd/keymaps/tuvior/oled/icon_workbench.py extract \
  --reference path/to/reference.png --icon linux --threshold 0.54
```

Add `--write` only after choosing the candidate. It updates the 24 text rows
in `icons.json`; individual pixels can then be refined directly in those rows.
The configured reference is checksum-verified when present, but rendering the
authoritative grids does not depend on image generation.

After editing it, regenerate the firmware header and preview:

```sh
python3 keyboards/crkbd/keymaps/tuvior/oled/generate.py
```

The command writes `layout.generated.h`, which is compiled into the firmware,
and four local, git-ignored PNGs in `.build/`:

- `crkbd_tuvior_oled_preview.png`: curated paired-screen states.
- `crkbd_tuvior_oled_state_matrix.png`: every layout × OS × layer state,
  including how NAV deliberately leaves the tri-layer graphic at base.
- `crkbd_tuvior_oled_modifier_matrix.png`: all 16 modifier combinations.
- `crkbd_tuvior_oled_performance_matrix.png`: representative WPM values,
  chart shapes, and one-, two-, and three-digit rendering.

The previews show the exact pixels produced from `glcdfont.c`. Pillow is
required only for preview generation.

To verify that the checked-in firmware header matches the editable layout:

```sh
python3 keyboards/crkbd/keymaps/tuvior/oled/generate.py --check
```

The primary OLED shows the active keyboard layout, host OS, tri-layer state,
and modifiers. The secondary OLED shows current WPM, a 32-second rolling line
chart, and the session maximum. The four preview scenarios cover every OS and
tri-layer state. Pixel art uses `#` for lit pixels and `.` for unlit pixels, so
the assets remain easy to edit and review in source.
