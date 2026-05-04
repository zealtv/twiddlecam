# config-loading

Brief: Load `config.json` at startup with sensible defaults.

Notes:
- JSON is acceptable for first implementation.
- Config covers OSC port, camera mode, effect limits, and performance toggles.
- Missing fields should fall back to spec defaults where practical.

Checklist:
- [ ] Add default `bin/data/config.json`.
- [ ] Parse OSC, camera, effects, and performance sections.
- [ ] Provide defaults for missing values.
- [ ] Log loaded configuration.
- [ ] Avoid crashing on malformed config; fall back where practical.
