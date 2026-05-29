# Changelog

All notable changes to **CircuitGen Generator** are documented in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and releases use [Semantic Versioning](https://semver.org/) — see [Versioning.md](Versioning.md).

**Русский:** [CHANGELOG.md](../ru/CHANGELOG.md)

## [Unreleased]

### Added

- **Chisel**-based Verilog generation and CLI integration.
- API and JSON examples (`examples/`); `save_circuit_parameters_json` flag.
- Synology NAS documentation deploy from CI: shared portal, `manifest.json` schema v2, multi-version trees (`versions/main/`, `versions/<tag>/`).
- `scripts/docs/` deploy toolkit (`versions-index.sh`, `manifest-merge.sh`, `modules-registry.json`, portal UI); `scripts/ci/test_deploy_mock.sh`.
- Functionality overview in `docs/ru|en/FUNCTIONALITY.md`.
- Changelog in `docs/ru|en/CHANGELOG.md`.

### Changed

- Major CMake, multi-OS GitLab CI, Docker, and `docs/` refresh (synced with Graph/Parameters).
- **CircuitGen Graph** dependency bump (v1.5.2+); API fixes.
- Documentation: `BUILDING`, CI markdown, `NewGenerator`, README.

### Fixed

- `runGeneration`: callback invoked on all code paths.
- Genetic/state-machine generator: merge init/transition DFFs.
- CI: Java/Chisel sanitize, LaTeX/PDF, NAS Auth v3; manifest merge across parallel module pipelines; portal language toggle without duplicate cards; `versions.json` from all staged channels.

---

## [1.3.0] - 2024-08-02

### Added

- **easylogging++** integration; tests prepared for structured logging.

### Changed

- CMake optimizations; manual workflow on any branch.
- Project version bump.

### Fixed

- `empty_project`; format command; redundant logs.

---

## [1.2.0] - 2024-07-01

### Changed

- **clang**, codecov, Graph version updates.

### Fixed

- Parallel generation runs; tests.

---

## [1.1.0] - 2024-06-09

### Added

- Expanded generator set and batch generation scenarios.
- Documentation pipeline improvements (Doxygen/HTML).

### Changed

- Large CI, CMake, and project structure update.

### Fixed

- Numerous generator, test, and documentation fixes.

---

## [1.0.1] - 2024-04-05

### Changed

- GitHub/GitLab CI; Doxygen (`Doxyfile.in`); README.

### Fixed

- Build and generation bugs.

---

## [1.0.0-alpha] - 2024-04-02

### Added

- CMake package consumption (`FetchContent` / find_package).
- CMake package example; `BUILDING.md` updates.

### Changed

- README and install layout.

---

## [0.1.4-alpha] - 2024-02-13

### Added

- `min_level`; memory optimizations.

### Fixed

- RandLevel and related algorithm bugs.

---

## [0.1.3-alpha] - 2024-02-02

### Changed

- `CMakeLists.txt`.

---

## [0.1.2-alpha] - 2024-01-29

### Added

- **bench** format; circuit I/O validation.

### Changed

- README; RandLevel.

---

## [0.1.1-alpha] - 2024-01-26

### Added

- JSON samples; publications for generation methods.

### Changed

- `generatorAPI`; code comments.

### Fixed

- API errors.

---

## [0.1.0-alpha] - 2024-01-25

> Git tag: `v0.1.0-aplpha` (typo in tag name).

### Added

- First alpha of the combinational circuit generator: JSON/API, RandLevel and related algorithms.
- CMake build, reliability calculation, GCC 9.4 adaptation.

### Changed

- CMake and test-generation refactoring.

---

## How to update

When releasing `vX.Y.Z`:

1. Move **Unreleased** items into `## [X.Y.Z] - YYYY-MM-DD`.
2. Tag: `git tag vX.Y.Z`.
3. Version hint: `bash scripts/release/suggest-next-version.sh`.

Keep **both** `docs/ru/CHANGELOG.md` and `docs/en/CHANGELOG.md` in sync.
