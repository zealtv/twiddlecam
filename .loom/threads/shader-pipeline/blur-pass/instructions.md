# blur-pass

Brief: Implement blur as a separate, optional shader pass.

Notes:
- Blur belongs at the end of the processing pipeline.
- Configured modes: gaussian, box, downsample, none.
- First pass can implement one practical mode plus `none`, as long as it is modular.

Checklist:
- [ ] Add FBO/pass structure for post-transform blur.
- [ ] Map `/blur` to configured `maxBlurRadius`.
- [ ] Implement or select an initial blur mode.
- [ ] Allow blur to be disabled for performance.
- [ ] Measure visual cost on the Pi.
