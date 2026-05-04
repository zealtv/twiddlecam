# VJ Camera Software Specification

## 1. Overview

This document specifies a real-time video processing application intended for live performance use, especially camera-based video feedback. The application captures a live camera feed, applies controllable video effects in real time, and outputs the processed image through the Raspberry Pi or compatible single-board computer's video output.

The primary target platform is Raspberry Pi, but the software should remain as platform-agnostic as practical, with possible support for Orange Pi running Armbian. The first implementation will target a USB UVC webcam and an openFrameworks-based C++ application.

The application receives Open Sound Control (OSC) messages over UDP and uses them to control video effect parameters.

## 2. Goals

- Capture from the first available USB webcam by default.
- Start outputting video immediately on launch.
- Run as a fullscreen visual application suitable for headless/performance deployment.
- Process live video with low latency.
- Provide OSC control over all performance-facing parameters.
- Support smooth parameter interpolation using a global `slurp` parameter.
- Use a shader-based rendering pipeline where practical.
- Keep the first implementation simple, reliable, and suitable for low-spec hardware.
- Allow performance-critical limits and mappings to be adjusted via configuration file.

## 3. Non-goals for First Implementation

- No graphical user interface beyond the fullscreen video output.
- No camera selection UI.
- No timeline, preset manager, patch browser, or scene system.
- No built-in network discovery.
- No requirement for the app itself to directly manage multiple physical video outputs.
- No requirement to support non-USB cameras in the first implementation.
- No requirement to set persistent configuration values over OSC in the first implementation.

## 4. Target Platform

### 4.1 Primary Target

- Raspberry Pi
- USB UVC webcam
- Linux-based Raspberry Pi OS or equivalent
- openFrameworks C++ application
- OpenGL ES-compatible rendering path where possible

### 4.2 Secondary Target

- Orange Pi or similar ARM single-board computer
- Armbian or equivalent Linux distribution
- USB UVC webcam

### 4.3 Hardware Philosophy

The application should not be tied to a specific Raspberry Pi model. Performance settings such as resolution, frame rate, blur method, and effect limits should be configurable so the same software can be tuned for different hardware.

## 5. Runtime Behaviour

On startup, the application should:

1. Load configuration from a config file.
2. Initialize OSC receiver on the configured port, defaulting to UDP port `1111`.
3. Select the first available USB webcam.
4. Request the configured camera resolution and frame rate.
5. Open a fullscreen rendering window on display `0`.
6. Begin displaying the processed camera feed immediately, using processing textures that match the active camera resolution.
7. Listen for OSC messages from any device on the local network.

If the requested camera resolution or frame rate is unavailable, the application should fall back to the closest available camera mode where possible and log the actual mode being used.

If no camera is available, the application should display a fallback visual state, such as a black frame, and continue listening for OSC messages.

## 6. Display and Output

The application outputs video by rendering a fullscreen openFrameworks window to display `0`.

The application should always run fullscreen. Display selection is not configurable in the first implementation.

HDMI and composite output routing are handled by the operating system, hardware configuration, or boot/display configuration rather than by the application itself.

The application does not include an output configuration section in the first implementation.

The internal processing texture resolution should match the active camera resolution.

The application frame rate should match the active camera frame rate where possible.

## 7. Configuration File

The application should load a configuration file at startup. Suggested format: JSON, TOML, or YAML. JSON is acceptable for the first implementation due to ease of parsing.

Suggested file name:

```text
config.json
```

Suggested config fields:

```json
{
  "osc": {
    "port": 1111
  },
  "camera": {
    "deviceIndex": 0,
    "width": 640,
    "height": 480,
    "fps": 30
  },
  "effects": {
    "maxSlurpTimeSeconds": 5.0,
    "maxZoom": 4.0,
    "minZoom": 0.0,
    "maxBlurRadius": 24.0,
    "blurMode": "gaussian",
    "maxContrastGain": 4.0,
    "hueRotationDegrees": 360.0,
    "rotationRangeDegrees": 360.0,
    "lfoMaxSpeedDegreesPerSecond": 180.0
  },
  "performance": {
    "useSeparateBlurShader": true,
    "enableColorMix": true,
    "enableRotationLfo": true
  }
}
```

### 7.1 Future OSC Configuration

A later implementation may allow runtime configuration changes over OSC, such as camera resolution, frame rate, or output mode. These values are not required to be writable over OSC in the first implementation.

## 8. OSC Input

### 8.1 Protocol

- OSC over UDP
- Default port: `1111`
- Bind address: all interfaces, equivalent to `0.0.0.0`
- Accept OSC messages from any network device

### 8.2 Message Style

OSC addresses are flat and ungrouped for the first implementation.

All continuous performance parameters use normalized floating-point values from `0.0` to `1.0`, unless otherwise specified.

Boolean parameters use integer or float values:

- `0` = off
- `1` = on

Button-style parameters are triggered by sending `1`.

## 9. OSC Address Map

| OSC Address | Type | Range / Values | Default | Description |
|---|---:|---:|---:|---|
| `/brightness` | float | `0.0–1.0` | `0.5` | Brightness control. `0.5` neutral, `0.0` black, `1.0` white. |
| `/contrast` | float | `0.0–1.0` | `0.5` | Contrast control. `0.5` neutral, `0.0` zero contrast, `1.0` high contrast. |
| `/saturation` | float | `0.0–1.0` | `0.5` | Saturation control. `0.5` neutral, `0.0` monochrome, `1.0` highly saturated. |
| `/hue` | float | `0.0–1.0` wrapping | `0.0` | Hue rotation. Continuous wraparound. |
| `/invert` | int/float | `0` or `1` | `0` | Invert image toggle. |
| `/x` | float | `0.0–1.0` | `0.5` | Horizontal translation. `0.5` centered. |
| `/y` | float | `0.0–1.0` | `0.5` | Vertical translation. `0.5` centered. |
| `/zoom` | float | `0.0–1.0` | `0.5` | Zoom. `0.5` native size. `0.0` shrunk to nothing. `1.0` heavily zoomed. |
| `/rotate` | float | `0.0–1.0` | `0.5` | Rotation. `0.5` neutral, `0.0` -180°, `1.0` +180°. |
| `/blur` | float | `0.0–1.0` | `0.0` | Blur amount. `0.0` no blur, `1.0` maximum configured blur. |
| `/slurp` | float | `0.0–1.0` | `0.0` | Global smoothing amount for continuous parameters. |
| `/color_hue` | float | `0.0–1.0` wrapping | `0.0` | Solid color hue. `0.0` red, `1.0` wraps to red. |
| `/color_saturation` | float | `0.0–1.0` | `0.0` | Solid color saturation. `0.0` off/desaturated, `1.0` fully saturated. |
| `/color_luminance` | float | `0.0–1.0` | `0.5` | Solid color luminance. `0.0` black, `0.5` neutral midpoint, `1.0` white. |
| `/color_mix_mode` | int | `0–3` | `0` | Solid color mix mode. See enum below. |
| `/rotation_lfo_speed` | float | `0.0–1.0` | `0.5` | Optional rotation LFO speed. Values below `0.5` rotate negative, above `0.5` rotate positive. |
| `/reset` | int/float | `1` triggers | n/a | Reset all controllable parameters to defaults, using slurp for smoothed parameters. |

## 10. Color Mix Mode Enum

`/color_mix_mode` uses integer values:

| Value | Mode | Description |
|---:|---|---|
| `0` | Add | Adds the generated solid color to the video. |
| `1` | Subtract | Subtracts the generated solid color from the video. |
| `2` | Minimum | Per-channel minimum between video and solid color. |
| `3` | Maximum | Per-channel maximum between video and solid color. |

Values outside `0–3` should be clamped or ignored. Clamping is preferred for robustness.

## 11. Parameter Mapping

### 11.1 Brightness

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = full black after clamping
- `0.5` = neutral
- `1.0` = full white after clamping

Suggested shader logic:

```glsl
rgb += (brightness - 0.5) * 2.0;
rgb = clamp(rgb, 0.0, 1.0);
```

### 11.2 Contrast

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = zero contrast
- `0.5` = neutral contrast
- `1.0` = high contrast

The maximum contrast gain should be configurable.

Suggested mapping:

```text
if contrast <= 0.5:
    gain = contrast / 0.5
else:
    gain = 1.0 + ((contrast - 0.5) / 0.5) * (maxContrastGain - 1.0)
```

Suggested shader logic:

```glsl
rgb = (rgb - 0.5) * gain + 0.5;
rgb = clamp(rgb, 0.0, 1.0);
```

### 11.3 Saturation

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = grayscale
- `0.5` = neutral
- `1.0` = highly saturated

Suggested mapping:

```text
saturationGain = saturation * 2.0
```

Suggested shader logic:

```glsl
float luma = dot(rgb, vec3(0.299, 0.587, 0.114));
rgb = mix(vec3(luma), rgb, saturationGain);
rgb = clamp(rgb, 0.0, 1.0);
```

### 11.4 Hue

Input range:

```text
0.0–1.0 wrapping
```

Mapping:

- `0.0` = no hue rotation
- `1.0` = full hue rotation, visually equivalent to `0.0`

The shader should treat hue as circular/wrapping.

Suggested mapping:

```text
hueDegrees = hue * hueRotationDegrees
```

Default:

```text
hueRotationDegrees = 360.0
```

### 11.5 Invert

Input values:

```text
0 or 1
```

Mapping:

- `0` = normal image
- `1` = inverted image

Suggested shader logic:

```glsl
if (invert > 0.5) {
    rgb = 1.0 - rgb;
}
```

Invert is a toggle-style parameter and should not be smoothed by `slurp`.

### 11.6 Translation X

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = image translated one full frame left, so the right edge is just past the left edge of the output frame
- `0.5` = centered
- `1.0` = image translated one full frame right, so the left edge is just past the right edge of the output frame

Suggested mapping:

```text
xOffsetFrames = (x - 0.5) * 2.0
```

### 11.7 Translation Y

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = image translated one full frame up
- `0.5` = centered
- `1.0` = image translated one full frame down

Suggested mapping:

```text
yOffsetFrames = (y - 0.5) * 2.0
```

### 11.8 Zoom

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = image zoomed down to nothing
- `0.5` = native size
- `1.0` = heavily zoomed in

The upper zoom amount should be configurable.

Suggested mapping:

```text
if zoom <= 0.5:
    scale = zoom / 0.5
else:
    scale = 1.0 + ((zoom - 0.5) / 0.5) * (maxZoom - 1.0)
```

Default:

```text
maxZoom = 4.0
```

### 11.9 Rotation

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = -180°
- `0.5` = 0°
- `1.0` = +180°

Suggested mapping:

```text
rotationDegrees = (rotate - 0.5) * rotationRangeDegrees
```

Default:

```text
rotationRangeDegrees = 360.0
```

### 11.10 Blur

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = no blur
- `1.0` = maximum configured blur

Suggested mapping:

```text
blurRadius = blur * maxBlurRadius
```

Default:

```text
maxBlurRadius = 24.0
```

The blur implementation should be modular so that a Gaussian blur can be replaced by a lower-cost blur if required.

Supported or planned blur modes:

- `gaussian`
- `box`
- `downsample`
- `none`

### 11.11 Slurp

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = no smoothing; parameters are immediate
- `1.0` = maximum configured smoothing time

`slurp` applies to all continuous parameters except itself.

Affected parameters:

- `/brightness`
- `/contrast`
- `/saturation`
- `/hue`
- `/x`
- `/y`
- `/zoom`
- `/rotate`
- `/blur`
- `/color_hue`
- `/color_saturation`
- `/color_luminance`
- `/rotation_lfo_speed`

Unaffected parameters:

- `/slurp`
- `/invert`
- `/color_mix_mode`
- `/reset`

Reset should restore target values to defaults, but the currently displayed/smoothed values should move toward those defaults using the active `slurp` amount.

Suggested behavior:

```text
slurpTimeSeconds = slurp * maxSlurpTimeSeconds
```

When `slurpTimeSeconds` is `0`, current value immediately equals target value.

When `slurpTimeSeconds` is greater than `0`, use frame-rate-independent exponential smoothing.

Suggested update formula:

```text
alpha = 1.0 - exp(-deltaTime / slurpTimeSeconds)
current = current + (target - current) * alpha
```

For wrapping parameters such as hue, interpolation should use shortest-path circular interpolation where appropriate.

## 12. Solid Color Generator

The application should generate a solid color field from HSL-style controls:

- `/color_hue`
- `/color_saturation`
- `/color_luminance`

This color field is mixed with the processed video using `/colorMixMode`.

There is no separate color mix amount in the first implementation. The strength of the color contribution is controlled indirectly by color saturation and luminance.

### 12.1 Color Hue

Input range:

```text
0.0–1.0 wrapping
```

Mapping:

- `0.0` = red
- `1.0` = red again, wrapping around the hue wheel

### 12.2 Color Saturation

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = desaturated/off
- `1.0` = fully saturated

### 12.3 Color Luminance

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = black
- `0.5` = middle luminance
- `1.0` = white

## 13. Rotation LFO

The application may support an optional rotation LFO.

The LFO is controlled by a single speed parameter:

```text
/rotation_lfo_speed
```

Input range:

```text
0.0–1.0
```

Mapping:

- `0.0` = maximum negative rotation speed
- `0.5` = stopped
- `1.0` = maximum positive rotation speed

Suggested mapping:

```text
speedDegreesPerSecond = (rotation_lfo_speed - 0.5) * 2.0 * lfoMaxSpeedDegreesPerSecond
```

The LFO should continuously add to the base rotation value.

Suggested behavior:

```text
lfoRotationDegrees += speedDegreesPerSecond * deltaTime
finalRotationDegrees = baseRotationDegrees + lfoRotationDegrees
```

The accumulated LFO rotation may wrap to avoid unbounded growth.

Default:

```text
rotation_lfo_speed = 0.5
```

## 14. Processing Pipeline

Preferred first implementation pipeline:

```text
Camera input
→ color correction: brightness, contrast, saturation, hue, invert
→ solid color mix
→ transform: translate, zoom, rotate, rotation LFO
→ blur
→ fullscreen output
```

Blur should be placed at the end of the pipeline.

The implementation should use shaders where practical. At minimum, color correction and color mixing should be implemented in a shader. Transform may be handled through geometry/texture coordinates or shader math. Blur should be implemented as a separate shader pass so it can be swapped or disabled for performance reasons.

## 15. Default Parameter Values

| Parameter | Default |
|---|---:|
| `/brightness` | `0.5` |
| `/contrast` | `0.5` |
| `/saturation` | `0.5` |
| `/hue` | `0.0` |
| `/invert` | `0` |
| `/x` | `0.5` |
| `/y` | `0.5` |
| `/zoom` | `0.5` |
| `/rotate` | `0.5` |
| `/blur` | `0.0` |
| `/slurp` | `0.0` |
| `/color_hue` | `0.0` |
| `/color_saturation` | `0.0` |
| `/color_luminance` | `0.5` |
| `/color_mix_mode` | `0` |
| `/rotation_lfo_speed` | `0.5` |

## 16. Reset Behavior

The reset message is:

```text
/reset 1
```

When received, the application should set all target parameter values back to their defaults.

Continuous parameters should return to default using the current `slurp` setting.

Immediate/toggle parameters should reset immediately:

- `/invert` → `0`
- `/color_mix_mode` → `0`

`/slurp` itself should reset to `0.0` unless configured otherwise.

Note: because `/slurp` resets immediately to `0.0`, this would make all other parameters snap to their defaults unless reset is implemented carefully. Preferred behavior is:

1. Capture current `slurp` value.
2. Set target values for smoothed parameters to defaults.
3. Use captured `slurp` value for the reset transition.
4. Set `/slurp` to default after the smoothed reset has completed, or leave `/slurp` unchanged.

Recommended first implementation behavior:

- `/reset 1` resets all parameters to defaults.
- Smoothed parameters use the active `slurp` value during the reset.
- `/slurp` itself remains unchanged.

This preserves the intended behavior that reset can glide back to neutral when slurp is active.

## 17. Error Handling and Robustness

### 17.1 OSC Values

- Continuous OSC values should be clamped to `0.0–1.0`.
- Integer enum values should be clamped to the supported enum range.
- Unknown OSC addresses should be ignored.
- Malformed OSC messages should be ignored and optionally logged.

### 17.2 Camera Failure

If camera initialization fails:

- Display black or a diagnostic fallback frame.
- Continue running.
- Continue listening for OSC.
- Retry camera initialization only if this does not destabilize the app.

### 17.3 Shader Failure

If a shader fails to load:

- Log the error.
- Fall back to a simpler pass-through shader if possible.
- Continue displaying video if possible.

## 18. Performance Considerations

The application should prioritize stable frame rate and low latency over visual complexity.

Recommended strategies:

- Use one main color-correction shader pass.
- Keep blur as a separate optional pass.
- Allow blur to be disabled in config.
- Avoid CPU-side per-pixel processing.
- Avoid unnecessary texture readbacks.
- Use lower default resolution for low-end boards.
- Use configurable resolution and frame rate.
- Prefer simple shader math over multi-pass effects unless necessary.

## 19. Suggested Project Structure

```text
VJCamera/
  bin/
    data/
      config.json
      shaders/
        colorCorrect.frag
        transform.vert
        transform.frag
        blur_gaussian.frag
        blur_box.frag
        passthrough.frag
  src/
    main.cpp
    ofApp.h
    ofApp.cpp
    OscController.h
    OscController.cpp
    Parameter.h
    Parameter.cpp
    VideoProcessor.h
    VideoProcessor.cpp
    Config.h
    Config.cpp
```

## 20. Internal Parameter Model

Each smoothed continuous parameter should maintain:

- current value
- target value
- default value
- minimum input value
- maximum input value
- smoothing enabled flag
- wrapping flag, where needed

Example conceptual structure:

```cpp
struct Parameter {
    float current;
    float target;
    float defaultValue;
    bool smoothed;
    bool wrapping;
};
```

OSC messages update target values. The render/update loop advances current values toward targets according to `slurp`.

## 21. First Implementation Checklist

Minimum viable implementation:

- Load config file.
- Open first USB webcam.
- Open fullscreen output window.
- Receive OSC on UDP port `1111`.
- Implement flat OSC addresses.
- Implement parameter smoothing via `/slurp`.
- Implement brightness, contrast, saturation, hue, invert.
- Implement translate X/Y, zoom, rotate.
- Implement blur as separate shader pass.
- Implement solid color generation and mix mode enum.
- Implement optional rotation LFO speed.
- Implement `/reset 1`.
- Clamp and validate incoming OSC values.

## 22. Open Questions

These items may be decided later:

1. Whether `/slurp` should remain unchanged after reset or eventually return to default.
2. Whether to add OSC support for writing runtime config values.
3. Whether to add a separate color mix amount.
4. Whether to support camera hot-plugging.
5. Whether to support Raspberry Pi CSI cameras.
6. Whether to add presets.
7. Whether to expose shader selection over OSC.
8. Whether to add a diagnostic overlay for development builds.

