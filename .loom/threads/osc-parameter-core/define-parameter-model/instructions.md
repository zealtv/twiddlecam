# define-parameter-model

Brief: Implement the internal parameter model and default state.

Notes:
- Include all OSC parameters from the spec.
- Continuous values are clamped to 0.0-1.0.
- Hue-like parameters need wrapping behavior.

Checklist:
- [ ] Create a `Parameter` representation with current, target, default, smoothed, and wrapping flags.
- [ ] Add defaults for brightness, contrast, saturation, hue, invert, x, y, zoom, rotate, blur, slurp, color controls, color mix mode, and rotation LFO speed.
- [ ] Add clamping helpers for floats and enum values.
- [ ] Add shortest-path interpolation support for wrapping parameters.
- [ ] Add basic unit-style or logged verification where practical.
