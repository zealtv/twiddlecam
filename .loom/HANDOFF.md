# Twiddlecam handoff

Date: 2026-05-04

## Where things live

- Local planning repo: `/Users/bob/repos/twiddlecam`
- Live Raspberry Pi app path: `/home/pi/openFrameworks/apps/myApps/VJCamera`
- Repo snapshot of the live Pi app: `pi-app-snapshot/`
- Loom plan/state: `.loom/`
- Original product spec: `vj_camera_software_spec_v_1.md`

`pi-app-snapshot/` is a lightweight source snapshot copied from the Pi. It intentionally excludes build products and the full openFrameworks tree.

## Pi target

- Host/user used during bringup: `pi@campi.local`
- Hardware: Raspberry Pi 3 Model B Plus Rev 1.4
- OS: Debian GNU/Linux 13.4 trixie, aarch64
- Kernel observed: `6.12.75+rpt-rpi-v8`
- openFrameworks: 0.12.1 aarch64 at `/home/pi/openFrameworks`
- App binary on Pi: `/home/pi/openFrameworks/apps/myApps/VJCamera/bin/VJCamera`

The original x86_64 OF archive was wrong for this target. The working OF package was:

```sh
https://github.com/openframeworks/openFrameworks/releases/download/0.12.1/of_v0.12.1_linuxaarch64_release.tar.gz
```

## Display and launch

Do not expect the app to launch correctly from a plain SSH shell. Direct launch produced GLFW platform detection errors because there was no active display platform in that environment.

The known working path is to launch on HDMI through VT2 with `openvt` and `startx`:

```sh
cd /home/pi/openFrameworks/apps/myApps/VJCamera/bin
sudo openvt -c 2 -f -s -- sudo -u pi sh -lc 'cd /home/pi/openFrameworks/apps/myApps/VJCamera/bin && XDG_RUNTIME_DIR=/run/user/1000 startx ./VJCamera -- :0 vt2 > /home/pi/vjcamera.log 2>&1'
```

Before relaunching, stop the previous app/X server:

```sh
killall VJCamera 2>/dev/null
sudo killall Xorg 2>/dev/null
```

The Pi was configured so this launch path works after enabling HDMI console autologin and allowing X to start from this route.

## Current app state

The app has these modules:

- `Config`
- `Parameter`
- `OscController` scaffold
- `VideoProcessor`

Current camera defaults:

- `camera.pipelineMode`: `yuy2_low_latency`
- `camera.width`: `640`
- `camera.height`: `480`
- `camera.fps`: `30`
- `camera.forceFallback`: `false`

Working camera pipelines:

- `mjpeg_hd`: `/dev/video0` MJPEG `1280x720@30`, works but high latency.
- `yuy2_low_latency`: `/dev/video0` raw `YUY2`, verified at `640x480@30` and `320x240@30`.

The selected Pi 3B+ default is `yuy2_low_latency` at `640x480@30`. It improves latency versus MJPEG, but user-estimated latency is still roughly 200 ms. Dropping to `320x240@30` did not remove the perceptible delay.

## Loom state

Use `.loom/loom.sh status` to inspect the work queue.

Tied/completed work includes:

- Pi bringup and baseline identification
- openFrameworks install/build proof
- VJCamera scaffold
- camera capture and fallback state
- USB camera mode enumeration
- low-latency YUY2 mode

Ready root threads include:

- `deployment-runtime`
- `osc-parameter-core`
- `shader-pipeline`
- `measure-camera-latency`
- `evaluate-pi4-csi-libcamera`

Continue the established workflow: read the stitch to the user before implementing it, claim it, work through it, then tie it or add follow-up stitches.

## Performance notes

The next useful performance work is measurement, not another blind pipeline tweak. `measure-camera-latency` should quantify end-to-end latency and capture CPU/FPS/dropped-frame data.

CSI/libcamera may be better, especially on a Pi 4, but it is a separate capture stack. Track that under `evaluate-pi4-csi-libcamera`.
