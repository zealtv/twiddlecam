# measure-camera-latency

Brief: Measure end-to-end camera/display latency instead of relying only on subjective feel.

Checklist:
- [ ] Build or choose a repeatable test method, such as filming a timer/flash source visible to the camera and HDMI display.
- [ ] Measure current `yuy2_low_latency` at `640x480@30` on Raspberry Pi 3B+.
- [ ] Measure `320x240@30` YUY2 and `mjpeg_hd` for comparison if useful.
- [ ] Capture CPU load, app FPS, and dropped-frame symptoms while measuring.
- [ ] Decide whether remaining latency is camera capture, GStreamer buffering, X/GL presentation, or app processing.
- [ ] Record next optimization or hardware migration recommendation.
