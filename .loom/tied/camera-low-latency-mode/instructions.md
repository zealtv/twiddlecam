# camera-low-latency-mode

Brief: Add and verify a low-latency YUYV/YUY2 camera pipeline for Raspberry Pi 3B+.

Checklist:
- [x] Add config support for camera pipeline modes, at least `mjpeg_hd` and `yuy2_low_latency`.
- [x] Implement `yuy2_low_latency` as `/dev/video0` `video/x-raw,format=YUY2,width=640,height=480,framerate=30/1`.
- [x] Prefer low buffering settings such as `io-mode=2` where supported.
- [x] Test launch on the Pi and compare subjective latency against `mjpeg_hd`.
- [x] Keep `mjpeg_hd` available for Pi 4 or better hardware.
- [x] Record the selected Pi 3 default and any follow-up performance work.

Notes:
- Current working mode is explicit GStreamer MJPEG: `/dev/video0 1280x720@30`.
- It works, but latency is too high on Raspberry Pi 3B+.
- Camera supports YUYV/YUY2 at 30 FPS for `640x480`, `640x360`, and `320x240`.
- GStreamer caps name is `YUY2` even though `v4l2-ctl` reports `YUYV`.
- Resolution is secondary to latency on Pi 3B+; expect Pi 4 migration later.

Outcome notes:
- Added `camera.pipelineMode` and `camera.forceFallback` config fields in the Pi app.
- `mjpeg_hd` remains available as explicit GStreamer MJPEG at `1280x720@30`.
- `yuy2_low_latency` opens successfully with `v4l2src device=/dev/video0 io-mode=2 do-timestamp=true ! video/x-raw,format=YUY2,... ! videoconvert ! videoscale`.
- Verified `640x480@30` YUY2 on HDMI via VT2/startx. User reports latency is better than MJPEG but still not great.
- Tested `320x240@30` YUY2 on HDMI via VT2/startx. User estimates latency is still noticeable, roughly 200 ms.
- Selected current Pi 3B+ default: `yuy2_low_latency` at `640x480@30`. It gives better latency than MJPEG while preserving usable image detail; dropping to `320x240` did not remove the perceptible delay.
- CSI/libcamera is a plausible future performance path, especially with a Pi 4, but it should be tracked separately because it changes the capture stack from UVC `/dev/video0` to Raspberry Pi `libcamera`/GStreamer.
