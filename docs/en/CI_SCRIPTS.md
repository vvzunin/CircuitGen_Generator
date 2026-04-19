# Reference: `scripts/ci`

This document is **kept in sync** across the Parameters, Graph, and Generator repositories. Script behavior is the same; GitLab jobs inject variables (`REPO_NAME`, `DOCKER_URL`, …) from `.gitlab-ci.yml`.

Pipeline overview: [CI_PIPELINE.md](CI_PIPELINE.md).

---

## 1. Running tasks locally

| Script | Purpose |
|--------|---------|
| **`run-task.sh`** | Single task: `bash scripts/ci/run-task.sh lint`, etc. Environment: `CI_RUNNER=local\|docker`, `CI_IMAGE_TAG`, `TARGET_OS`. |
| **`run-all.sh`** | Runs the main CI scripts in sequence; see the script for order (GitLab runs several jobs in parallel). |

See `run-task.sh` for the supported task names (`lint`, `sanitize`, `static-analysis`, `coverage`, `tests`, `examples`, `docs`, …).

---

## 2. Docker image build and push

| Script | Purpose |
|--------|---------|
| **`docker-build-ci.sh`** | Build and push the **CI** image (`buildx`), driven by `docker-paths.sh` / CI variables. |
| **`docker-build-dev.sh`** | Build the **dev** image (based on the CI image). |
| **`docker-build-release.sh`** | Build the **release** image. |
| **`docker-registry-login.sh`** | `docker login` to the CI registry (GitLab CI/CD variables). |
| **`docker-skip-if-unchanged.sh`** | `docker manifest inspect` plus `docker-context-changed.sh`; exit 0 means skip the build. Argument: `ci` \| `dev` \| `release`. |
| **`docker-context-changed.sh`** | `git diff` over paths that affect an image layer; argument: `ci` \| `dev` \| `release`. |
| **`docker-hub-proxy-image.sh`** | Rewrites a short Docker Hub reference (`ubuntu:24.04`) to a Harbor proxy path (`REGISTRY_URL`/`DOCKER_HUB_PROXY_PROJECT`). |

---

## 3. `.gitlab-ci.yml` generation and validation

| Script | Purpose |
|--------|---------|
| **`generate-gitlab-os-matrix.sh`** | Generates OS matrix jobs between markers in `.gitlab-ci.yml`. Modes: no args (stdout), `--write`, `--check`. |

---

## 4. Code checks (main entrypoints)

| Script | Purpose |
|--------|---------|
| **`lint.sh`** | Linting (format, project rules). |
| **`static-analysis.sh`** | Static analysis (e.g. cppcheck). |
| **`sanitize.sh`** | Build/tests with sanitizers. |
| **`tests.sh`** | Run tests (CTest, etc.). |
| **`coverage.sh`** | Code coverage. |
| **`examples.sh`** | Build/run examples. |
| **`docs.sh`** | Documentation build in CI. |

---

## 5. OS images and full checks

| Script | Purpose |
|--------|---------|
| **`os-image-build-push.sh`** | Build a “clean” OS image and push to the registry (os-check stage). |
| **`os-full-check.sh`** | Full validation on an OS image (install-deps, checks). |

---

## 6. Other

| Script | Purpose |
|--------|---------|
| **`create-gitlab-release.sh`** | Create a GitLab Release (**release** stage, tags). |
| **`apk-install-with-retry.sh`** | Install **apk** packages on Alpine with retries (helper for `before_script`). |

---

<a id="docker-prune-runner-windows"></a>

## 7. Windows runner maintenance: `docker-prune-keep-bases.ps1`

PowerShell script for **Windows 11** hosts with **Docker Desktop (WSL2)** and **GitLab Runner**: removes accumulated **non-base** images and optionally **compacts** `docker_data.vhdx` so **free space on the Windows volume** grows. This is **not** a `.gitlab-ci.yml` job; it is **manual or scheduled** runner host maintenance.

**Executable:** `scripts/ci/docker-prune-keep-bases.ps1` (the **`scripts/ci`** tree is synchronized across **Parameters**, **Graph**, and **Generator**).

**Русский:** the same section in [docs/ru/CI_SCRIPTS.md](../ru/CI_SCRIPTS.md#docker-prune-runner-windows).

### Purpose

| Problem | What the script does |
|---------|----------------------|
| Many CI images / private-registry tags on the runner host | Removes them with `docker rmi`, keeping common base images |
| After `docker rmi`, **no** extra free space on `C:` in Explorer | Optionally runs `Optimize-VHD` on `docker_data.vhdx` |

### Requirements

**Image cleanup:** PowerShell 5.1+, Docker CLI on `PATH`; **administrator not required**.

**VHDX compaction (`-CompactDockerDataVhdx`):** elevated PowerShell, **Hyper-V** module (`Optimize-VHD`), Docker Desktop.

### Two stages

**Cleanup (default):** `docker image prune -f` (unless `-SkipDanglingPrune`); then for each tag compare **REPOSITORY** to “keep” rules — otherwise `docker rmi repository:tag`; finally `docker system df`. If a container still uses an image, `docker rmi` fails — expected.

**VHDX compaction:** graceful Docker Desktop exit (`--quit`, wait up to `DockerQuitWaitSeconds`), `wsl --shutdown` and `WslShutdownWaitSeconds` delay, then `Optimize-VHD -Mode Full` on `%LOCALAPPDATA%\Docker\wsl\disk\docker_data.vhdx` (or `-DockerDataVhdxPath`). **Start Docker manually** afterwards. Layer deletion frees space *inside* the VHDX; the `.vhdx` file on NTFS does not shrink until **compact**.

### Default “keep” rules

Images whose **REPOSITORY** matches: `ubuntu`, `debian`, `fedora`, `docker` (incl. dind), `alpine`, `busybox` (incl. `docker.io/library/…`), or `registry.gitlab.com/gitlab-org/release-cli`, are **kept**. Everything else is removed. Add **`-ExtraKeepPattern`** for more exceptions.

### Parameters

| Parameter | Purpose |
|-----------|---------|
| `-KeepRepositoryRegex` | Custom “keep” regex list |
| `-ExtraKeepPattern` | Additional regexes |
| `-SkipDanglingPrune` | Skip `docker image prune -f` |
| `-SkipImagePrune` | Image stage skipped (use with `-CompactDockerDataVhdx`) |
| `-CompactDockerDataVhdx` | Compact `docker_data.vhdx` |
| `-DockerDataVhdxPath` | Path to `.vhdx` |
| `-DockerQuitWaitSeconds` / `-WslShutdownWaitSeconds` | Timeouts (defaults 90 / 15) |
| `-WhatIf` / `-Confirm` | `ShouldProcess` |

### Typical commands

```powershell
cd <repo_root>
.\scripts\ci\docker-prune-keep-bases.ps1 -WhatIf
.\scripts\ci\docker-prune-keep-bases.ps1
.\scripts\ci\docker-prune-keep-bases.ps1 -CompactDockerDataVhdx   # elevated
.\scripts\ci\docker-prune-keep-bases.ps1 -ExtraKeepPattern '^mcr\.microsoft\.com/'
.\scripts\ci\docker-prune-keep-bases.ps1 -SkipImagePrune -CompactDockerDataVhdx
```

### Built-in help

```powershell
Get-Help .\scripts\ci\docker-prune-keep-bases.ps1 -Full
```

Matches the comment-based help at the top of the `.ps1`.

### FAQ

Long runs / stuck `docker system df` — common on huge stores or slow disks. **Free space on `C:` did not increase** after `rmi` — run **`-CompactDockerDataVhdx`**. **`Optimize-VHD` fails** — admin, Hyper-V, fully stop Docker/WSL. **Custom bases** — extend **`-ExtraKeepPattern`** on full `REPOSITORY`.

### Automation and safety

Windows Task Scheduler + `powershell.exe -File …\docker-prune-keep-bases.ps1`; for compact, **Run with highest privileges**. Use **`-WhatIf`** first. **`wsl --shutdown`** stops **all** WSL distros. Schedule a maintenance window on shared runners.

**See also:** [CI_PIPELINE.md](CI_PIPELINE.md).

---

## 8. Related directories

| Directory | Role |
|-----------|------|
| `scripts/config` | `supported-os.sh` — OS matrix for CI. |
| `scripts/docker` | `docker-paths.sh` and registry/path helpers. |
| `scripts/setup` | OS dependency installers (used by Dockerfiles and os-check). |
| `scripts/dev`, `scripts/release`, `scripts/docs` | Not GitLab CI entrypoints from `.gitlab-ci.yml`, but related to dev/release/docs; see [SCRIPTS.md](SCRIPTS.md). |
