# pi-bringup

Brief: Establish the fresh Raspberry Pi as a known target for development and testing.

Notes:
- This is the first root thread because hardware facts shape later choices.
- Record Pi model, OS version, display path, network address, camera model, and GPU/display environment.
- Do not install the full application here; this thread is about proof that the board, camera, display, and access path are sane.

Checklist:
- [ ] Confirm SSH/local access and repo transfer workflow.
- [ ] Identify OS, architecture, Pi model, graphics stack, and available disk space.
- [ ] Confirm USB webcam is visible to Linux.
- [ ] Confirm display output works fullscreen on display 0.
- [ ] Tie this thread when the Pi is ready for openFrameworks setup.
