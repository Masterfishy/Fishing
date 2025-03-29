# Fishing!

A web fishing game.

## Overview

This is a web game written in C++.

The game is built with CMake for webassembly using Emscripten.

A Podman container builds and then hosts the game with NginX.

### Building

```bash
podman build -f Dockerfile.dev -t fishing-game .
```

### Running

```bash
podman run --replace -p 8080:80 --name fishing fishing-game
```

