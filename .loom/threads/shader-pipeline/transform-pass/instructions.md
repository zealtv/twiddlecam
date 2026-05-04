# transform-pass

Brief: Implement x/y translation, zoom, rotate, and optional rotation LFO.

Notes:
- Translation range moves the image by one full frame in each direction.
- Zoom is native at 0.5 and uses configured `maxZoom` above 0.5.
- Rotation maps 0.0-1.0 to configured range, default -180 to +180 degrees.

Checklist:
- [ ] Apply x/y transform mappings.
- [ ] Apply zoom mapping with configured min/max behavior.
- [ ] Apply base rotation mapping.
- [ ] Add accumulated rotation LFO using configured max speed.
- [ ] Confirm transforms are centered and stable at defaults.
