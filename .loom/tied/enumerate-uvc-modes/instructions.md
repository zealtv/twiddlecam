# enumerate-uvc-modes

Brief: Discover the webcam modes available on the fresh Pi.

Notes:
- This informs default `config.json` values and fallback logic.
- Prefer `v4l2-ctl --list-devices` and `v4l2-ctl --list-formats-ext`.

Checklist:
- [x] Identify the camera device path and name.
- [x] Record supported pixel formats, resolutions, and frame rates.
- [x] Choose a conservative first default, likely 640x480 at 30 FPS.
- [x] Note any driver or permissions issues.

Outcome:
- Camera: `4k usb Camera Redeagle: 4k usb` on `/dev/video0`, with companion `/dev/video1` and `/dev/media3`.
- Driver: `uvcvideo`, kernel driver version `6.12.75`.
- Current negotiated mode during inspection: `640x360` MJPG at 30 FPS.
- Supported formats on `/dev/video0`:
  - MJPG 30 FPS: `3840x2160`, `2592x1944`, `2560x1440`, `1920x1080`, `1280x960`, `1280x720`, `800x600`, `640x480`, `640x360`, `320x240`.
  - YUYV: `640x480`, `640x360`, and `320x240` at 30 FPS; larger YUYV modes drop to 20/10/5/2 FPS.
- Conservative default for the app: `640x480 @ 30 FPS`, device index `0`.

Notes:
- `pi` user has video/render permissions from earlier checks.
- Prior stream tests negotiated 30 FPS but measured closer to ~15 FPS on the Pi 3B+, so later performance stitches should verify the real app frame rate before increasing resolution.
