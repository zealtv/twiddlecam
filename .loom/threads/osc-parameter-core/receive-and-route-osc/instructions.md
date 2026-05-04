# receive-and-route-osc

Brief: Receive OSC messages and route known addresses into parameter targets.

Notes:
- Bind UDP to all interfaces on configured port, default 1111.
- Unknown and malformed messages should be ignored.
- Toggle/enum values should update immediately rather than using slurp.

Checklist:
- [ ] Add OSC receiver dependency/addon.
- [ ] Bind to configured UDP port.
- [ ] Route every address in the spec table.
- [ ] Clamp float and enum inputs.
- [ ] Test with a simple OSC sender from another machine or localhost.
