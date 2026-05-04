# solid-color-mix

Brief: Generate HSL-style solid color and mix it with the processed video.

Notes:
- Controls: `/color_hue`, `/color_saturation`, `/color_luminance`, `/color_mix_mode`.
- Modes: add, subtract, minimum, maximum.
- No separate color mix amount in first implementation.

Checklist:
- [ ] Convert color controls into RGB for shader use.
- [ ] Implement all four mix modes.
- [ ] Clamp out-of-range mix mode values to 0-3.
- [ ] Confirm default color settings leave output neutral or minimally affected as intended.
- [ ] Gate with `enableColorMix` config if implemented.
