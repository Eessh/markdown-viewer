# Markdown Viewer

A simple, lightweight markdown viewer.

## Building
- Linux
  - Install [Premake5](https://premake.github.io/)
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
  - Generate Makefiles
    ```bash
    ./scripts/widows/gen_makefiles.bat
    ```
  - Build `DEBUG` version
    ```bash
    ./scripts/windows/build_debug.bat
    ```
  - Build `RELEASE` version
    ```bash
    ./scripts/widows/build_release.bat
    ```
  - Run `DEBUG` version
    ```bash
    ./scripts/windows/run_debug.bat
    ```
  - Run `RELEASE` version
    ```bash
    ./scripts/windows/run_release.bat
    ```
  - Clean
    ```bash
    ./scripts/windows/clean.bat
    ```
