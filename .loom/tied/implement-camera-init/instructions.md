# implement-camera-init

Brief: Add app-side camera initialization using config values.

Notes:
- Use openFrameworks capture APIs first unless hardware forces a lower-level path.
- The app should begin outputting video immediately after launch.

Checklist:
- [x] Read camera device index, width, height, and FPS from config.
- [x] Open the configured camera.
- [x] Allocate processing textures/FBOs to active camera dimensions.
- [x] Render the live frame through a pass-through path.
- [x] Log the actual active mode.

Progress:
- Updated `/home/pi/openFrameworks/apps/myApps/VJCamera/src/VideoProcessor.h`.
- Updated `/home/pi/openFrameworks/apps/myApps/VJCamera/src/VideoProcessor.cpp`.
- Initial `ofVideoGrabber` path selected Pi ISP nodes before the USB camera, then selected a bad `DMA_DRM` caps mode on `/dev/video0`.
- Replaced camera capture with explicit `ofGstVideoUtils` pipeline targeting `/dev/video0`.
- Current config default is `1280x720@30`.
- Pipeline: `v4l2src device=/dev/video0 ! image/jpeg,width=1280,height=720,framerate=30/1 ! jpegdec ! videoconvert ! videoscale`.
- Frames are uploaded to an `ofTexture`, rendered through an FBO at active camera dimensions, then fitted to the window.
- Rebuilt successfully with `make Release -j1`.

Verification needed:
- Confirmed live camera feed on HDMI via VT2 launch from tmux.
- Log confirmed: `Camera opened: /dev/video0 1280x720@30 MJPEG`.

Notes:
- tmux launch now works using `openvt` + `startx` after configuring `/etc/X11/Xwrapper.config`.
- Direct SSH launch still fails because GLFW has no display platform in that environment.
