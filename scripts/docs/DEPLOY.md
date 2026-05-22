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

Each module pipeline deploys only `modules/<slug>/` plus portal root files. `manifest.json` is downloaded from NAS, merged, and uploaded again so other modules are preserved.

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
