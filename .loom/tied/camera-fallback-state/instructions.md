# camera-fallback-state

Brief: Keep the app alive and controllable when camera initialization fails.

Notes:
- Spec requires a fallback visual state and continued OSC listening.
- First fallback can be black; diagnostic visuals can wait.

Checklist:
- [x] Detect failed camera open.
- [x] Render black or a simple fallback frame.
- [x] Continue running update/draw loops.
- [ ] Confirm OSC still updates internal parameters.
- [x] Log failure without crashing.

Outcome:
- Added `camera.forceFallback` to config parsing and `bin/data/config.json`.
- On forced fallback or camera pipeline failure, the app allocates a black frame buffer, keeps update/draw running, and shows `camera fallback black frame` in the overlay.
- Verified normal camera launch still opens `/dev/video0 1280x720@30 MJPEG`.
- Verified forced fallback launch stays alive and logs: `Camera fallback forced by config; running with black frame`.
- Restored `camera.forceFallback` to `false` after testing.

Deferred:
- OSC receive/routing is not implemented yet, so parameter updates during fallback cannot be meaningfully verified in this stitch. The OSC controller still initializes in fallback mode; actual OSC behavior should be verified after `receive-and-route-osc`.
