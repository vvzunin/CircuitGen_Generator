# Contributing

<!--
    Short overview, rules, general guidelines, notes about pull requests and
    style should go here.
-->

## Commit messages

Commit messages must be **understandable without extra context** and represent one logical change (or a tightly related set). Avoid titles like “Update”, “Some update”, or “Fix” without saying what changed.

### Format

We recommend [Conventional Commits](https://www.conventionalcommits.org/):

```text
<type>[(scope)]: <short description>
```

- **Type** (common): `feat` — feature; `fix` — bugfix; `refactor` — internal change without behavior change; `docs` — documentation only; `ci` — CI/CD and pipeline scripts; `test` — tests; `build` — CMake, dependencies, build; `chore` — maintenance without functional changes; `style` — formatting only.
- **Scope** — optional; subsystem name such as `ci`, `cmake`, `genetic`, `examples`. Multiple scopes: `feat(ci,examples): …`.
- **Description** — imperative mood (*add*, *fix*), no period at end of the first line, ~72 characters when possible.

Examples:

```text
fix(cmake): pass flags correctly to subdirectory
docs: document Debian 13 dependency install
ci: expand OS matrix in GitLab CI
```

Add a **body** after a blank line when needed: motivation, details, issue/MR references (`Closes #…`, `See …`). For breaking changes, say so in the body or use `BREAKING CHANGE:`.

The **subject line must be in English**.

### Do not

- Commit temp files, secrets, or local settings that must not be in the repo (see `.gitignore`).
- Mix unrelated changes in one commit “just to push” — smaller commits simplify review and `git revert`.

## Merge requests

How to open an MR, assign reviewers, review, request changes, merge, squash vs merge commit, and when to delete branches: [MergeRequests.md](MergeRequests.md).

## Getting started

Developer notes are in [`HACKING.md`](HACKING.md).

If you use CMake presets as documented, **do not** commit `CMakeUserPresets.json` to version control even if upstream CMake examples suggest checking it in.

Some Markdown files are **mirrored** across Generator, Graph, and Parameters (for example the `BUILDING.md` preset + “new sources / CMakeLists” sections, `CI_PIPELINE.md`, `CI_SCRIPTS.md`, and the extra bullets in `docs/README.md`). When you change them, keep the **same structure and wording** in all three repositories unless the edit is clearly repo-specific (package names, `REPO_NAME` / Docker paths, PDF product filename).

**Русский:** [Вклад](../ru/CONTRIBUTING.md)
