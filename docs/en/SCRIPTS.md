# Project scripts

Scripts live under `scripts/`. They invoke CMake presets and Docker builds without duplicating configure logic.

## Layout

```text
scripts/
  config/
    supported-os.sh
  ci/
    lint.sh
    sanitize.sh
    static-analysis.sh
    coverage.sh
    tests.sh
    examples.sh
    docs.sh
    run-task.sh
    run-all.sh
    generate-gitlab-os-matrix.sh
    docker-build-ci.sh
    docker-build-dev.sh
    docker-build-release.sh
    os-image-build-push.sh
    os-full-check.sh
  dev/
    build-debug.sh
    build-docs.sh
    build-examples.sh
    coverage.sh
    pre-push.sh
    pre-push-docker.sh
  docker/
    docker-paths.sh
    build-ci-image.sh
    build-dev-only-image.sh
    build-release-only-image.sh
    build-images.sh
  release/
    build.sh
    build-examples.sh
    test.sh
    install.sh
  setup/
    install-doxygen-llvm.sh
    install-deps-ubuntu-22.04.sh
    install-deps-ubuntu-24.04.sh
    install-deps-debian-13.sh
    install-deps-fedora-42.sh
    install-deps-fedora-43.sh
    verify-installers-docker.sh
    install-deps-for-current-os.sh
```

Marked **per-OS job** sections in **`.gitlab-ci.yml`** (between `BEGIN generated` / `END generated` comments) are **generated** from `scripts/config/supported-os.sh` (see below); edit `supported-os.sh` and `install-deps-<slug>.sh` only, then run **`generate-gitlab-os-matrix.sh --write`**.

## Supported OS list and GitLab matrix

Target OS slugs and Docker base images (`ID:VERSION`) are defined in **`scripts/config/supported-os.sh`** (`SUPPORTED_OS_ENTRIES`, `DEFAULT_TARGET_OS_SLUG`). `scripts/docker/docker-paths.sh`, Docker helpers, and installer verification consume this file.

GitLab CI lists one job per OS (`docker-images-<slug>`, `os-system-validation-main-<slug>`) in **`.gitlab-ci.yml`** between `BEGIN generated` / `END generated` markers (no `parallel.matrix`, so IDE schemas stay quiet). **Do not edit generated lines by hand** — they must match the generator output.

Script: **`scripts/ci/generate-gitlab-os-matrix.sh`**

- no arguments — print generated blocks to stdout;
- **`--write`** — rewrite the marked sections in `.gitlab-ci.yml`;
- **`--check`** — compare markers in the committed file with generated output (used by `gitlab-os-matrix-check` in `.gitlab-ci.yml`).

After changing `scripts/config/supported-os.sh` (or adding `scripts/setup/install-deps-<slug>.sh`):

```sh
bash scripts/ci/generate-gitlab-os-matrix.sh --write
```

Commit the updated `.gitlab-ci.yml` together with your changes.

### Practice when adding a new OS

Typical steps when onboarding a new OS to the matrix (more than editing `supported-os.sh`):

1. **`supported-os.sh`.** Add `"<slug>|<ID>:<VERSION>"` to `SUPPORTED_OS_ENTRIES`. `ID` and `VERSION_ID` must match `/etc/os-release` in the base Docker image (for `KEY="${ID}:${VERSION_ID}"` in scripts).

2. **CI dependency installer.** Add `scripts/setup/install-deps-<slug>.sh` (copy from the closest OS and adjust packages/repos). After step 1, `install-deps-for-current-os.sh` will pick it up for `dockerfile/Dockerfile.ci` without an extra `case`.

3. **Minimal release toolchain.** Add a branch for the same `ID:VERSION` in **`scripts/docker/install-release-toolchain.sh`** (`dockerfile/Dockerfile.release` calls only this script; without it, release builds fail on the new base even if step 1 is done).

4. **GitLab matrix.** Run `bash scripts/ci/generate-gitlab-os-matrix.sh --write` and commit **`.gitlab-ci.yml`**.

5. **Defaults and `.gitlab-ci.yml`.** If you change the “primary” OS for default variables, update **`DEFAULT_TARGET_OS_SLUG`** in `supported-os.sh` and review **`.gitlab-ci.yml`**: e.g. `TARGET_OS` in `os-system-validation-main-*` jobs (manual on default branch), and `DOCKER_CI_IMAGE` / `DOCKER_DEV_IMAGE` / `DOCKER_RELEASE_IMAGE` under `variables` if they embed an image slug.

6. **Verification.** Run `bash scripts/setup/verify-installers-docker.sh <slug>` and optionally `TARGET_OS=<slug> bash scripts/docker/build-images.sh`.

## General guidance

- Run scripts from the repository root.
- Prefer `bash script.sh` explicitly.
- Most behavior is controlled via environment variables.
- Full tooling: `cmake`, `ninja`, `clang-format` (pinned **18.1.8** via PyPI in `install-clang-format-ci.sh`), `codespell`, `doxygen`, `graphviz`, LaTeX (`pdflatex`/`makeindex`), `docker` (for Docker scripts).

## Script: pre-push checks

Path: `scripts/dev/pre-push.sh`

What it does:
- checks basic tools (`cmake`, `ninja`, `codespell`);
- clean local build;
- `format-check` and `spell-check`;
- build and tests for `dev` and `release-ci`.

Run:

```sh
bash scripts/dev/pre-push.sh
```

Parameters:
- `JOBS` — parallel jobs (default `nproc`).

Example:

```sh
JOBS=8 bash scripts/dev/pre-push.sh
```

## Script: simple Debug build

Path: `scripts/dev/build-debug.sh`

What it does:
- configures the `dev` preset;
- builds in Debug.

Run:

```sh
bash scripts/dev/build-debug.sh
```

Parameters:
- `JOBS` — parallel jobs.

## Script: local documentation build

Path: `scripts/dev/build-docs.sh`

What it does:
- configures the **`dev`** preset (for `compile_commands.json` used by Doxygen libclang);
- runs **`scripts/docs/build-doxygen-lang-variants.sh`** — same pipeline as **`scripts/ci/docs.sh`**, with outputs under **`build/dev/docs/{html,xml,latex,pdf}/{en,ru}/`** (default: English + Russian).

Run:

```sh
bash scripts/dev/build-docs.sh
```

Parameters:
- `DOXYGEN_LANG_VARIANTS` — optional; default `en=english;ru=russian`. Example single language: `DOXYGEN_LANG_VARIANTS=en=english`.
- `DOXYGEN_SKIP_DOT_GRAPHS`, `DOXYGEN_SKIP_REFMAN_PDF` — same as CI (faster iteration).

CI-style output under `build/docs/.../{en,ru}/`: **`bash scripts/ci/docs.sh`**.

The CMake target **`docs`** (only if **`BUILD_MCSS_DOCS=ON`**) uses **`cmake/docs.cmake`** for a **single** language into `build/dev/docs/html` (flat); set **`DOXYGEN_DOCUMENTATION_LANGUAGE`** for that workflow.

## Script: local coverage

Path: `scripts/dev/coverage.sh`

What it does:
- configures and builds the `coverage` preset;
- runs tests;
- generates a coverage report.

Run:

```sh
bash scripts/dev/coverage.sh
```

Parameters:
- `JOBS` — parallel jobs.

## Script: pre-push in Docker

Path: `scripts/dev/pre-push-docker.sh`

What it does:
- runs the same checks as `scripts/dev/pre-push.sh`;
- inside a local dev Docker image;
- bind-mounts the repo and runs with your UID/GID.

Run:

```sh
bash scripts/dev/pre-push-docker.sh
```

Parameters:
- `DEV_IMAGE_TAG` — full dev image name (default via `scripts/docker/docker-paths.sh`, e.g. `circuitgen/generator/ubuntu-24.04/dev:local`);
- `TARGET_OS` — see `scripts/docker/docker-paths.sh`;
- `JOBS` — parallel jobs inside the container.

Example:

```sh
TARGET_OS=ubuntu-22.04 DEV_IMAGE_TAG=circuitgen/generator/ubuntu-22.04/dev:local JOBS=8 bash scripts/dev/pre-push-docker.sh
```

## Helper: Docker image paths

Path: `scripts/docker/docker-paths.sh`

What it does:
- central image naming aligned with `.gitlab-ci.yml`:
  `$DOCKER_URL/$IMAGE_OS_SUFFIX/ci:<tag>`, `$DOCKER_URL/$IMAGE_OS_SUFFIX/dev:<tag>`,
  `$DOCKER_URL/$IMAGE_OS_SUFFIX/release:<tag>`;
- OS selection via `TARGET_OS` or `DOCKER_CI_SYSTEM`;
- consumed by `scripts/docker/*`, `scripts/ci/docker-build-*.sh`, `scripts/ci/docs.sh`, `scripts/ci/run-task.sh`, `scripts/dev/pre-push-docker.sh`.

## Script: build Docker images (CI + dev + release)

Path: `scripts/docker/build-images.sh`

What it does:
- build local CI image from `dockerfile/Dockerfile.ci`;
- build local dev image from `dockerfile/Dockerfile.dev` on top of CI;
- build local release image from `dockerfile/Dockerfile.release` on a minimal OS base
  (compiler, CMake, Ninja, git, etc. — no Doxygen/TeX or full CI stack).

Image names come from `scripts/docker/docker-paths.sh` and match `.gitlab-ci.yml`:
`$DOCKER_URL/$IMAGE_OS_SUFFIX/ci:<tag>`, `$DOCKER_URL/$IMAGE_OS_SUFFIX/dev:<tag>`,
`$DOCKER_URL/$IMAGE_OS_SUFFIX/release:<tag>`.

Run:

```sh
bash scripts/docker/build-images.sh
```

Environment:
- `DOCKERFILE_CI_NAME` (default `dockerfile/Dockerfile.ci`);
- `DOCKERFILE_DEV_NAME` (default `dockerfile/Dockerfile.dev`);
- `DOCKERFILE_RELEASE_NAME` (default `dockerfile/Dockerfile.release`);
- `DOCKERFILE_CI` (legacy alias, overrides `DOCKERFILE_CI_NAME`);
- `DOCKERFILE_DEV` (legacy alias, overrides `DOCKERFILE_DEV_NAME`);
- `DOCKERFILE_RELEASE` (legacy alias, overrides `DOCKERFILE_RELEASE_NAME`);
- `DOCKER_URL` (default `circuitgen/generator`, or `${REGISTRY_URL}/${GROUP_NAME}/${REPO_NAME}` when set);
- `TARGET_OS` — slug from `scripts/config/supported-os.sh` (drives `DOCKER_CI_SYSTEM`);
- `DOCKER_CI_SYSTEM` (default `ubuntu:24.04`; derives `IMAGE_OS_SUFFIX`);
- `LOCAL_IMAGE_TAG` — local tag suffix (default `local`);
- `CI_IMAGE_TAG` / `DEV_IMAGE_TAG` / `RELEASE_IMAGE_TAG` — full names (optional; otherwise derived).

Example:

```sh
TARGET_OS=fedora-42 bash scripts/docker/build-images.sh
```

## Script: CI Docker image only

Path: `scripts/docker/build-ci-image.sh`

Builds only the local CI image from `dockerfile/Dockerfile.ci`.

```sh
bash scripts/docker/build-ci-image.sh
```

## Script: dev Docker image only

Path: `scripts/docker/build-dev-only-image.sh`

Builds only the dev image from `dockerfile/Dockerfile.dev` using an existing CI base.

```sh
bash scripts/docker/build-dev-only-image.sh
```

## Script: release Docker image only

Path: `scripts/docker/build-release-only-image.sh`

Builds only the release image from `dockerfile/Dockerfile.release`; base image comes from `DOCKER_CI_SYSTEM` / `TARGET_OS` (`BASE_IMAGE` in the Dockerfile), not the fat CI image.

```sh
bash scripts/docker/build-release-only-image.sh
```

## Release scripts

- `scripts/release/build.sh` — optimized release build without tests.
- `scripts/release/test.sh` — release build with tests (`release-ci` preset).
- `scripts/release/install.sh` — install release build artifacts.
- `scripts/release/suggest-next-version.sh` — print a suggested `vX.Y.Z` tag from commits since the last SemVer tag (Conventional Commits); see [Versioning.md](Versioning.md).

Examples:

```sh
bash scripts/release/build.sh
bash scripts/release/test.sh
INSTALL_PREFIX=prefix/release bash scripts/release/install.sh
bash scripts/release/suggest-next-version.sh --verbose
```

## Dependency installers

- `scripts/setup/install-deps-ubuntu-22.04.sh` — Ubuntu 22.04.
- `scripts/setup/install-deps-ubuntu-24.04.sh` — Ubuntu 24.04.
- `scripts/setup/install-deps-debian-13.sh` — Debian 13 (trixie). Installs pinned `clang-format` **18.1.8** via `install-clang-format-ci.sh` (PyPI wheel).
- `scripts/setup/install-deps-fedora-42.sh` — Fedora Workstation 42.
- `scripts/setup/install-deps-fedora-43.sh` — Fedora Workstation 43.

All installers:
- detect distro and version;
- skip already installed packages;
- install only missing packages;
- install `codespell` via `pip` if the distro package is unavailable;
- build `doxygen` from source with `-Duse_libclang=ON` (default `1.13.2`), matching `dockerfile/Dockerfile.ci`.

Extra:
- `scripts/setup/install-doxygen-llvm.sh` — build Doxygen with LLVM/libclang support.

Verify installers in Docker:

```sh
bash scripts/setup/verify-installers-docker.sh
```

Single OS:

```sh
bash scripts/setup/verify-installers-docker.sh ubuntu-24.04
```

Checked slugs match `scripts/config/supported-os.sh` (and marked matrix sections in `.gitlab-ci.yml` after `generate-gitlab-os-matrix.sh --write`).

## CI scripts

`scripts/ci/` is the single entry point used from `.gitlab-ci.yml`.

Local modes:
- `CI_RUNNER=local` — host execution;
- `CI_RUNNER=docker` — inside a local CI container.

For `scripts/ci/docs.sh` additionally:
- `DOCS_RUNNER=auto|local|docker` (default `auto`).
- `DOXYGEN_LANG_VARIANTS` — default **`en=english;ru=russian`**. Format `abbr=section1 section2;abbr2=...`; each variant writes to `build/docs/{html,xml,latex,pdf}/<abbr>/`.
- `DOXYGEN_SKIP_DOT_GRAPHS`, `DOXYGEN_SKIP_REFMAN_PDF` — forwarded to `cmake/docs-ci.cmake`.
- `DOXYGEN_ENABLED_SECTIONS` — legacy default `english` when not using explicit variants; overridden per variant by **`DOXYGEN_LANG_VARIANTS`**. `cmake/docs-ci.cmake` sets Doxygen **`OUTPUT_LANGUAGE`** from each variant’s sections (Russian when that variant’s sections are exactly `russian`, otherwise English).

### Wrappers

- `scripts/ci/run-task.sh <task>` — one CI stage (`lint`, `sanitize`, `static-analysis`, `coverage`, `tests`, `examples`, `docs`).
- `scripts/ci/run-all.sh` — full pipeline: `lint -> static-analysis -> sanitize -> coverage -> tests -> examples -> docs`.

Examples:

```sh
CI_RUNNER=local bash scripts/ci/run-task.sh lint
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-task.sh tests
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-all.sh
```

### Checks and tests

- `scripts/ci/lint.sh` — format and spell checks via CMake, validates `.clang-format`, checks `clang-format` version.
- `scripts/ci/sanitize.sh` — `ci-sanitize` preset, tests with sanitizers.
- `scripts/ci/static-analysis.sh` — `ci-static-analysis` (clang-tidy at compile time) + `cppcheck` on `compile_commands.json`.
- `scripts/ci/coverage.sh` — `ci-coverage` preset, tests, coverage report.
- `scripts/ci/tests.sh` — `release-ci` build, install, tests with JUnit output.
- `scripts/ci/examples.sh` — examples in **Debug** (`ci-examples-dev`) and **Release** (`release-examples`), then **`run-examples`** (see `examples/CMakeLists.txt`, `docs/en/BUILDING.md`).
- `scripts/ci/docs.sh` — docs via `cmake/docs-ci.cmake` with Doxygen libclang parsing. HTML via `m.css`; default outputs
  `build/docs/html/{en,ru}`, `build/docs/xml/{en,ru}`, etc. Graphviz `dot` is configured in CMake (`HAVE_DOT`/`DOT_PATH`).
  Default **`DOXYGEN_LANG_VARIANTS="en=english;ru=russian"`** (see `scripts/docs/build-doxygen-lang-variants.sh`).
  Conditional blocks: `\english ... \lang_end`, `\russian ... \lang_end` (Doxygen `\if` sections).
  Local runs default to Docker `CI_IMAGE_TAG` (`circuitgen/generator/ubuntu-24.04/ci:local` via `scripts/docker/docker-paths.sh`).
  Fails if Doxygen lacks `CLANG_ASSISTED_PARSING`.

### GitLab matrix consistency

- `scripts/ci/generate-gitlab-os-matrix.sh` — updates marked matrix sections in `.gitlab-ci.yml`. Job `gitlab-os-matrix-check` runs `--check`; on mismatch, run `--write` and commit.

### Docker images in CI

- `scripts/ci/docker-build-ci.sh` — build/publish CI image (matrix over OS).
- `scripts/ci/docker-build-dev.sh` — dev image on CI base for the same OS.
- `scripts/ci/docker-build-release.sh` — release image (minimal base, see `dockerfile/Dockerfile.release`).

Environment variables from `.gitlab-ci.yml`:
`DOCKERFILE_CI_NAME`, `DOCKERFILE_DEV_NAME`, `DOCKERFILE_RELEASE_NAME`, `DOCKER_CI_SYSTEM`,
`DOCKER_CI_TAG`, `REGISTRY_URL`, `GROUP_NAME`, `REPO_NAME`, `DOCKER_URL`,
`DOCKER_CI_IMAGE`, `DOCKER_DEV_IMAGE`, `DOCKER_RELEASE_IMAGE`.

### Per-OS checks (matrix)

- `scripts/ci/os-image-build-push.sh` — for `TARGET_OS`, build `.../os-<target>:<tag>`, run `scripts/setup/install-deps-*.sh`, push to registry.
- `scripts/ci/os-full-check.sh` — run full `scripts/ci/run-all.sh` in the published OS image.

Branch rules in `.gitlab-ci.yml`:
- `main` — all supported OS;
- other branches — `ubuntu-24.04` only.

**Русский:** [Скрипты](../ru/SCRIPTS.md)
