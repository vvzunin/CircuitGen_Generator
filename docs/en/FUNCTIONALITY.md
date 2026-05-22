# CircuitGen Generator — functionality overview

**Repository:** [CircuitGen_Generator](https://hub.mos.ru/circuitgen/CircuitGen_Generator)  
**CMake project:** `CircuitGenGenerator`  
**Role in CircuitGen:** generate batches of combinational and mixed digital circuits from JSON configuration, exporting Verilog, GraphML, and related artifacts.

## Purpose

Generator is the application layer on top of **Graph**. It implements many **generation algorithms** (random level networks, truth tables, genetic search, ALU, coders, state machines, etc.) and orchestrates the full flow: build graph → write files → optional post-processing. The batch entry point is the **`CircuitGenGenerator`** executable and JSON job descriptions.

## Main features

### JSON-driven runs

- Read generation parameters from JSON (`runGenerationFromJson`, `runGenerationFromJsonForGraph`, `runGenerationFromJsonForPath`).
- Batch runs with per-generator output directory prefixes ([GeneratorsPrefixes.md](GeneratorsPrefixes.md), [json.md](json.md)).
- CLI: `CircuitGenGenerator --json_path <path_to_json>`.

### Generation algorithms (`GenerationTypes`)

| Type | Summary |
|------|---------|
| `RandLevel` / `RandLevelExperimental` | Random combinational circuits by levels |
| `FromRandomTruthTable` | Generation from a random truth table |
| `Genetic` | Evolutionary circuit search (chromosomes, mutation, crossover, selection) |
| `NumOperation` | Bit-vector numeric operations |
| `Summator`, `Subtractor`, `Multiplier` | Arithmetic blocks |
| `Comparison`, `Parity` | Compare, parity |
| `Encoder`, `Decoder`, `Multiplexer`, `Demultiplexer` | Encoders and multiplexing |
| `ALU` | Arithmetic logic unit |
| `MealyMoore` | Finite-state machines (Mealy/Moore) |
| `Cascade` | Cascade structures |
| `DotToGraph` | Build a graph from DOT |

Each type uses an output folder prefix `CCG…` (Combinational Circuit Generator).

### Generation architecture

- **`SimpleGenerator`** and derivatives in `src/generators/simple/` — concrete algorithms.
- **`GeneticGenerator`** — genetic pipeline (parents, recombination, mutation, selection).
- **`DataBaseGenerator`** — dispatches by generation type, wraps results in **`Circuit`**.
- **`Circuit`** — `GraphPtr` + path + name; `generate()` writes Verilog, GraphML, etc.
- **`GenerationParameters`** — unified parameters (I/O counts, GraphML, ABC, FIRRTL flags, …).

### Additional modes

- **`runChiselGeneration`** — Chisel-based generation path.
- **`BasisConverter`** — basis conversion.
- Parallelism: `ThreadPool`, `UnboundedMPMCQueue`.

### Output artifacts

- Verilog (`.v`) — primary RTL.
- GraphML (classic, pseudo-ABCD, open-ABCD) when enabled.
- JSON metadata and prefixed output tree.
- Hooks for ABC stats, FIRRTL, bench (parameters in `GenerationParameters`; some paths still evolving).

## Public API

| Component | Purpose |
|-----------|---------|
| `CircuitGenGenerator.hpp` | JSON run entry points, version |
| `export.hpp`, `info.hpp` | Library export macros, build version |

Implementation: `src/generators/`, `src/database/`, `src/circuit/`, `src/settings/`.

## Build and artifacts

- CMake, `dev` / `release-ci` presets, `scripts/dev/build-debug.sh`, `scripts/release/build.sh`.
- Docker CI/dev/release images (`scripts/docker/`).
- Doxygen docs, NAS deploy (same pattern as Graph/Parameters).
- Platforms: Linux (primary CI), Windows/macOS via CMake ([README.md](../../README.en.md)).

## Dependencies

- **CircuitGen Graph** — `OrientedGraph`, `GraphPtr`.
- JSON parsing, filesystem; optional JVM/SBT for Chisel.
- Full CI: Docker, Harbor, OS matrix (`scripts/ci/generate-gitlab-os-matrix.sh`).

## Related repositories

| Repository | Relationship |
|------------|--------------|
| **Graph** | All generators return `GraphPtr`; Verilog export via graph |
| **Parameters** | Generated Verilog → Yosys/ABC/OpenLane |
| **CircuitGen** | Main repo, end-to-end flows |

## Extending the system

Add a generator: type in `Settings.hpp`, parameter class, implementation under `src/generators/simple/<name>/`, register in `DataBaseGenerator` — [NewGenerator.md](NewGenerator.md).

## See also

- [README.md](../../README.en.md) — build, JSON runs  
- [json.md](json.md) — JSON format  
- [GeneratorsPrefixes.md](GeneratorsPrefixes.md) — output prefixes  
- [BUILDING.md](BUILDING.md) — build and CI  
- [CHANGELOG.md](CHANGELOG.md) — release history  
- Russian version: [FUNCTIONALITY.md](../ru/FUNCTIONALITY.md)
