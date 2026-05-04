# osc-parameter-core

Brief: Build the config, OSC, parameter, smoothing, and reset core.

Notes:
- OSC is UDP on all interfaces, default port 1111.
- Addresses are flat and performance-facing values are normalized floats unless specified.
- Continuous parameters have current, target, default, smoothed, and wrapping behavior.

Checklist:
- [ ] Load runtime config.
- [ ] Define parameter defaults and input clamping.
- [ ] Receive and route all OSC addresses from the spec.
- [ ] Implement `/slurp` smoothing.
- [ ] Implement `/reset 1` behavior.
