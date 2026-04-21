# GitLab CI: конвейер и архитектура

Документ описывает конвейер **GitLab CI/CD** этого репозитория (CircuitGen: Parameters, Graph или Generator). Файл **синхронизируется** между тремя репозиториями; отличие только в переменной **`REPO_NAME`** в `.gitlab-ci.yml` (`parameters` / `graph` / `generator`) и в путях образов в registry.

Подробный справочник по скриптам: [CI_SCRIPTS.md](CI_SCRIPTS.md).

---

## 1. Общая архитектура

- **Оркестратор:** GitLab Runner с **Docker executor**, тег **`docker`**.
- **Сборка образов:** job’ы на образе **`docker:27`** (через proxy cache registry) + сервис **Docker-in-Docker (dind)** `docker:27-dind`. Нужен Runner с **`privileged = true`**.
- **Проверки кода (lint, тесты, …):** job’ы на **`$DOCKER_CI_IMAGE`** — образ CI, собранный из `dockerfile/Dockerfile.ci` и опубликованный в ваш registry (`REGISTRY_URL` / `GROUP_NAME` / `REPO_NAME`).
- **Кэш Docker Hub / GitLab:** в `.gitlab-ci.yml` задаются проекты Harbor **`DOCKER_HUB_PROXY_PROJECT`** и **`DOCKER_GITLAB_PROXY_PROJECT`**; client/dind и часть баз тянутся через proxy, чтобы снизить лимиты и ускорить pull.

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

### Диаграмма стадий

Порядок секции **`stages:`** в `.gitlab-ci.yml`: следующая стадия начинается после завершения всех заданий предыдущей стадии (с учетом правил GitLab на пропуски и ручные задания).

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

### Основной поток зависимостей (Ubuntu 24.04)

Упрощенная цепочка **`needs:`** для дефолтного образа CI: проверка YAML, сборка и push **`ci`**, затем `check` / `test`; далее матрица образов для других ОС и **`docker-release`** (в основном на тегах, после успешных тестов и примеров).

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

Вторичные job’ы **`docker-images-*`** (не Ubuntu 24.04) в **`needs`** указывают только **`docker-images-ubuntu-24.04`**, **`tests`** и **`examples`** — job **`coverage`** для них не объявлен (см. `.gitlab-ci.yml`).

---

## 2. Правила workflow (`.gitlab-ci.yml`)

- Коммит с **`[skip ci]`** в сообщении — pipeline **не** запускается.
- Черновики MR (**Draft** / флаг draft) — pipeline **не** запускается.
- Переменная **`DOCKER_CI_TAG`** (тег образов `ci` / `dev` / `release` в registry) задается правилами `workflow` в зависимости от источника pipeline (упрощенно, как в `.gitlab-ci.yml`):
  - **тег** репозитория → `DOCKER_CI_TAG = CI_COMMIT_TAG`;
  - **merge request** при истинном **`CI_COMMIT_REF_SLUG`** → `DOCKER_CI_TAG = CI_COMMIT_REF_SLUG`;
  - **merge request** иначе → `DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`;
  - **push в ветку** (есть `CI_COMMIT_BRANCH`) → `DOCKER_CI_TAG = CI_COMMIT_REF_SLUG`;
  - **fallback** (`when: always`) → `DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`.

Точные условия смотрите в начале `.gitlab-ci.yml` в репозитории.

---

## 3. Стадии (stages)

| Стадия | Назначение |
|--------|------------|
| **validate** | Проверка, что сгенерированные блоки `.gitlab-ci.yml` совпадают с `scripts/config/supported-os.sh` (`generate-gitlab-os-matrix.sh --check`). |
| **docker-ubuntu** | Сборка и push образов **ci** (и при правилах — **dev**) для **Ubuntu 24.04** — основной источник `$DOCKER_CI_IMAGE` для последующих стадий. |
| **check** | Линт, статический анализ, санитайзеры в образе CI по умолчанию (Ubuntu 24.04). |
| **test** | Юнит-тесты, покрытие, примеры в том же образе CI. |
| **docker-matrix** | Образы **ci** для вторичных ОС после успешных **`tests`** и **`examples`** на Ubuntu 24.04; **release**-образы на тегах (`docker-release-*`, те же зависимости). |
| **check-os** / **test-os** | Те же проверки на **вторичных ОС** (ограничения `rules`, см. `.secondary-os-matrix-rules`). |
| **os-check** | Полная проверка установки зависимостей и сценариев на «чистых» образах ОС (`os-image-build-push` + `os-full-check`), увеличенный `timeout`. |
| **docs** | Сборка документации (Doxygen и др.) по `rules` / изменениям путей. |
| **release** | Создание GitLab Release на тегах (`create-gitlab-release.sh`). |

---

## 4. Матрица ОС и генерация YAML

- Единый источник списка ОС: **`scripts/config/supported-os.sh`**.
- Скрипт **`scripts/ci/generate-gitlab-os-matrix.sh`** переписывает помеченные блоки в **`.gitlab-ci.yml`** (`# BEGIN generated` … `# END generated`).
- После изменения поддерживаемых ОС выполните **`--write`**, затем закоммитьте обновленный `.gitlab-ci.yml`. В CI стадия **validate** гоняет **`--check`**.

---

## 5. Образы Docker в CI

- **CI:** `Dockerfile.ci`, переменные `DOCKERFILE_CI_NAME`, `DOCKER_CI_SYSTEM`, публикация в `$DOCKER_URL/<os>/ci:$DOCKER_CI_TAG`.
- **Dev:** `Dockerfile.dev` — сборка в job’ах ограничена **тегами и default branch** (см. встроенный `if` в `.gitlab-ci.yml`); локально на runner после job образ **dev** удаляется в **`after_script`**, чтобы не забивать диск dind.
- **Release:** `Dockerfile.release` — для тегов; локальный образ **release** также снимается в **`after_script`**.
- Пропуск лишних пересборок: **`docker-skip-if-unchanged.sh`** вызывается из `docker-build-*.sh` при **`CI`**. Учитываются только пути из **`docker-context-changed.sh`** (для `ci` — `Dockerfile.ci`, `scripts/setup`, …); каталог **`docs/`** к контексту CI-образа не относится. Пропуск возможен, если в registry уже есть **`$DOCKER_CI_IMAGE`** или тег **`ci:$CI_COMMIT_SHORT_SHA`**, и с merge base до текущего коммита эти пути не менялись. **Если нужного тега в registry ещё нет** (первый прогон ветки/MR, очистка registry, сбой прошлого push, либо **`DOCKER_CI_TAG = CI_COMMIT_SHORT_SHA`** на каждый коммит MR — см. `workflow` в `.gitlab-ci.yml`), job всё равно выполнит полную **`docker build`**, даже при правках только в `docs/`.
- **`resource_group`** на docker/os job’ах сериализует сборки по проекту и ОС, чтобы не пересекались push’и.

---

## 6. Локальный запуск как в CI

- **`bash scripts/ci/run-task.sh <task>`** — одна задача (`lint`, `tests`, …): локально или в контейнере (`CI_RUNNER=docker`, `CI_IMAGE_TAG=...`).
- **`bash scripts/ci/run-all.sh`** — последовательный прогон набора скриптов; порядок см. в скрипте (в GitLab часть шагов параллельна).

Подробнее: [CI_SCRIPTS.md](CI_SCRIPTS.md), [SCRIPTS.md](SCRIPTS.md), [HACKING.md](HACKING.md).

---

## 7. Обслуживание runner (Windows)

Для хостов с **Docker Desktop (WSL2)** и накоплением данных используйте **`scripts/ci/docker-prune-keep-bases.ps1`**. Полное описание — в [CI_SCRIPTS.md §7](CI_SCRIPTS.md#docker-prune-runner-windows) (рус.) / [англ. версия](../en/CI_SCRIPTS.md#docker-prune-runner-windows). Это **не** шаг GitLab job’а по умолчанию, а ручное/плановое обслуживание диска.
