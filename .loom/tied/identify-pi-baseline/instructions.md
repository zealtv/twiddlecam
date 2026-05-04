# identify-pi-baseline

Brief: Capture the Pi baseline before installing or building anything.

Notes:
- Commands should be copied into the development notes or stitch outcome.
- Useful checks: `cat /etc/os-release`, `uname -a`, `lscpu`, `vcgencmd version`, `df -h`, `free -h`, `ip addr`.
- Note whether the session is SSH, local terminal, desktop, or kiosk-style boot.

Outcome:
- Access path: SSH session to `pi@campi.local` in tmux session `0`, window `0`, pane `0`.
- Network: `campi.local`, IPv4 `192.168.1.108` on `wlan0`; `eth0` down.
- Model: Raspberry Pi 3 Model B Plus Rev 1.4.
- OS: Debian GNU/Linux 13.4 trixie, Raspberry Pi kernel `6.12.75+rpt-rpi-v8`, `aarch64`.
- CPU: 4x Cortex-A53 cores.
- Graphics firmware: `vcgencmd version` reports Broadcom firmware from Feb 11 2026.
- Disk: root filesystem 15G total, 3.0G used, 11G available.
- Memory: 905MiB RAM, 904MiB swap; about 745MiB available at baseline.
- Camera devices exist at `/dev/video0`, `/dev/video1`, and multiple Pi media devices.
- User groups include `video`, `render`, `input`, `gpio`, `i2c`, and `spi`.
- Present tools: `vcgencmd`, `v4l2-ctl 1.30.1`, `gcc 14.2.0`, `g++ 14.2.0`, `make 4.4.1`, `pkg-config 1.8.1`.
- Missing tool: `git`; apt candidate is `1:2.47.3-0+deb13u1`.

Checklist:
- [x] Record Pi model and OS release.
- [x] Record architecture and kernel.
- [x] Record network address used for development.
- [x] Record available disk and memory.
- [x] Identify whether `vcgencmd`, `v4l2-ctl`, and build tools are present.
