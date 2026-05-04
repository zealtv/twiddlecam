# deployment-runtime

Brief: Make the application easy to build, run, configure, and operate during performance.

Notes:
- The app should launch fullscreen and start outputting immediately.
- OS handles output routing; app always targets display 0 for first implementation.
- This thread turns the working app into a repeatable Pi runtime.

Checklist:
- [ ] Add documented build/run commands.
- [ ] Add or document runtime config location.
- [ ] Add fullscreen launch behavior.
- [ ] Decide autostart/systemd/kiosk approach.
- [ ] Run a performance validation pass on the Pi.
