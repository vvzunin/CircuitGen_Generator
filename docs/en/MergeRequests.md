# Merge requests (MR)

This document describes merge-request practices for this repository on GitLab. Project settings (minimum approvals, required checks) may be stricter — always follow the GitLab UI and maintainers when they **override** these guidelines.

## Preparation

- Branch from an **up-to-date** target branch (usually the agreed development default).
- Keep the MR **focused**: one topic or a tightly related set of changes; unrelated edits make review and rollback harder.
- Before opening the MR, ensure **builds and tests pass** locally (or on your fork CI) and commit messages follow [CONTRIBUTING.md](CONTRIBUTING.md).
- If the repo requires generated artifacts (e.g. CI matrix YAML from a script), regenerate and **include them in the same MR**.

## Opening an MR: recommended order

1. **Push** your branch to the shared remote (or open an MR from a fork, per your GitLab workflow).
2. **Create the MR** and fill in:
   - **Title** — short and specific (English subject line; Conventional-Commits style when it matches the change).
   - **Description** — what changed and why, how to verify, links to issues (`Closes #…`, `See …`), screenshots when behavior or UI changes.
   - **Target branch** — the branch that should receive the change.
3. Use a **Draft** MR while the work is **not** ready for review so reviewers are not pinged prematurely.
4. When ready for review: remove Draft, **assign reviewer(s)** and, if your team uses it, an **assignee** (see below).
5. Add **labels** and link **issues/epics** if that is standard for the project.

## Reviewers and assignee

- **Reviewer** — expected to review substance: correctness, style, architecture, risk.
- **Assignee** — often the author or the person driving the MR to completion; teams differ — agree locally who gets the assignee field.
- Pick people with **relevant expertise**; when unsure, ask the subsystem owner or team lead.
- If a reviewer **cannot take the MR**, they should **reassign** or say so explicitly so the author can pick someone else.
- Do not add reviewers “just because” — each person should have a clear role (primary reviewer, optional domain expert).

## Review expectations

Reviewers check:

- **Fit for purpose** and absence of unrelated churn.
- **Correctness and readability**, edge cases, failure modes.
- **Tests** — new behavior covered; regressions considered.
- **Docs and comments** where behavior is non-obvious.
- **CI** — green pipeline or explicitly agreed exceptions.

Leave feedback in **line discussions** or top-level comments; be constructive and suggest alternatives when helpful. The author **responds** to each thread: fix in code, explain, or ask follow-up questions.

## Changes requested

When a reviewer requests changes:

- The author **pushes fixes** to the same branch (or rewrites history only if the team agreed and it does not block the reviewer).
- **Resolve** discussion threads when addressed, or comment why a suggestion was not applied.
- **Request a new review** from the same reviewer after substantial updates.

Do not close the MR just to “restart” — update the branch instead unless there is a strong reason.

## Approval

- **Approve** means: at the current revision the reviewer **does not block** merge (subject to project rules; multiple approvals may be required).
- The author should **not merge** until CI is green and project rules are satisfied.

## Merge

- Merge when: **CI is green**, **required approvals** are in place, and **blocking discussions** are resolved or explicitly handled.
- **Who clicks Merge** is a team rule: author after approval vs maintainers only — ask when unsure.

### Merge method: merge commit, squash, rebase

- **Merge commit** — preserves branch history on main; good when the MR has **several meaningful commits** with good messages.
- **Squash** — combines the whole MR into **one** commit on the target branch. Prefer when history is noisy (many tiny “fix review” commits, WIP commits); edit the final message at merge time so it describes the full change.
- **Rebase + merge** (fast-forward) — linear history without a merge commit; requires a clean rebase before merge.

**When squash helps:** noisy or intermediate commits; long-lived branch with unreadable history; project policy of one commit per MR.

**When not to squash:** **multiple logical commits**, each useful for `git bisect` / `git revert`; see [CONTRIBUTING.md](CONTRIBUTING.md).

## After merge

- **Delete the remote branch** after merge for typical feature branches to avoid clutter.
- **Do not delete** long-lived shared branches or branches still referenced by open MRs or teammates — confirm with the team.

## Short checklist

| Stage | Actions |
|-------|---------|
| Before MR | Up-to-date base, tests green, commits follow conventions |
| Creation | Description, target branch, Draft until ready |
| Review | Assigned reviewers, constructive threads |
| Follow-up | Fixes, resolve threads, re-request review |
| Merge | Green CI, approvals, chosen merge strategy |
| After | Delete feature branch when safe |

**Русский:** [Запросы на слияние](../ru/MergeRequests.md)
