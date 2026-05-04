# camera-capture

Brief: Implement webcam input that starts immediately and degrades gracefully.

Notes:
- Default device is camera index 0.
- Requested width, height, and FPS come from config.
- Internal processing texture resolution should match the active camera resolution.

Checklist:
- [ ] Enumerate the UVC camera modes on the Pi.
- [ ] Open the configured camera mode or closest practical fallback.
- [ ] Display live camera frames in the app.
- [ ] Continue running with a black/fallback frame if no camera is available.
- [ ] Log actual mode and camera failures.

Threading:
- This goal is decomposed into direct child stitches:
  - `enumerate-uvc-modes`
  - `implement-camera-init`
  - `camera-fallback-state`
- Tie this goal stitch to promote those implementation stitches.
