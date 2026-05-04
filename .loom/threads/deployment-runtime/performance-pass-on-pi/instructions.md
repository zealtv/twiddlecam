# performance-pass-on-pi

Brief: Validate that the completed first implementation holds a stable usable frame rate on the Pi.

Notes:
- Prioritize stability and latency over effect complexity.
- Start at conservative camera settings and increase only if stable.
- Blur may need to be disabled or simplified on lower-end boards.

Checklist:
- [ ] Run at default resolution/FPS with all core effects neutral.
- [ ] Exercise OSC controls during live camera capture.
- [ ] Test heavy settings: max zoom, rotation, blur, contrast, color mix.
- [ ] Adjust config defaults or limits if the Pi drops frames.
- [ ] Record final recommended Pi config.
