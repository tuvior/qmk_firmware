# OLED design QA

**Source visual truth**

- Accepted render: `.build/crkbd_tuvior_oled_preview_v5.png`
- SHA-256: `182ffa6b783d400c9b22c914aeee4c1b5e7f62e4382bdba9ab1350d8be937176`
- Pixel dimensions: 640 by 1189
- OLED viewport: 32 by 128 pixels per screen, displayed at 4x nearest-neighbor scale
- States: Colemak/macOS/base, QWERTY/Linux/lower, QWERTY/Windows/raise, Colemak/macOS/adjust

**Implementation evidence**

- Canonical generated render: `.build/crkbd_tuvior_oled_preview.png`
- SHA-256: `182ffa6b783d400c9b22c914aeee4c1b5e7f62e4382bdba9ab1350d8be937176`
- Pixel dimensions: 640 by 1189
- Density normalization: none; source and implementation used the same 1-bit 32 by 128 screen buffers and 4x presentation scale
- Firmware asset: `layout.generated.h`, produced by the same generator and layout data as the implementation render

**Full-view comparison evidence**

The accepted v5 PNG and canonical generated PNG were opened, compared at the same dimensions and states, and were byte-for-byte identical before the redundant versioned render was removed. Fonts, spacing, palette, assets, and content therefore have no rendered differences.

**Focused-region evidence**

Each of the four 32 by 128 state buffers and four performance buffers was also compared directly. All buffers were byte-for-byte identical, covering the Corne logo, layout labels, OS icons, layer art, layer labels, all displayed modifier combinations, WPM digits, chart, and maximum value. Separate crops were unnecessary because the underlying monochrome buffers matched exactly.

**Findings**

- Fonts and typography: passed. The micro labels and native 5 by 7 OLED digits match the accepted render.
- Spacing and layout rhythm: passed. Arbitrary pixel placement, including the OS icon at y=36, matches the accepted render.
- Colors and visual tokens: passed. The one-bit screen buffers and preview colors are identical.
- Image quality and asset fidelity: passed. Original Corne, layer, and modifier bitmaps are protected by source-pixel hashes; OS icons use the accepted grids.
- Copy and content: passed. Layout, layer, WPM, and maximum labels match every accepted state.

**Comparison history**

- Earlier P1: the accepted composition existed only in the preview workbench while firmware still used the old keyboard artwork, page-aligned positions, OS labels, and 4 by 7 numbers.
- Fix: made `layout.json` authoritative for firmware and previews, generated the original logo and native digits from `glcdfont.c`, added exact-coordinate bitmap rendering, and removed the preview-only composition path.
- Post-fix evidence: the accepted and canonical preview PNG hashes match, all eight screen buffers match, the generated header check passes, and the Corne firmware compiles.

**Residual test gap**

Physical OLED behavior still needs an on-keyboard visual check after flashing; this does not change the source-to-render fidelity result.

final result: passed
