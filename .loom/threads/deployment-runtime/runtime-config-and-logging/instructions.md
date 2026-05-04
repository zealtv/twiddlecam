# runtime-config-and-logging

Brief: Make runtime configuration and logs clear enough for performance troubleshooting.

Notes:
- Config should expose performance-critical limits and toggles.
- Logs should state OSC port, camera status, active mode, shader status, and config fallback behavior.

Checklist:
- [ ] Confirm `config.json` is packaged in `bin/data`.
- [ ] Document all config fields used by the app.
- [ ] Log loaded OSC port and camera request.
- [ ] Log actual camera mode or fallback state.
- [ ] Log shader load failures and performance toggles.
