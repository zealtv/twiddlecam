# implement-slurp-and-reset

Brief: Implement frame-rate-independent smoothing and reset semantics.

Notes:
- `/slurp` maps to `slurp * maxSlurpTimeSeconds`.
- `/slurp` applies to continuous parameters except itself.
- Recommended reset behavior keeps `/slurp` unchanged so reset can glide.

Checklist:
- [ ] Update smoothed current values using exponential smoothing and `deltaTime`.
- [ ] Snap immediately when slurp time is zero.
- [ ] Use circular interpolation for hue and color hue.
- [ ] Implement `/reset 1` to restore target defaults.
- [ ] Reset `invert` and `color_mix_mode` immediately.
