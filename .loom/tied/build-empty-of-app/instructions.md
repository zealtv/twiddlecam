# build-empty-of-app

Brief: Build and run a minimal openFrameworks app on the Pi.

Notes:
- Use an upstream example or an empty generated app.
- The app does not need camera, OSC, shaders, or repo structure yet.

Outcome so far:
- Selected the packaged app at `/home/pi/openFrameworks/apps/myApps/emptyExample`.
- Built it successfully with:
  `make Release -C ~/openFrameworks/apps/myApps/emptyExample -j1`
- Binary produced at:
  `/home/pi/openFrameworks/apps/myApps/emptyExample/bin/emptyExample`
- Short run test from SSH:
  `cd ~/openFrameworks/apps/myApps/emptyExample/bin && timeout 8 ./emptyExample`
- Run failed before creating a window:
  - `ofAppGLFWWindow: Failed to detect any supported platform`
  - `ofAppGLFWWindow: couldn't init GLFW`
  - process aborted with exit `134`
- Display/session check after the failed run:
  - no `Xorg`, `startx`, `xinit`, `weston`, or `labwc` found on PATH
  - `XDG_SESSION_TYPE=tty`
  - default system target is `multi-user.target`
- Interpretation: the OF toolchain and empty app build work, but this Pi image currently has no X11/Wayland display session for GLFW to bind to. Visible/fullscreen run is blocked on installing/configuring a minimal display session or choosing a non-X11 runtime path.
- Follow-up from HDMI console: the empty example runs successfully when launched directly from the active HDMI console/session.
- Important deployment note: launching from SSH/tmux without explicitly binding to the active local display/session fails. Runtime scripts or services must target the active monitor/session explicitly, for example by running inside the console/X session or setting the correct display environment such as `DISPLAY`, `XAUTHORITY`, and possibly `XDG_RUNTIME_DIR`.

Checklist:
- [x] Generate or select a minimal OF app.
- [x] Build it successfully on the Pi.
- [x] Run it and confirm a visible window.
- [x] Switch it to fullscreen and confirm display 0 output.
- [x] Record build and run commands.
