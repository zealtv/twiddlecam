# color-correction-shader

Brief: Implement brightness, contrast, saturation, hue, and invert in a shader.

Notes:
- Brightness, contrast, saturation defaults are neutral at 0.5.
- Hue wraps 0.0-1.0 across configured degrees, default 360.
- Invert is immediate and not smoothed.

Checklist:
- [ ] Add shader uniforms for brightness, contrast gain, saturation gain, hue rotation, and invert.
- [ ] Apply spec mappings and clamping.
- [ ] Confirm neutral defaults produce pass-through video.
- [ ] Confirm each control visibly changes output.
- [ ] Add shader load failure fallback if practical.
