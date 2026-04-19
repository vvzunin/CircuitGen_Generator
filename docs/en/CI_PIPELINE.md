# GitLab CI: pipeline and architecture

This document describes the **GitLab CI/CD** pipeline for this CircuitGen repository (Parameters, Graph, or Generator). It is **kept in sync** across the three repositories; the only intentional difference is **`REPO_NAME`** in `.gitlab-ci.yml` (`parameters` / `graph` / `generator`) and the resulting image paths in the registry.

For a full script reference, see [CI_SCRIPTS.md](CI_SCRIPTS.md).

---

## 1. High-level architecture

- **Orchestration:** GitLab Runner with the **Docker** executor, tag **`docker`**.
- **Image builds:** jobs use **`docker:27`** (via registry proxy cache) plus a **Docker-in-Docker (dind)** service `docker:27-dind`. The runner must allow **`privileged = true`**.
- **Code checks (lint, tests, …):** jobs run on **`$DOCKER_CI_IMAGE`**, i.e. the CI image built from `dockerfile/Dockerfile.ci` and pushed to your registry (`REGISTRY_URL` / `GROUP_NAME` / `REPO_NAME`).
- **Registry mirrors:** `.gitlab-ci.yml` sets Harbor projects **`DOCKER_HUB_PROXY_PROJECT`** and **`DOCKER_GITLAB_PROXY_PROJECT`** so client/dind and some base layers are pulled through the proxy (rate limits, speed).

```mermaid
flowchart LR
  subgraph validate["validate"]
    A[gitlab-os-matrix-check]
  end
  subgraph docker["docker stages"]
    B[docker-images-*]
    C[docker-release-*]
  end
  subgraph checks["check / test"]
    D[lint, static-analysis, ...]
    E[tests, coverage, examples]
  end
  A --> B
  B --> D
  D --> E
  E --> C
```

### Stage diagram

Order of the **`stages:`** section in `.gitlab-ci.yml`: the next stage starts after all jobs in the previous stage finish (subject to GitLab skip rules and manual jobs).

```mermaid
flowchart TB
  S1["validate"] --> S2["docker-ubuntu"]
  S2 --> S3["check"]
  S3 --> S4["test"]
  S4 --> S5["docker-matrix"]
  S5 --> S6["check-os"]
  S6 --> S7["test-os"]
  S7 --> S8["os-check"]
  S8 --> S9["docs"]
  S9 --> S10["release"]
```

### Main dependency flow (Ubuntu 24.04)

Simplified **`needs:`** chain for the default CI image: YAML check, build/push **`ci`**, then `check` / `test`; then secondary OS image builds and **`docker-release`** (mostly on tags, after successful **tests** and **examples**).

```mermaid
flowchart LR
  V[gitlab-os-matrix-check]
  D[docker-images-ubuntu-24.04]
  L[lint]
  N[sanitize]
  SA[static-analysis]
  C[coverage]
  T[tests]
  X[examples]
  M[docker-images secondary OS]
  R[docker-release]

  V --> D
  D --> L
  D --> N
  D --> SA
  L --> C
  N --> C
  SA --> C
  L --> T
  N --> T
  SA --> T
  D --> T
  L --> X
  D --> X
  T --> M
  X --> M
  T --> R
  X --> R
```

Secondary **`docker-images-*`** jobs (not Ubuntu 24.04) list **`needs`** on **`docker-images-ubuntu-24.04`**, **`tests`**, and **`examples`** only — not **`coverage`** (see `.gitlab-ci.yml`).

---

## 2. Workflow rules (`.gitlab-ci.yml`)

- Commit message contains **`[skip ci]`** → pipeline is **skipped**.
- Draft merge requests → pipeline is **skipped**.
- **`DOCKER_CI_TAG`** (tag for `ci` / `dev` / `release` images in the registry) is set by `workflow` rules depending on pipeline source (simplified, as in `.gitlab-ci.yml`):
  - **Git tag** → `DOCKER_CI_TAG = CI_COMMIT_TAG`;
  - **Merge request** when **`CI_COMMIT_REF_SLUG`** is truthy → `DOCKER_CI_TAG = CI_COMMIT_REF_SLUG`;
  - **Merge request** otherwise → `DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`;
  - **Branch push** (`CI_COMMIT_BRANCH` set) → `DOCKER_CI_TAG = CI_COMMIT_REF_SLUG`;
  - **Fallback** (`when: always`) → `DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`.

See the top of `.gitlab-ci.yml` in the repo for the exact conditions.

---

## 3. Stages

| Stage | Purpose |
|--------|---------|
| **validate** | Ensures generated `.gitlab-ci.yml` blocks match `scripts/config/supported-os.sh` (`generate-gitlab-os-matrix.sh --check`). |
| **docker-ubuntu** | Build and push **ci** images (and, per rules, **dev**) for **Ubuntu 24.04** — primary source of `$DOCKER_CI_IMAGE` for later stages. |
| **check** | Lint, static analysis, sanitizers in the default CI image (Ubuntu 24.04). |
| **test** | Unit tests, coverage, examples in the same CI image. |
| **docker-matrix** | **ci** images for secondary OSes after successful **`tests`** and **`examples`** on Ubuntu 24.04; **`docker-release-*`** on tags (same **needs**). |
| **check-os** / **test-os** | Same checks on **secondary OS** images (see `rules` / `.secondary-os-matrix-rules`). |
| **os-check** | Full install-deps and scenario checks on “clean” OS images (`os-image-build-push` + `os-full-check`), higher `timeout`. |
| **docs** | Documentation build (Doxygen, etc.) with path-based `rules`. |
| **release** | GitLab Release creation on version tags (`create-gitlab-release.sh`). |

---

## 4. OS matrix and YAML generation

- Single source of truth: **`scripts/config/supported-os.sh`**.
- **`scripts/ci/generate-gitlab-os-matrix.sh`** rewrites marked sections in **`.gitlab-ci.yml`** (`# BEGIN generated` … `# END generated`).
- After changing supported OSes, run **`--write`** and commit the updated `.gitlab-ci.yml`. CI **validate** runs **`--check`**.

---

## 5. Docker images in CI

- **CI:** `Dockerfile.ci`, variables `DOCKERFILE_CI_NAME`, `DOCKER_CI_SYSTEM`, push to `$DOCKER_URL/<os>/ci:$DOCKER_CI_TAG`.
- **Dev:** `Dockerfile.dev` — build in jobs is limited to **tags and the default branch** (see the embedded `if` in `.gitlab-ci.yml`); the local **dev** image is removed in **`after_script`** to avoid filling the dind disk.
- **Release:** `Dockerfile.release` — for tags; the local **release** image is also removed in **`after_script`**.
- Skip redundant rebuilds: **`docker-skip-if-unchanged.sh`**, invoked from `docker-build-*.sh` when **`CI`** is set. Only paths listed in **`docker-context-changed.sh`** count (for **`ci`**: `Dockerfile.ci`, `scripts/setup`, …); **`docs/` is not part of the CI image context**. A skip happens when the registry already has **`$DOCKER_CI_IMAGE`** or **`ci:$CI_COMMIT_SHORT_SHA`**, and those paths did not change since the merge base. **If the tag is missing** (first pipeline for the ref, registry cleanup, failed previous push, or **`DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`** on every MR commit — see `workflow` in `.gitlab-ci.yml`), the job still runs a full **`docker build`**, even for docs-only commits.
- **`resource_group`** on docker/os jobs serializes builds per project/OS.

---

## 6. Local runs (CI parity)

- **`bash scripts/ci/run-task.sh <task>`** — one task (`lint`, `tests`, …): locally or in a container (`CI_RUNNER=docker`, `CI_IMAGE_TAG=...`).
- **`bash scripts/ci/run-all.sh`** — runs CI scripts in sequence; see the script for order (GitLab runs several jobs in parallel).

More detail: [CI_SCRIPTS.md](CI_SCRIPTS.md), [SCRIPTS.md](SCRIPTS.md), [HACKING.md](HACKING.md).

---

## 7. Windows runner maintenance

For hosts using **Docker Desktop (WSL2)** where disk usage grows, use **`scripts/ci/docker-prune-keep-bases.ps1`**. Full instructions: [CI_SCRIPTS.md §7](CI_SCRIPTS.md#docker-prune-runner-windows) (EN) / [Russian version](../ru/CI_SCRIPTS.md#docker-prune-runner-windows). This is **not** a default GitLab job step; it is manual or scheduled host maintenance.
