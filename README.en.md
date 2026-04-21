# Combinational circuit generator

**Language:** [Русский](README.md) | English  
**Documentation:** [Russian](docs/ru/README.md) | [English](docs/en/README.md)  
**Versioning (SemVer):** [Russian](docs/ru/Versioning.md) | [English](docs/en/Versioning.md)  
**Contributing:** [Russian](docs/ru/CONTRIBUTING.md) | [English](docs/en/CONTRIBUTING.md)  
**Merge requests:** [Russian](docs/ru/MergeRequests.md) | [English](docs/en/MergeRequests.md)

<a name="content_en"></a>

![License: MIT](https://img.shields.io/github/license/vvzunin/CircuitGen_Generator)
![GitHub forks](https://img.shields.io/github/forks/vvzunin/CircuitGen_Generator)
![GitHub Repo stars](https://img.shields.io/github/stars/vvzunin/CircuitGen_Generator)
![GitHub watchers](https://img.shields.io/github/watchers/vvzunin/CircuitGen_Generator)

[![codecov](https://codecov.io/gh/vvzunin/CircuitGen_Generator/graph/badge.svg?token=U88U82QFX8)](https://codecov.io/gh/vvzunin/CircuitGen_Generator)
![GitHub Release](https://img.shields.io/github/v/release/vvzunin/CircuitGen_Generator)
![GitHub Release Date](https://img.shields.io/github/release-date/vvzunin/CircuitGen_Generator)

![GitHub commit activity](https://img.shields.io/github/commit-activity/m/vvzunin/CircuitGen_Generator)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/vvzunin/CircuitGen_Generator/latest)
![GitHub last commit](https://img.shields.io/github/last-commit/vvzunin/CircuitGen_Generator)

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/vvzunin/CircuitGen_Generator)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr/vvzunin/CircuitGen_Generator)

![Alt](https://repobeats.axiom.co/api/embed/22944c53bda053bd3f0899dc855632dc9b8c38c2.svg "Repobeats analytics image")

**Contents:**

- [Developer workflow](#hacking)
- [Adding a new generator](#generator_add)
- [Building](#generator_build)
- [Command-line generation](#generator_run_one_json)
- [JSON files](#JSON_files)
- [Output directory prefixes](#prefix)
- [License](#license)

> [!IMPORTANT]  
> Main project repository: https://github.com/vvzunin/CircuitGen

The project builds on Linux, Windows, and macOS using CMake presets.
Development and CI are primarily validated on Ubuntu (including WSL).
A developer handbook is available [here](https://drive.google.com/file/d/1eKWMpF0Ig5r5ZI81dJjRoibctzezNE-D/view?usp=sharing).

## Installing dependencies

Package lists and extra steps (Kitware CMake when needed, pinned **clang-format**, **lcov** 2+ on Ubuntu 22.04, Doxygen, TeX for docs, etc.) live under **[`scripts/setup/`](scripts/setup/)** — one script per supported OS, for example:

- [`install-deps-ubuntu-22.04.sh`](scripts/setup/install-deps-ubuntu-22.04.sh)
- [`install-deps-ubuntu-24.04.sh`](scripts/setup/install-deps-ubuntu-24.04.sh)
- [`install-deps-debian-13.sh`](scripts/setup/install-deps-debian-13.sh)
- [`install-deps-fedora-42.sh`](scripts/setup/install-deps-fedora-42.sh) / [`install-deps-fedora-43.sh`](scripts/setup/install-deps-fedora-43.sh)

Run as root: `sudo bash scripts/setup/install-deps-ubuntu-24.04.sh`.

More detail: [BUILDING.md](docs/en/BUILDING.md), [SCRIPTS.md](docs/en/SCRIPTS.md).

## Developer workflow
<a name="hacking"></a>

Tips for building and testing as a developer or contributor: [HACKING.md](docs/en/HACKING.md).

[&#8593; Contents](#content_en)

## Adding a new generator
<a name="generator_add"></a>

See the dedicated guide: [NewGenerator.md](docs/en/NewGenerator.md).

[&#8593; Contents](#content_en)

## Building
<a name="generator_build"></a>

From the repository root:

```
bash scripts/dev/build-debug.sh
```

Coverage:

```
bash scripts/dev/coverage.sh
```

Release (no tests):

```
bash scripts/release/build.sh
```

Release with tests (CI parity):

```
bash scripts/release/test.sh
```

Local dev containers (similar to CI):

```
bash scripts/docker/build-images.sh
```

By default this builds `circuitgen/generator/ubuntu-24.04/ci:local`,
`circuitgen/generator/ubuntu-24.04/dev:local`, and
`circuitgen/generator/ubuntu-24.04/release:local` (see `scripts/docker/docker-paths.sh`).

Pick another OS with `TARGET_OS` or `DOCKER_CI_SYSTEM`:

```
TARGET_OS=fedora-42 bash scripts/docker/build-images.sh
```

Override tags and registry prefix:

```
CI_IMAGE_TAG=my-ci DEV_IMAGE_TAG=my-dev RELEASE_IMAGE_TAG=my-release DOCKER_CI_SYSTEM=ubuntu:24.04 bash scripts/docker/build-images.sh
```

Details: [BUILDING.md](docs/en/BUILDING.md), scripts: [SCRIPTS.md](docs/en/SCRIPTS.md).

[&#8593; Contents](#content_en)

## Command-line generation
<a name="generator_run_one_json"></a>

Prepare a JSON file with generation parameters, then run:

```
build/CircuitGenGenerator --json_path <path_to_json>
```

[&#8593; Contents](#content_en)

## JSON files
<a name="JSON_files"></a>

Command-line generation requires a JSON configuration file.

Structure: [json.md](docs/en/json.md).

[&#8593; Contents](#content_en)

## Output directory prefixes
<a name="prefix"></a>

Each generator creates output folders with a generator-specific prefix.

Prefix list: [GeneratorsPrefixes.md](docs/en/GeneratorsPrefixes.md).

[&#8593; Contents](#content_en)

# License
<a name="license"></a>

See [LICENSE](LICENSE).

[&#8593; Contents](#content_en)
