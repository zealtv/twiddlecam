# fullscreen-autostart

Brief: Configure launch behavior suitable for headless/performance deployment.

Notes:
- App should always run fullscreen.
- Display selection is not configurable in first implementation.
- Autostart mechanism should match the Pi OS session model.

Checklist:
- [ ] Confirm fullscreen behavior in code.
- [ ] Choose autostart mechanism: systemd user service, desktop autostart, shell profile, or other.
- [ ] Record how to start, stop, and view logs.
- [ ] Confirm app launches after reboot.
- [ ] Confirm OSC can reach the app after autostart.
