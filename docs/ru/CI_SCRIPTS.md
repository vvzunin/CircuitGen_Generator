# Справочник: `scripts/ci`

Текст **синхронизируется** между репозиториями Parameters, Graph и Generator. Поведение скриптов одно и то же; в job’ах GitLab подставляются переменные (`REPO_NAME`, `DOCKER_URL`, …) из `.gitlab-ci.yml`.

Общая картина конвейера: [CI_PIPELINE.md](CI_PIPELINE.md).

---

## 1. Запуск задач локально

| Скрипт | Назначение |
|--------|------------|
| **`run-task.sh`** | Одна задача: `bash scripts/ci/run-task.sh lint` (и т.д.). Переменные: `CI_RUNNER=local\|docker`, `CI_IMAGE_TAG`, `TARGET_OS`. |
| **`run-all.sh`** | Последовательный прогон основных CI-задач; порядок шагов см. внутри скрипта (в GitLab часть job’ов параллельна). |

Список задач для `run-task.sh` см. внутри скрипта (например: `lint`, `sanitize`, `static-analysis`, `coverage`, `tests`, `examples`, `docs`).

---

## 2. Сборка и публикация Docker-образов

| Скрипт | Назначение |
|--------|------------|
| **`docker-build-ci.sh`** | Сборка и push образа **CI** (`buildx`), аргументы из `docker-paths.sh` / переменных CI. |
| **`docker-build-dev.sh`** | Образ **dev** (на базе CI-образа). |
| **`docker-build-release.sh`** | Образ **release**. |
| **`docker-registry-login.sh`** | `docker login` в registry CI (переменные GitLab CI/CD). |
| **`docker-skip-if-unchanged.sh`** | `docker manifest inspect` + `docker-context-changed.sh`; exit 0 — пропустить сборку. Аргумент: `ci` \| `dev` \| `release`. |
| **`docker-context-changed.sh`** | Сравнение `git diff` по путям, влияющим на слой образа; аргумент: `ci` \| `dev` \| `release`. |
| **`docker-hub-proxy-image.sh`** | Переписывает короткую ссылку Docker Hub (`ubuntu:24.04`) в путь Harbor proxy (`REGISTRY_URL`/`DOCKER_HUB_PROXY_PROJECT`). |

---

## 3. Генерация и проверка `.gitlab-ci.yml`

| Скрипт | Назначение |
|--------|------------|
| **`generate-gitlab-os-matrix.sh`** | Генерация job’ов матрицы ОС между маркерами в `.gitlab-ci.yml`. Режимы: без аргументов (stdout), `--write`, `--check`. |

---

## 4. Проверки кода (основные entrypoint’ы)

| Скрипт | Назначение |
|--------|------------|
| **`lint.sh`** | Линт (формат, правила проекта). |
| **`static-analysis.sh`** | Статический анализ (например cppcheck). |
| **`sanitize.sh`** | Сборка/тесты со санитайзерами. |
| **`tests.sh`** | Запуск тестов (CTest и т.п.). |
| **`coverage.sh`** | Покрытие кода. |
| **`examples.sh`** | Сборка/запуск примеров. |
| **`docs.sh`** | Сборка документации в CI. |

---

## 5. Образы ОС и полные проверки

| Скрипт | Назначение |
|--------|------------|
| **`os-image-build-push.sh`** | Сборка «чистого» образа ОС и push в registry (сценарии os-check). |
| **`os-full-check.sh`** | Полная проверка на образе ОС (install-deps, прогон проверок). |

---

## 6. Прочее

| Скрипт | Назначение |
|--------|------------|
| **`create-gitlab-release.sh`** | Создание GitLab Release (стадия **release**, теги). |
| **`apk-install-with-retry.sh`** | Установка пакетов **apk** в Alpine с повторами (вспомогательный shell для `before_script`). |

---

<a id="docker-prune-runner-windows"></a>

## 7. Обслуживание runner (Windows): `docker-prune-keep-bases.ps1`

PowerShell-скрипт для **Windows 11** с **Docker Desktop (WSL2)** на хостах с **GitLab Runner**: снимает накопленные **небазовые** образы и при необходимости **сжимает** `docker_data.vhdx`, чтобы на томе Windows реально освободилось место. **Не** является шагом `.gitlab-ci.yml`; это ручное или плановое обслуживание машины runner’а.

**Исполняемый файл:** `scripts/ci/docker-prune-keep-bases.ps1` (каталог `scripts/ci` синхронизируется между **Parameters**, **Graph** и **Generator**).

**English:** тот же раздел в [docs/en/CI_SCRIPTS.md](../en/CI_SCRIPTS.md#docker-prune-runner-windows).

### Назначение

| Проблема | Что делает скрипт |
|----------|-------------------|
| Много CI-образов и тегов из частного registry на машине runner’а | Удаляет их через `docker rmi`, оставляя типовые базовые образы |
| После `docker rmi` в проводнике **не** растет свободное место на `C:` | Опционально: `Optimize-VHD` для `docker_data.vhdx` |

### Требования

**Очистка образов:** PowerShell 5.1+, Docker CLI в `PATH`; администратор **не** обязателен.

**Сжатие VHDX (`-CompactDockerDataVhdx`):** PowerShell **от администратора**, модуль **Hyper-V** (`Optimize-VHD`), Docker Desktop.

### Два этапа работы

**Очистка (по умолчанию):** `docker image prune -f` (если не `-SkipDanglingPrune`); затем по каждому тегу сравнение **REPOSITORY** с правилами «оставить» — иначе `docker rmi repository:tag`; в конце `docker system df`. Если образ занят контейнером, `docker rmi` даст ошибку — это ожидаемо.

**Сжатие VHDX:** корректный выход Docker Desktop (`--quit`, ожидание до `DockerQuitWaitSeconds`), `wsl --shutdown` и пауза `WslShutdownWaitSeconds`, затем `Optimize-VHD -Mode Full` для `%LOCALAPPDATA%\Docker\wsl\disk\docker_data.vhdx` (или `-DockerDataVhdxPath`). После сжатия **запустите Docker вручную**. Удаление слоев освобождает место *внутри* VHDX; без compact размер файла на NTFS не уменьшается.

### Что остается по умолчанию

Образ сохраняется, если **REPOSITORY** совпадает с regex: `ubuntu`, `debian`, `fedora`, `docker` (в т.ч. dind), `alpine`, `busybox` (в т.ч. `docker.io/library/…`), либо `registry.gitlab.com/gitlab-org/release-cli`. Остальное удаляется. Свои исключения — **`-ExtraKeepPattern`**.

### Параметры

| Параметр | Назначение |
|----------|------------|
| `-KeepRepositoryRegex` | Свой список regex «оставить» |
| `-ExtraKeepPattern` | Дополнительные regex |
| `-SkipDanglingPrune` | Без `docker image prune -f` |
| `-SkipImagePrune` | Только compact (вместе с `-CompactDockerDataVhdx`) |
| `-CompactDockerDataVhdx` | Сжать `docker_data.vhdx` |
| `-DockerDataVhdxPath` | Путь к `.vhdx` |
| `-DockerQuitWaitSeconds` / `-WslShutdownWaitSeconds` | Таймауты (по умолчанию 90 / 15) |
| `-WhatIf` / `-Confirm` | `ShouldProcess` |

### Типовые команды

```powershell
cd <корень_репозитория>
.\scripts\ci\docker-prune-keep-bases.ps1 -WhatIf
.\scripts\ci\docker-prune-keep-bases.ps1
.\scripts\ci\docker-prune-keep-bases.ps1 -CompactDockerDataVhdx   # от администратора
.\scripts\ci\docker-prune-keep-bases.ps1 -ExtraKeepPattern '^mcr\.microsoft\.com/'
.\scripts\ci\docker-prune-keep-bases.ps1 -SkipImagePrune -CompactDockerDataVhdx
```

### Встроенная справка

```powershell
Get-Help .\scripts\ci\docker-prune-keep-bases.ps1 -Full
```

Текст совпадает с комментариями в начале `.ps1`.

### Частые вопросы

Долгое выполнение / «висящий» `docker system df` — возможны на больших хранилищах и медленном диске. Свободное место на `C:` не увеличилось после `rmi` — нужен **`-CompactDockerDataVhdx`**. `Optimize-VHD` падает — админ, Hyper-V, полная остановка Docker/WSL. Свои базовые образы — расширьте **`-ExtraKeepPattern`** по полному `REPOSITORY`.

### Автоматизация и осторожность

Планировщик заданий Windows + `powershell.exe -File …\docker-prune-keep-bases.ps1`; для compact — «с наивысшими правами». Перед первым запуском — **`-WhatIf`**. `wsl --shutdown` останавливает **все** дистрибутивы WSL. Согласуйте окно обслуживания на общих runner’ах.

**См. также:** [CI_PIPELINE.md](CI_PIPELINE.md).

---

## 8. Связанные каталоги

| Каталог | Роль |
|---------|------|
| `scripts/config` | `supported-os.sh` — матрица ОС для CI. |
| `scripts/docker` | `docker-paths.sh` и вспомогательные скрипты путей/registry. |
| `scripts/setup` | Установка зависимостей по ОС (используются Dockerfile’ы и os-check). |
| `scripts/dev`, `scripts/release`, `scripts/docs` | Не entrypoint’ы GitLab CI из `.gitlab-ci.yml`, но связаны со сборкой и релизом; см. [SCRIPTS.md](SCRIPTS.md). |
