# Documentation Deployment (Synology NAS)

This deployment flow is shared by **Graph**, **Generator**, and **Parameters** (`scripts/docs/` is kept in sync). In each repository, the GitLab **`docs`** job runs `scripts/ci/docs.sh` and then `scripts/docs/deploy-synology.sh`.

**Русский:** [DEPLOY.md](../ru/DEPLOY.md)

## Public URL and layout

The portal is published under `DOCS_PUBLIC_BASE_URL` (CI variable, e.g. `https://vvzunin.me/docs/CircuitGen`):

```
CircuitGen/
├── index.html, portal.js, portal.css   # portal UI (ru/en)
├── manifest.json                       # schema v2 — all modules and doc channels
├── modules-registry.json               # catalog: repos, Docker image links, planned modules
└── modules/
    └── <slug>/                         # graph | generator | parameters | …
        ├── versions.json               # index: main + release tags
        └── versions/
            ├── main/                   # rolling docs from default-branch CI
            │   ├── meta.json
            │   ├── pdf/{ru,en}.pdf
            │   └── html/{ru,en}/…
            └── v1.6.0/                 # frozen docs from Git tag pipeline
                ├── meta.json
                └── …
```

**Legacy layout** `modules/<slug>/meta.json` (flat, no `versions/`) is still discovered by the portal as channel **main**.

## Version channels

| Pipeline | `DOCS_VERSION_CHANNEL` | NAS path replaced |
|----------|------------------------|-------------------|
| Default branch (`main`) | `main` | `modules/<slug>/versions/main/` only |
| Git tag (`v1.6.0`, …) | exact tag name | `modules/<slug>/versions/v1.6.0/` only |

Channel resolution is implemented in `scripts/docs/nas-docs-names.sh`: `resolve_docs_version_channel` uses `CI_COMMIT_TAG` when it is set, otherwise it falls back to `main`.

Older release trees are **not** deleted when a new tag is deployed. `versions.json` lists all known channels (merged from NAS + local staging).

## CI job `docs`

**Rules** (`.gitlab-ci.yml`):

- Always for **Git tags** (full docs build and NAS deployment for that tag).
- For the **default branch**, when `changes:` match (sources, `scripts/docs/**`, Doxygen inputs, `scripts/ci/docs.sh`, etc.).

**Script:** `bash scripts/ci/docs.sh` → `bash scripts/docs/deploy-synology.sh`.

**Artifacts:** `docs_<tag>.tar.gz` or `docs_latest.tar.gz` (local `build/docs` tree; independent of NAS).

**Release stage:** `release-from-tag` creates a GitLab Release only; it does not upload to NAS.

Set `NAS_DEPLOY_STRICT=false` for local runs when NAS credentials are not available.

## CI variables (per repository)

| Variable | Example (Graph) | Description |
|----------|-----------------|-------------|
| `NAS_URL` | `https://vvzunin.me:5001` | DSM / File Station API base |
| `NAS_USER`, `NAS_PASS` | *(masked CI/CD variables)* | File Station credentials |
| `NAS_DOCS` | `/volume1/web/docs/CircuitGen` | Destination folder on NAS |
| `NAS_DEPLOY_STRICT` | `true` in CI | Fail when credentials are missing |
| `DOCS_MODULE_SLUG` | `graph` | URL segment under `modules/` |
| `REPO_DOCS_NAME` | `Graph` | Display name in `meta.json` |
| `DOCS_PDF_BASE_NAME` | `CircuitGenGraph` | Built PDF basename |
| `DOCS_PUBLIC_BASE_URL` | `https://vvzunin.me/docs/CircuitGen` | Base URL in `manifest.json` / portal |

Generator uses `generator` / `CircuitGenGenerator`; Parameters uses `parameters` / `CircuitGenParameters`.

## Deploy pipeline (scripts)

| Script | Role |
|--------|------|
| `deploy-synology.sh` | Orchestrator: stage docs → create ZIP → delete the target channel on NAS → upload → extract → refresh portal files |
| `stage-module-docs.sh` | Copy `build/docs` into `modules/<slug>/versions/<channel>/` |
| `versions-index.sh` | Merge remote `versions.json` with every staged `versions/*/meta.json` |
| `manifest-merge.sh` | Build `manifest.json` schema v2 (`channels[]` per module) from staging + NAS siblings |
| `nas-filestation-api.sh` | Auth v3, upload, extract, remote listing, legacy flat `meta.json` support |
| `nas-docs-names.sh` | Slug, PDF basename, version channel, path normalization |
| `build-doxygen-lang-variants.sh` | Shared Doxygen driver (used by `docs.sh` / `build-docs.sh`) |
| `modules-registry.json` | Portal catalog: [hub.mos.ru](https://hub.mos.ru) repo URLs, `dockerDefaults`, per-module `releaseTag` |
| `portal/*` | Static portal; version selector per card; probes `versions.json` and per-channel `meta.json` |

**Parallel CI:** module pipelines may run at the same time. Each job replaces only its own module/channel directory, then merges **sibling modules** discovered on NAS into `manifest.json`. This prevents a stale manifest from removing links published by another module.

## Portal and Docker links

- Language toggle (ru/en) uses a single `change` listener (no duplicate cards).
- Each module card links to HTML/PDF for both languages and shows a version dropdown when multiple channels exist.
- **Repository** links come from `modules-registry.json` (`hub.mos.ru`, not GitHub).
- **Docker** dev/release links per OS (`ubuntu-22.04`, `ubuntu-24.04`, `fedora-43`):  
  `{registryHost}/{group}/{imageRepo}/{os}/{dev|release}:{tag}` (see `dockerDefaults` in registry JSON).

## Local Dry Run

```bash
bash scripts/ci/docs.sh          # or scripts/dev/build-docs.sh
export NAS_DEPLOY_STRICT=false   # skip NAS when credentials unset
bash scripts/docs/deploy-synology.sh
```

Simulate a release channel:

```bash
export DOCS_VERSION_CHANNEL=v1.6.0
export CI_COMMIT_TAG=v1.6.0
bash scripts/docs/deploy-synology.sh
```

## Validation without NAS

```bash
bash scripts/ci/test_deploy_mock.sh
```

This checks path normalization, the staging layout (`versions/<channel>/`), `versions.json` merging for `main` and a tag channel, manifest schema v2, and the `.gitlab-ci.yml` call to `deploy-synology.sh`.

## Adding a new module (7+)

1. Add an entry to `scripts/docs/modules-registry.json` (the same file is kept in every repository).
2. Set `DOCS_MODULE_SLUG`, `REPO_DOCS_NAME`, and `DOCS_PDF_BASE_NAME` in the module’s `.gitlab-ci.yml` `docs` job.
3. Reuse `scripts/docs/deploy-synology.sh` (no path changes required).

## See also

- [SCRIPTS.md](SCRIPTS.md) — layout and script index  
- [CI_SCRIPTS.md](CI_SCRIPTS.md) — `docs.sh` and NAS deploy (§7)  
- [CI_PIPELINE.md](CI_PIPELINE.md) — `docs` stage rules  
