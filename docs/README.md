# Documentation hub

The [repository root README](../README.md) is the project landing page (overview, build, links). This file is only the **documentation tree** entry point.

- [Русский — полное оглавление](ru/README.md)
- [English — full index](en/README.md)

Published API reference (HTML + PDF, RU/EN) after CI `docs` job on `main` / tags:

- Portal: [https://vvzunin.me/docs/CircuitGen/](https://vvzunin.me/docs/CircuitGen/)
- This module: `modules/generator/` (see [scripts/docs/DEPLOY.md](../scripts/docs/DEPLOY.md))

CI and `scripts/ci` (kept in sync across Parameters / Graph / Generator):

- [CI pipeline (RU)](ru/CI_PIPELINE.md) · [CI pipeline (EN)](en/CI_PIPELINE.md)
- [CI scripts reference (RU)](ru/CI_SCRIPTS.md) · [CI scripts reference (EN)](en/CI_SCRIPTS.md) — including Windows runner maintenance (`docker-prune-keep-bases.ps1`, §7 / anchor `docker-prune-runner-windows`)

CMake presets, CI-parity build commands, and **how to add new sources / `CMakeLists.txt` targets** (same structure in **en**/**ru** across all three repos):

- [BUILDING (EN)](en/BUILDING.md) · [BUILDING (RU)](ru/BUILDING.md)
- [FUNCTIONALITY (EN)](en/FUNCTIONALITY.md) · [FUNCTIONALITY (RU)](ru/FUNCTIONALITY.md) — repository role and capabilities

Generator-specific guides:

- JSON format: [RU](ru/json.md) · [EN](en/json.md)
- New generator: [RU](ru/NewGenerator.md) · [EN](en/NewGenerator.md)
- Output prefixes: [RU](ru/GeneratorsPrefixes.md) · [EN](en/GeneratorsPrefixes.md)
- Changelog: [RU](ru/CHANGELOG.md) · [EN](en/CHANGELOG.md)
