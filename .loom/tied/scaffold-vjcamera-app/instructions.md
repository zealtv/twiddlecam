# scaffold-vjcamera-app

Brief: Create the initial VJCamera openFrameworks project structure from the spec.

Notes:
- Suggested files: `main.cpp`, `ofApp`, `OscController`, `Parameter`, `VideoProcessor`, `Config`.
- Suggested data: `bin/data/config.json` and `bin/data/shaders/`.
- Keep implementation skeletal until the camera and OSC stitches fill it in.

Checklist:
- [x] Create the OF app directory and source files.
- [x] Add a default `config.json`.
- [x] Add placeholder/pass-through shaders.
- [x] Ensure the scaffold builds.
- [x] Commit or record scaffold outcome before adding behavior.

Outcome:
- Created `/home/pi/openFrameworks/apps/myApps/VJCamera` from `emptyExample`.
- Added skeletal `Config`, `Parameter`, `OscController`, and `VideoProcessor` modules.
- Added `bin/data/config.json` and placeholder `bin/data/shaders/pass.vert` / `pass.frag`.
- Verified `make Release -j1` completes on the Pi and produces `/home/pi/openFrameworks/apps/myApps/VJCamera/bin/VJCamera` (3.0M).

Notes:
- Build on Raspberry Pi 3B+ was very slow for even the scaffold. Keep future compile steps small and expect long waits.
