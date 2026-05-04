# shader-pipeline

Brief: Implement the real-time shader processing path from camera texture to fullscreen output.

Notes:
- Preferred pipeline: camera -> color correction -> solid color mix -> transform -> blur -> output.
- Color correction and color mix should be shader-based at minimum.
- Blur should be a separate optional pass.

Checklist:
- [ ] Implement color correction shader.
- [ ] Implement solid color generation and mix modes.
- [ ] Implement transform controls and rotation LFO.
- [ ] Implement optional blur pass.
- [ ] Validate performance on the Pi at target resolution/FPS.
