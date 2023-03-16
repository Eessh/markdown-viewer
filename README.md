# Markdown Viewer

A simple, lightweight markdown viewer.

## Building
- Linux
  - Install [SDL2](https://www.libsdl.org/) development libraries.
    - Arch Linux
    ```bash
    sudo pacman -S sdl2
    ```
    - Ubuntu/Debian based distro
    ```bash
    sudo apt install libsdl2-dev
    ```
    - Fedora
    ```bash
    sudo dnf install SDL2-devel
    ```
  - Install [Premake5](https://premake.github.io/)
  - Making premake5 available system wide
    ```bash
    cd <dir in which you extracted premake5>
    sudo mv ./premake5 /usr/bin/
    ```
  - Making scripts executable
    ```bash
    chmod +x ./scripts/linux/*
    ```
  - Generate Makefiles
    ```bash
    ./scripts/linux/gen_makefiles.sh
    ```
  - Build `DEBUG` version
    ```bash
    ./scripts/linux/build_debug.sh
    ```
  - Build `RELEASE` version
    ```bash
    ./scripts/linux/build_release.sh
    ```
  - Run `DEBUG` version
    ```bash
    ./scripts/linux/run_debug.sh
    ```
  - Run `RELEASE` version
    ```bash
    ./scripts/linux/run_release.sh
    ```
  - Clean
    ```bash
    ./scripts/linux/clean.sh
    ```
- macOS
  - Install [SDL2](https://www.libsdl.org/) development libraries.
  - Install [Premake5](https://premake.github.io/)
  - Making scripts executable
    ```bash
    chmod +x ./scripts/macos/*
    ```
  - Generate Makefiles
    ```bash
    ./scripts/macos/gen_makefiles.sh
    ```
  - Build `DEBUG` version
    ```bash
    ./scripts/macos/build_debug.sh
    ```
  - Build `RELEASE` version
    ```bash
    ./scripts/macos/build_release.sh
    ```
  - Run `DEBUG` version
    ```bash
    ./scripts/macos/run_debug.sh
    ```
  - Run `RELEASE` version
    ```bash
    ./scripts/macos/run_release.sh
    ```
  - Clean
    ```bash
    ./scripts/macos/clean.sh
    ```
- Windows
  - Install [Premake5](https://premake.github.io/)
  - Move `premake5.exe` to project root folder.
  - Generate Makefiles
    ```powershell
    .\scripts\widows\gen_makefiles.bat
    ```
  - Build `DEBUG` version
    ```powershell
    .\scripts\windows\build_debug.bat
    ```
  - Build `RELEASE` version
    ```powershell
    .\scripts\widows\build_release.bat
    ```
  - Run `DEBUG` version
    ```powershell
    .\scripts\windows\run_debug.bat
    ```
  - Run `RELEASE` version
    ```powershell
    .\scripts\windows\run_release.bat
    ```
  - Clean
    ```powershell
    .\scripts\windows\clean.bat
    ```
