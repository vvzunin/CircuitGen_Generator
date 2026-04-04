# Versioning (Semantic Versioning)

This project follows **[Semantic Versioning 2.0.0](https://semver.org/)** (SemVer) for **release tags and public API compatibility**. The authoritative specification is on [semver.org](https://semver.org/); this page is a short project-local summary.

## Version format

A version number is **`MAJOR.MINOR.PATCH`** (three non-negative integers, no leading zeros):

| Part | When to increment |
|------|-------------------|
| **MAJOR** | Incompatible changes to the **public API** (breaking changes). |
| **MINOR** | New functionality that stays **backward compatible** with the previous public API. |
| **PATCH** | **Backward compatible** bug fixes only. |

Pre-releases may use a hyphen suffix (e.g. `1.0.0-alpha`, `1.0.0-rc.1`). Build metadata may use `+` (ignored for precedence). See the [full spec](https://semver.org/).

## Rules that matter for this codebase

1. **Public API** — SemVer applies once a **public API** is defined (headers, documented CMake package contract, CLI/JSON behavior treated as stable). Until then, **`0.y.z`** is appropriate: anything may change at any time.
2. **Released artifacts are immutable** — a given `MAJOR.MINOR.PATCH` must not be republished with different contents; fixes ship as a **new** version (usually PATCH).
3. **Breaking vs non-breaking** — a **MAJOR** bump is required for changes that force consumers to change their code, build flags, or JSON/config in a non-compatible way.
4. **Deprecations** — deprecating API typically ships in a **MINOR** release with documentation; removal happens in a later **MAJOR** release after users had time to migrate.

## Tags and Git

Release tags are usually named `vMAJOR.MINOR.PATCH` (the `v` prefix is a Git convention; the **semantic version** is still `MAJOR.MINOR.PATCH`). Example: `git tag v1.2.3`.

## Suggested next version (automation)

The script **`scripts/release/suggest-next-version.sh`** inspects commits since the latest SemVer-like tag (`vX.Y.Z` or `X.Y.Z`) and prints a suggested tag using [Conventional Commits](https://www.conventionalcommits.org/) (see [CONTRIBUTING.md](CONTRIBUTING.md)):

| Signal in commit subject / body | Bump |
|---------------------------------|------|
| `BREAKING CHANGE:` / `BREAKING-CHANGE` in body, or `type!:` (e.g. `feat!:`) | **MAJOR** |
| `feat:` | **MINOR** |
| `fix:` or `perf:` | **PATCH** |
| Other types (`docs:`, `ci:`, `chore:`, …) | No bump by default; use `--any-patch` to force **PATCH** if there were any commits |

```sh
bash scripts/release/suggest-next-version.sh
bash scripts/release/suggest-next-version.sh --verbose
bash scripts/release/suggest-next-version.sh --any-patch
```

If nothing matches and `--any-patch` is not set, the script prints the current version and exits with code **2**. Merge commits are ignored (`--no-merges`).

## See also

- [Semantic Versioning 2.0.0](https://semver.org/) — full specification and FAQ  
- [CONTRIBUTING.md](CONTRIBUTING.md) — commit message conventions (orthogonal to release numbers, but both help communicate change)

**Русский:** [Версионирование](../ru/Versioning.md)
