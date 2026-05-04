# install-openframeworks-deps

Brief: Install the minimum Pi dependencies required to build openFrameworks apps.

Notes:
- Prefer official openFrameworks Linux/Raspberry Pi setup scripts where appropriate.
- Record exact versions and commands so the setup can be repeated.
- Watch for graphics stack differences between Raspberry Pi OS releases.

Outcome:
- Installed `git` and verified `git version 2.47.3`.
- Downloaded openFrameworks 0.12.1 for Linux aarch64 from the official GitHub release:
  `https://github.com/openframeworks/openFrameworks/releases/download/0.12.1/of_v0.12.1_linuxaarch64_release.tar.gz`
- Unpacked it to `/home/pi/openFrameworks`.
- The user-provided `linux64_gcc6` archive was not used because this Pi is `aarch64`; `linux64_gcc6` is for x86_64 Linux.
- Ran `/home/pi/openFrameworks/scripts/linux/debian/install_dependencies.sh`.
- The stock script failed on Debian 13 trixie because `libgconf-2-4` is no longer available.
- Patched the unpacked OF script on the Pi:
  - backed up original as `install_dependencies.sh.orig`
  - removed `libgconf-2-4`
  - added `-y` to `apt-get install` commands
- Reran the patched script successfully. It installed the broad OF dependency set and updated `ofxOpenCV` to use OpenCV 4.
- Verified pkg-config versions:
  - OpenCV `4.10.0`
  - GStreamer `1.26.2`
  - GLFW `3.4.0`
- Disk after dependency install: root filesystem 15G total, 5.5G used, 8.0G available.
- Actual empty app path in this OF package is `/home/pi/openFrameworks/apps/myApps/emptyExample`.
- A make dry-run reached the OF project dependency stage, then stopped because the OF core library was not built yet.
- Built the openFrameworks core library explicitly with:
  `make Release -C ~/openFrameworks/libs/openFrameworksCompiled/project -j1`
- Used `-j1` because the target is a Raspberry Pi 3B+ with limited RAM.
- Verified `/home/pi/openFrameworks/libs/openFrameworksCompiled/lib/linuxaarch64/libopenFrameworks.a` exists, size about 9.6M.

Checklist:
- [x] Install compiler, make, git, pkg-config, OpenGL/GLES, video, and audio dependencies.
- [x] Install openFrameworks or document its existing location.
- [x] Run OF dependency/install scripts if needed.
- [x] Record any manual fixes.
- [x] Confirm an example project can start compiling.
