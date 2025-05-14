# NoiseNinja - Noise Cancelling Audio Plugin

A VST3 plugin implementing noise cancellation with three adjustable suppression levels.

## Features
- Three noise suppression levels: Mild, Moderate, and Aggressive
- Cross-platform compatibility (VST3)
- Preset management for different use-cases

## Build Instructions
### Dependencies
- CMake 3.25+
- VST3 SDK/JUCE framework
- Compiler with C++20 support

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

##### Optional plugin install path
```bash
mkdir build && cd build
cmake .. -DVST3_INSTALL_DIR=$HOME/path/to/dir
cmake --build .
```

## Commit semantics

| Prefix    | Scope                          |
|-----------|--------------------------------|
| `CMAKE`   | Build system changes           |
| `GIT`     | Repository management          |
| `CORE`    | Core audio processing logic    |
| `UI`      | User interface components      |
| `DOCS`    | Documentation updates          |
| `TEST`    | Testing-related changes        |
| `PLUGIN`  | Logic that isn't directly related to the UI or  audio functionality|
| `BUILD`   | Build scripts/CI pipelines     |
