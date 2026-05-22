# CircuitGen documentation deploy (Synology NAS)

## Public layout

Published under `DOCS_PUBLIC_BASE_URL` (see CI variable below):

```
CircuitGen/
├── index.html              # portal UI
├── manifest.json           # deployed modules (merged on each CI deploy)
├── modules-registry.json   # full module catalog (incl. planned)
└── modules/
    └── <slug>/             # graph, generator, parameters, …
        ├── meta.json
        ├── pdf/ru.pdf
        ├── pdf/en.pdf
        └── html/{ru,en}/…
```

## CI variables (per repository)

| Variable | Example | Description |
|----------|---------|-------------|
| `NAS_URL` | `https://nas-k7xq.example.invalid:5043` | DSM API base URL |
| `NAS_USER`, `NAS_PASS` | `ci_deploy_bot` / *(masked)* | File Station credentials |
| `NAS_DOCS` | `/volume/docs/AcmeFwk` | Destination folder on NAS |
| `DOCS_MODULE_SLUG` | `widget-core` | URL segment under `modules/` |
| `REPO_DOCS_NAME` | `Widget Core` | Display name |
| `DOCS_PDF_BASE_NAME` | `AcmeWidgetCore` | Built PDF basename |
| `DOCS_PUBLIC_BASE_URL` | `https://docs.example.invalid/acme` | Links in `manifest.json` |

Each module pipeline deploys only `modules/<slug>/` plus portal root files. `manifest.json` is rebuilt from:

1. existing `manifest.json` on NAS (if present),
2. every sibling `modules/<slug>/meta.json` listed on NAS (avoids lost updates when pipelines run in parallel),
3. the current module’s staged `meta.json` (wins for its `id`).

The portal also probes `modules/<id>/meta.json` so the catalog stays correct even if `manifest.json` was overwritten by a concurrent deploy.

Docker image links on portal cards use Harbor layout  
`{registry}/{group}/{imageRepo}/{os}/{dev|release}:{tag}`  
(e.g. `vvzunin.me:5201/circuitgen/graph/fedora-43/release:v1.6.0`, dev tag `main` on all OS: `ubuntu-22.04`, `ubuntu-24.04`, `fedora-43`).

Sources: `modules-registry.json` (`dockerDefaults.osList`, `devTag`, per-module `imageRepo` + `releaseTag`) and `meta.json` after deploy (`docker.images[]`). CI: `REGISTRY_URL`, `GROUP_NAME`, `REPO_NAME`, `DOCKER_DEV_TAG`, `DOCKER_RELEASE_TAG`, `CI_COMMIT_TAG`.

## Local dry-run

```bash
bash scripts/ci/docs.sh          # or scripts/dev/build-docs.sh
export NAS_DEPLOY_STRICT=false   # skip NAS when credentials unset
bash scripts/docs/deploy-synology.sh
```

## Adding a new module (7+)

1. Add an entry to `scripts/docs/modules-registry.json` (same file in every repo).
2. Set `DOCS_MODULE_SLUG` and `REPO_DOCS_NAME` in the module `.gitlab-ci.yml` `docs` job.
3. Reuse `scripts/docs/deploy-synology.sh` (no path changes required).
