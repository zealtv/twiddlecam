# evaluate-pi4-csi-libcamera

Brief: Evaluate whether Pi 4 and/or Raspberry Pi CSI camera through libcamera gives a better latency budget.

Checklist:
- [ ] Set up equivalent openFrameworks build on Raspberry Pi 4 if hardware is available.
- [ ] Re-test USB UVC `yuy2_low_latency` and `mjpeg_hd` on Pi 4.
- [ ] Test Raspberry Pi CSI camera using the modern libcamera stack.
- [ ] Prototype a GStreamer `libcamerasrc` pipeline suitable for openFrameworks.
- [ ] Compare latency, frame stability, and image quality against Pi 3B+ USB UVC results.
- [ ] Record whether the production target should move to Pi 4 USB, Pi 4 CSI, or stay on Pi 3B+.
