# Building with CMake

## Build

For day-to-day work, use presets from `CMakePresets.json` and `CMakeUserPresets.json`.
`CMakeUserPresets.json` is local (listed in `.gitignore`); after cloning, create it from the template:

```sh
cp CMakeUserPresets.json.example CMakeUserPresets.json
```

The project defaults to the `Ninja` generator.

### CMake presets (reference)

This repository uses [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html): schema **version 6** and `cmakeMinimumRequired` **3.26** (see `CMakePresets.json` in the repo root).

| File | Role |
|------|------|
| `CMakePresets.json` | Committed presets: **release**, **release-ci**, **release-examples**, CI profiles (**ci-ubuntu**, **ci-coverage**, **ci-sanitize**, **ci-static-analysis**, …), **ci-examples-dev**, plus hidden presets (**dev-mode**, compiler flag bundles, Ninja/C++17 bases). |
| `CMakeUserPresets.json` | **Local only** (gitignored). After clone: `cp CMakeUserPresets.json.example CMakeUserPresets.json`. Defines **dev**, **coverage**, **dev-msvc**, … and `include`s this repo’s `CMakePresets.json`. |

Configure, build, and test a typical **Debug** tree:

```sh
cmake --preset=dev
cmake --build --preset=dev -j"$(nproc)"
ctest --preset=dev
```

**Release + tests** using only committed presets (CI parity, no `CMakeUserPresets.json`):

```sh
cmake --preset=release-ci
cmake --build --preset=release-ci -j"$(nproc)"
ctest --preset=release-ci
```

Run `cmake --list-presets` to see every configure preset visible from your working copy.

**Cross-repository reference:** developer/examples toggles differ only by cache variable names (set through the hidden **dev-mode** bundle used by `dev` / many CI presets):

| Repository | Developer mode | Examples |
|------------|-----------------|----------|
| Generator | `CircuitGenGenerator_DEVELOPER_MODE` | `CircuitGenGenerator_BUILD_EXAMPLES` |
| Graph | `CircuitGenGraph_DEVELOPER_MODE` | `CircuitGenGraph_BUILD_EXAMPLES` |
| Parameters | `OptimizationsVerilogLib_DEVELOPER_MODE` | `optimizationsveriloglib_BUILD_EXAMPLES` |

### CMake: adding new C++ sources

Sources are grouped into **libraries** declared beside the code; parents use `add_subdirectory`.

1. **Directory** — place files under `src/` (and public headers under `include/...` when exporting an API).
2. **Register** — from the parent `CMakeLists.txt`, `add_subdirectory(<subdir>)` if you added a new folder.
3. **Leaf `CMakeLists.txt`** — typical internal library skeleton:

   ```cmake
   add_library(myLeaf STATIC MyLeaf.cpp)
   target_include_directories(myLeaf PUBLIC
     $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
   )
   target_link_libraries(myLeaf PUBLIC …)  # existing targets your code uses
   add_folders(MyLeaf)  # optional IDE grouping (cmake/folders.cmake)
   ```

4. **Wire upward** — executables or larger libraries that call your code must `target_link_libraries(... myLeaf ...)`.
5. **Reconfigure** — any `CMakeLists.txt` edit requires a fresh CMake run (`cmake --preset=dev` or equivalent).

**Repository-specific layout hints**

- **Generator:** many features are small static libraries under `src/generators/simple/<name>/CMakeLists.txt`; see `src/generators/simple/simple/CMakeLists.txt` for a canonical pattern. Parents under `src/generators/simple/CMakeLists.txt` chain `add_subdirectory` calls.
- **Graph:** the primary `CircuitGenGraph` target lists `.cpp` files in `src/CMakeLists.txt` (`SOURCES`, `LIBS`) and public headers in `include/CircuitGenGraph/` (`PUBLIC_HEADER` / install metadata). Append new translation units and headers there when you extend the core library.
- **Parameters:** the main library and OpenLane CLI live in `src/CMakeLists.txt` (`SOURCES` for `CircuitGenParameters`, executable target **`CircuitGenParameters_exe`** with runtime name **`CircuitGenParameters`** — same pattern as `CircuitGenGenerator_exe` / `CircuitGenGenerator`; entry source `CircuitGenToOpenLane.cpp`; `OptimizationsVerilogLib::…` aliases). Enable `add_subdirectory(examples)` with `-D optimizationsveriloglib_BUILD_EXAMPLES=ON` at the top level; extend `SOURCES` or add another `add_library` next to existing patterns when you add modules.

Common workflows:

```sh
# Simple local Debug build
bash scripts/dev/build-debug.sh

# Debug build with tests
cmake --preset=dev
cmake --build --preset=dev
ctest --preset=dev

# Local coverage
bash scripts/dev/coverage.sh

# Release build (no tests)
bash scripts/release/build.sh

# Release build for CI (with tests)
bash scripts/release/test.sh

# Build examples (Debug via dev preset, Release via release-examples)
bash scripts/dev/build-examples.sh
bash scripts/release/build-examples.sh

# Install release artifacts
bash scripts/release/install.sh
```

### Examples (`examples/`)

The `examples/` tree is built only when **`CircuitGenGenerator_BUILD_EXAMPLES=ON`**. The **dev** preset (see `CMakeUserPresets.json.example`) and **`ci-examples-dev`** in `CMakePresets.json` enable this via **dev-mode**. For **Release**, examples are off by default; use the **`release-examples`** preset or pass `-D CircuitGenGenerator_BUILD_EXAMPLES=ON` at configure time.

The **`run-examples`** target builds all example executables and runs them in sequence (see `examples/CMakeLists.txt`).

**Locally — dev (Debug, `dev` preset):**

```sh
cp CMakeUserPresets.json.example CMakeUserPresets.json   # once after clone
bash scripts/dev/build-examples.sh
```

Equivalent to: `bash scripts/dev/build-debug.sh`, then `cmake --build build/dev --target run-examples`.

**Locally — Release with examples:**

```sh
bash scripts/release/build-examples.sh
```

Manual equivalent:

```sh
cmake --preset=release-examples
cmake --build --preset=release-examples -j "$(nproc)"
cmake --build --preset=release-examples --target run-examples -j "$(nproc)"
```

**Without helper scripts (presets from `CMakePresets.json` only):**

```sh
# Debug + examples (dev-like; handy in CI without CMakeUserPresets)
cmake --preset=ci-examples-dev
cmake --build --preset=ci-examples-dev -j "$(nproc)"
cmake --build --preset=ci-examples-dev --target run-examples -j "$(nproc)"

# Release + examples
cmake --preset=release-examples
cmake --build --preset=release-examples -j "$(nproc)"
cmake --build --preset=release-examples --target run-examples -j "$(nproc)"
```

JSON files under `examples/json/` are inputs for `CircuitGenGenerator::runGenerationFromJson`. The C++ example targets include **`empty_example`** (smoke test), **`example_print_version`**, JSON runners **`example_run_comparison_json`**, **`example_run_truth_table_json`**, and **`example_run_parity_json`** (each compiles `example_run_preset_json.cpp` with a compile-time JSON path via `add_json_example`), plus **`example_run_json_for_graph`** (`runGenerationFromJsonForGraph`, `add_for_graph_example`). See `examples/CMakeLists.txt`.

### Building with MSVC

MSVC does not enable all strict diagnostics by default. This repo provides a `dev-msvc` preset in `CMakeUserPresets.json` that inherits `flags-msvc` from [CMakePresets.json](../../CMakePresets.json):

```sh
cmake --preset=dev-msvc
cmake --build build/dev-msvc
ctest --test-dir build/dev-msvc --output-on-failure --no-tests=error
```

### Building on Apple Silicon

CMake supports Apple Silicon starting with 3.20.1. Install the [latest CMake][1].

## Install

No special install flags are required. Build the project first using the commands above.

You need CMake 3.15 or newer for [`cmake --install`][2].

Install release artifacts:

```sh
cmake --install build/release
```

## Local dev container

To build a development environment similar to CI:

```sh
bash scripts/docker/build-images.sh
```

This builds a local base CI image, then dev and release images via
`dockerfile/Dockerfile.dev` and `dockerfile/Dockerfile.release`.
You can also build images individually:

```sh
bash scripts/docker/build-ci-image.sh
bash scripts/docker/build-dev-only-image.sh
bash scripts/docker/build-release-only-image.sh
```

See [SCRIPTS.md](SCRIPTS.md) for details on these scripts.

## Documentation (Doxygen + m.css + PDF)

Generate docs with:

```sh
bash scripts/ci/docs.sh
```

Outputs (default: **English and Russian** in parallel trees):

- `build/docs/html/en`, `build/docs/html/ru` — HTML via `m.css`;
- `build/docs/xml/en`, `build/docs/xml/ru` — Doxygen XML;
- `build/docs/latex/en`, `build/docs/latex/ru` — LaTeX sources;
- `build/docs/pdf/en`, `build/docs/pdf/ru` — final PDF (`CircuitGenGenerator.pdf` in each folder; Doxygen still builds `latex/refman.pdf`, then CMake copies it).

By default, `scripts/ci/docs.sh` and `scripts/dev/build-docs.sh` use `DOXYGEN_LANG_VARIANTS="en=english;ru=russian"` (see `scripts/docs/build-doxygen-lang-variants.sh`). To build **only one** language:

```sh
DOXYGEN_LANG_VARIANTS="en=english" bash scripts/ci/docs.sh
```

For each variant, Doxygen **`OUTPUT_LANGUAGE`** (labels in HTML, LaTeX, search UI) matches that variant: `ru=russian` uses Russian, `en=english` uses English. This is configured in `cmake/docs-ci.cmake` together with m.css `conf.py` navbar strings.

**Local** multi-language output matches CI but under `build/dev/docs/.../{en,ru}/`: run **`bash scripts/dev/build-docs.sh`** (configures the `dev` preset for `compile_commands.json`, then runs the same generator as CI).

Optional: with **`BUILD_MCSS_DOCS=ON`**, the CMake target **`docs`** (`cmake/docs.cmake`) builds **one** language at a time into `build/dev/docs/html` (no `en`/`ru` subfolders), controlled by the cache variable **`DOXYGEN_DOCUMENTATION_LANGUAGE`** (`english` or `russian`). Reconfigure after changing it.

PDF needs a LaTeX toolchain (`pdflatex`, `makeindex`), installed by `scripts/setup/install-deps-*.sh` and in the `dockerfile/Dockerfile.ci` image.
Graphviz (`dot`) is enabled automatically in CMake (`HAVE_DOT` / `DOT_PATH` when `dot` is available).

The default two-pass build (`en=english` and `ru=russian`) emits one language’s conditional text per folder. To enable **both** Doxygen sections in **one** output tree, use a variant whose section list contains both words, for example:

```sh
DOXYGEN_LANG_VARIANTS="all=english russian" bash scripts/ci/docs.sh
```

That writes under `build/docs/html/all/` (and matching `xml` / `latex` / `pdf`).

Run pre-push checks in the dev image:

```sh
bash scripts/dev/pre-push-docker.sh
```

## Running CI steps locally

GitLab CI invokes `scripts/ci/` scripts instead of long inline commands in `.gitlab-ci.yml`.
That keeps CI maintainable and reproducible locally:

```sh
bash scripts/ci/lint.sh
bash scripts/ci/static-analysis.sh
bash scripts/ci/sanitize.sh
bash scripts/ci/coverage.sh
bash scripts/ci/tests.sh
bash scripts/ci/examples.sh
bash scripts/ci/docs.sh
```

Unified local runner:

```sh
# On the host
CI_RUNNER=local bash scripts/ci/run-task.sh lint

# Inside a local Docker CI image
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-task.sh coverage

# Full CI pipeline
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-all.sh
```

## OS coverage in CI

Supported OS slugs live in **`scripts/config/supported-os.sh`**. Marked **per-OS CI job** blocks in **`.gitlab-ci.yml`** are **generated** by **`scripts/ci/generate-gitlab-os-matrix.sh`** (`--write` after editing the OS list). The **`gitlab-os-matrix-check`** job (stage `validate`) runs **`--check`**: if the committed YAML does not match the generator, the pipeline fails.

The `os-system-validation-*` stage behaves differently per branch:

- on `main`, the full supported-OS matrix runs;
- on other branches, only `ubuntu-24.04` runs (the slug must match `DEFAULT_TARGET_OS_SLUG` in `supported-os.sh` if you change the default).

For each selected system, CI:

- builds a Docker image `.../os-<target>:<tag>`;
- pushes it to the registry;
- runs `scripts/ci/run-all.sh` inside (`lint -> static-analysis -> sanitize -> coverage -> tests -> examples -> docs`), validating the full compile/test/docs path.

See `scripts/config/supported-os.sh` (or the generated matrix markers in `.gitlab-ci.yml`) for the current slug list.

For a checklist when adding a new OS, see **“Practice when adding a new OS”** in [SCRIPTS.md](SCRIPTS.md).

## CI / dev / release Docker images per OS

The `docker` stage runs one `docker-images-<slug>` job per supported OS; each builds and publishes `ci`, `dev`, and `release` images for that OS.
The `release` image is built from `dockerfile/Dockerfile.release` on a minimal base (runtime toolchain only), without the full dev/doc stack from CI.
Image name patterns like `.../<slug>/ci:<tag>` are documented in `scripts/config/supported-os.sh` (slug matches `IMAGE_OS_SUFFIX` suffixes in CI).

### CMake package

This project exports a CMake package consumable via [`find_package`][3]:

* Package name: `CircuitGenGenerator`
* Target name: `CircuitGenGenerator::CircuitGenGenerator`

Example `FetchContent`:

```cmake
FetchContent_Declare(
  CircuitGen_Generator
  GIT_REPOSITORY https://github.com/vvzunin/CircuitGen_Generator
  GIT_TAG v1.0.0-alpha
)
FetchContent_MakeAvailable(CircuitGen_Generator)
```

> [!CAUTION]
> Pick the latest released `GIT_TAG` for real use.


Link the library:

```cmake
target_link_libraries(
    app PRIVATE
    CircuitGenGenerator::CircuitGenGenerator
)
```

### API overview

Include `CircuitGenGenerator.hpp`:

```cpp
#include <CircuitGenGenerator/CircuitGenGenerator.hpp>
```

#### `runGenerationFromJson`

Takes a path to a JSON file. Returns nothing.

#### `runGenerationFromJsonForGraph`

Same JSON input. Returns `std::vector<std::pair<std::string, std::vector<GraphPtr>>>` (alias `ResultGraph`). The first element of each pair is the folder with generated Verilog; the second is the list of graphs for that path. One vector element is produced per top-level JSON object in the file (the implementation invokes the same generation path as `runGenerationFromJson`, collecting graphs instead of only writing files).

#### `runGenerationFromJsonForPath`

Same JSON input. Returns `std::vector<std::pair<std::string, std::vector<std::string>>>`: graph names used as folder names for Verilog output and as file names.

### Note to packagers

When this project is the top-level project, `CMAKE_INSTALL_INCLUDEDIR` is not plain `include`, to avoid accidentally pulling unrelated headers from a shared install prefix. See [install-rules.cmake](../../cmake/install-rules.cmake) for the full install rules.

**Русский:** [Сборка](../ru/BUILDING.md)

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/command/find_package.html
