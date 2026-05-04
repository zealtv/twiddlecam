# validate-camera-and-display

Brief: Verify the attached USB camera and display path before writing app code.

Notes:
- Target is first available USB UVC webcam.
- Display routing is handled by the OS, not the app.
- Use lightweight platform tools first, then an openFrameworks window later.

Outcome so far:
- `v4l2-ctl --list-devices` identifies the USB webcam as `4k usb Camera Redeagle: 4k usb`.
- Camera capture nodes: `/dev/video0` and `/dev/video1`; `/dev/video0` is the useful capture node.
- `/dev/video0` supports MJPG and YUYV.
- Advertised MJPG modes include 3840x2160, 2592x1944, 2560x1440, 1920x1080, 1280x960, 1280x720, 800x600, 640x480, 640x360, and 320x240 at 30 FPS.
- Advertised YUYV modes include 640x480, 640x360, and 320x240 at 30 FPS; higher YUYV modes are lower FPS.
- Forced 640x480 YUYV at 30 FPS negotiated successfully and captured frames to `/tmp/twiddlecam-640x480-yuyv.raw`.
- `v4l2-ctl` streaming tests report roughly 15 FPS for both 640x480 YUYV and MJPG despite 30 FPS negotiation. Treat 640x480/30 as the requested default but expect the actual rate may be lower on this Pi/camera path.
- Permissions are okay: video devices are `root:video`, and user `pi` is in `video`; DRM render node exists and user `pi` is in `render`.
- Display was connected after the initial check: `/sys/class/drm/card0-HDMI-A-1/status` now reports `connected`.
- HDMI modes include 1920x1080, 1680x1050, 1600x900, 1280x1024, 1440x900, 1280x800, 1280x720, 1024x768, 800x600, 720x576, 720x480, and 640x480.
- `/dev/fb0` exists with `root:video` permissions.
- Runtime target is `multi-user.target`; there is no desktop session visible from `loginctl`.

Checklist:
- [x] Confirm `/dev/video*` devices appear when the webcam is attached.
- [x] List supported camera modes if `v4l2-ctl` is available.
- [x] Confirm a live test frame or preview can be obtained outside the app.
- [x] Confirm HDMI/composite output target is active.
- [x] Note any permissions or group membership needed for camera access.
