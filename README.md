# Fishing!

A web fishing game.

## Overview

This is a web game written in C++.

The game is built with CMake for webassembly using Emscripten.

A Podman container builds and then hosts the game with NginX.

### Building

```bash
podman build -f Containerfile.deploy -t fishing-game .
```

### Running

```bash
podman run --replace -p 8080:80 --name fishing fishing-game
```

### Setting Up DevContainer

1. Install podman on windows
2. Run
  ```
  podman machine start
  ```
3. Disable wayland (there is some error related to wsl and wayland and windows and paths https://github.com/containers/podman/issues/17986#issuecomment-2525290149)
4. Reopen in devcontainer
5. Update the cpp_properties to use `/emsdk/upstream/emscripten/emcc` and add `/emsdk/upstream/emscripten/system/include/**` to your include path