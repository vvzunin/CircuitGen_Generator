# CMake build flags

This document describes the main flags used to build this project. There are two broad categories. *Built-in* flags are standard CMake options that matter for this project. *Project* flags are added by the developers. **Any new CMake option should be documented here.**

## Built-in flags

### `CMAKE_BUILD_TYPE`

Selects the build type: `Release` or `Debug`. The default is `Debug`, which enables debugging tools (including full `gdb` debugging).

`Release` uses `-O3`, which makes debugging impractical but improves runtime performance (on the order of ~5%).

## Project flags

### `LOCAL_BUILD`

Path to a local checkout of the `OrientedGraph` repository. Use this to test graph changes without pushing and without changing the `FetchContent_Declare` tag in `CMakeLists.txt`. Pass the absolute path to the graph directory, for example:

```text
cmake -S . -B build -G Ninja -DLOCAL_BUILD=/home/user/CircuitGen_Graph
```

### `CircuitGenGenerator_DEVELOPER_MODE`

Enables tests and other developer targets. Values: `OFF` (default) / `ON`. Turned on automatically when using the `dev` preset.

**Русский:** [Описание флагов CMake](../ru/CmakeFlags.md)
