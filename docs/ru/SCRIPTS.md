# Скрипты проекта

В репозитории скрипты сгруппированы по каталогам в `scripts/`.
Скрипты вызывают CMake presets и Docker-сборки, не дублируя логику конфигурации.

## Структура

```text
scripts/
  config/
    supported-os.sh
  ci/
    lint.sh
    sanitize.sh
    static-analysis.sh
    coverage.sh
    tests.sh
    examples.sh
    docs.sh
    run-task.sh
    run-all.sh
    generate-gitlab-os-matrix.sh
    docker-build-ci.sh
    docker-build-dev.sh
    docker-build-release.sh
    os-image-build-push.sh
    os-full-check.sh
  dev/
    build-debug.sh
    build-docs.sh
    build-examples.sh
    coverage.sh
    pre-push.sh
    pre-push-docker.sh
  docker/
    docker-paths.sh
    build-ci-image.sh
    build-dev-only-image.sh
    build-release-only-image.sh
    build-images.sh
  release/
    build.sh
    build-examples.sh
    test.sh
    install.sh
  setup/
    install-doxygen-llvm.sh
    install-deps-ubuntu-22.04.sh
    install-deps-ubuntu-24.04.sh
    install-deps-debian-13.sh
    install-deps-fedora-42.sh
    install-deps-fedora-43.sh
    verify-installers-docker.sh
    install-deps-for-current-os.sh
```

Помеченные секции **джобов по одной ОС** в **`.gitlab-ci.yml`** (между комментариями `BEGIN generated` / `END generated`) **генерируются** из `scripts/config/supported-os.sh` (см. ниже); правьте только `supported-os.sh` и скрипты установки `install-deps-<slug>.sh`, затем выполните **`generate-gitlab-os-matrix.sh --write`**.

## Поддерживаемые ОС и GitLab matrix

Единый список целевых ОС (slug и образ `ID:VERSION` для Docker) задается в **`scripts/config/supported-os.sh`** (`SUPPORTED_OS_ENTRIES`, `DEFAULT_TARGET_OS_SLUG`). Его используют `scripts/docker/docker-paths.sh`, Docker helper-скрипты и проверки установщиков.

В GitLab CI для каждой ОС задан отдельный джоб (`docker-images-<slug>`, `os-system-validation-main-<slug>`) в **`.gitlab-ci.yml`** между маркерами `BEGIN generated` / `END generated` (без `parallel.matrix`, чтобы схемы в IDE не ругались). **Не правьте сгенерированные строки вручную** — они должны совпадать с выводом генератора.

Путь: **`scripts/ci/generate-gitlab-os-matrix.sh`**

- без аргументов — печатает сгенерированные блоки в stdout;
- **`--write`** — перезаписывает помеченные секции в `.gitlab-ci.yml`;
- **`--check`** — сравнивает маркеры в закоммиченном файле с выводом генератора (используется в джобе `gitlab-os-matrix-check` в `.gitlab-ci.yml`).

После изменения `scripts/config/supported-os.sh` (или добавления `scripts/setup/install-deps-<slug>.sh`) выполните:

```sh
bash scripts/ci/generate-gitlab-os-matrix.sh --write
```

и закоммитьте обновленный `.gitlab-ci.yml` вместе с правками.

### Практика при добавлении новой ОС

Ниже — типовой порядок действий при появлении новой целевой системы в матрице (не только правка списка в `supported-os.sh`).

1. **Запись в `supported-os.sh`.** Добавьте элемент в `SUPPORTED_OS_ENTRIES` в виде `"<slug>|<ID>:<VERSION>"`. Значения `ID` и `VERSION_ID` должны совпадать с тем, что дает `/etc/os-release` в базовом Docker-образе (для `KEY="${ID}:${VERSION_ID}"` в скриптах).

2. **Установщик зависимостей для CI.** Создайте `scripts/setup/install-deps-<slug>.sh` (разумно взять за основу ближайшую ОС и поправить имена пакетов/репозитории). После шага 1 скрипт `install-deps-for-current-os.sh` начнет выбирать его для `dockerfile/Dockerfile.ci` без отдельного `case`.

3. **Минимальный toolchain для release.** Допишите ветку для того же `ID:VERSION` в **`scripts/docker/install-release-toolchain.sh`** (образ `dockerfile/Dockerfile.release` вызывает только этот скрипт; без новой ветки сборка release на новой базе завершится ошибкой, даже если пункт 1 выполнен).

4. **GitLab matrix.** Выполните `bash scripts/ci/generate-gitlab-os-matrix.sh --write` и включите в коммит обновленный **`.gitlab-ci.yml`**.

5. **Дефолт и ссылки в `.gitlab-ci.yml`.** Если меняете «главную» ОС для переменных по умолчанию, обновите **`DEFAULT_TARGET_OS_SLUG`** в `supported-os.sh` и проверьте вручную поля в **`.gitlab-ci.yml`**: например `TARGET_OS` в джобах `os-system-validation-main-*` (ручной запуск на default branch), а также `DOCKER_CI_IMAGE` / `DOCKER_DEV_IMAGE` / `DOCKER_RELEASE_IMAGE` в секции `variables`, если там зашит slug образа.

6. **Проверка.** Запустите `bash scripts/setup/verify-installers-docker.sh <slug>` и при необходимости локальную сборку образов, например `TARGET_OS=<slug> bash scripts/docker/build-images.sh`.

## Общие рекомендации

- Запускайте скрипты из корня репозитория.
- Для надежности используйте явный вызов через `bash`.
- Большинство параметров настраивается через переменные окружения.
- Для полного набора скриптов требуются инструменты: `cmake`, `ninja`, `clang-format` (пин **18.1.8** через PyPI в `install-clang-format-ci.sh`), `codespell`, `doxygen`, `graphviz`, LaTeX toolchain (`pdflatex`/`makeindex`), `docker` (для docker-скриптов).

## Скрипт: pre-push проверки

Путь: `scripts/dev/pre-push.sh`

Назначение:
- проверка базовых инструментов (`cmake`, `ninja`, `codespell`);
- чистая локальная сборка;
- `format-check` и `spell-check`;
- сборка и тесты для `dev` и `release-ci`.

Запуск:

```sh
bash scripts/dev/pre-push.sh
```

Параметры:
- `JOBS` — количество потоков для сборки (по умолчанию `nproc`).

Пример:

```sh
JOBS=8 bash scripts/dev/pre-push.sh
```

## Скрипт: простая Debug-сборка

Путь: `scripts/dev/build-debug.sh`

Назначение:
- конфигурация preset `dev`;
- сборка проекта в режиме Debug.

Запуск:

```sh
bash scripts/dev/build-debug.sh
```

Параметры:
- `JOBS` — количество потоков для сборки.

## Скрипт: локальная сборка документации

Путь: `scripts/dev/build-docs.sh`

Назначение:
- конфигурация preset **`dev`** (для `compile_commands.json`, нужного libclang в Doxygen);
- запуск **`scripts/docs/build-doxygen-lang-variants.sh`** — тот же пайплайн, что и **`scripts/ci/docs.sh`**, с выводом в **`build/dev/docs/{html,xml,latex,pdf}/{en,ru}/`** (по умолчанию английский и русский).

Запуск:

```sh
bash scripts/dev/build-docs.sh
```

Параметры:
- `DOXYGEN_LANG_VARIANTS` — необязательно; по умолчанию `en=english;ru=russian`. Пример одного языка: `DOXYGEN_LANG_VARIANTS=en=english`.
- `DOXYGEN_SKIP_DOT_GRAPHS`, `DOXYGEN_SKIP_REFMAN_PDF` — как в CI (ускорение итераций).

Вывод в духе CI в `build/docs/.../{en,ru}/`: **`bash scripts/ci/docs.sh`**.

Цель CMake **`docs`** (только при **`BUILD_MCSS_DOCS=ON`**) использует **`cmake/docs.cmake`** для **одного** языка в `build/dev/docs/html` (плоская структура); язык — **`DOXYGEN_DOCUMENTATION_LANGUAGE`**.

## Скрипт: локальное покрытие

Путь: `scripts/dev/coverage.sh`

Назначение:
- конфигурация и сборка preset `coverage`;
- запуск тестов;
- генерация отчета покрытия.

Запуск:

```sh
bash scripts/dev/coverage.sh
```

Параметры:
- `JOBS` — количество потоков для сборки.

## Скрипт: pre-push проверки в Docker

Путь: `scripts/dev/pre-push-docker.sh`

Назначение:
- запускает тот же набор проверок, что и `scripts/dev/pre-push.sh`;
- выполняет проверки внутри локального dev-образа Docker;
- монтирует текущий репозиторий в контейнер и запускает с вашим UID/GID.

Запуск:

```sh
bash scripts/dev/pre-push-docker.sh
```

Параметры:
- `DEV_IMAGE_TAG` — полное имя dev-образа (по умолчанию через `scripts/docker/docker-paths.sh`, например `circuitgen/generator/ubuntu-24.04/dev:local`);
- `TARGET_OS` — см. `scripts/docker/docker-paths.sh`;
- `JOBS` — количество потоков для сборки внутри контейнера.

Пример:

```sh
TARGET_OS=ubuntu-22.04 DEV_IMAGE_TAG=circuitgen/generator/ubuntu-22.04/dev:local JOBS=8 bash scripts/dev/pre-push-docker.sh
```

## Вспомогательный модуль: пути Docker-образов

Путь: `scripts/docker/docker-paths.sh`

Назначение:
- единые правила имен образов, совпадающие с `.gitlab-ci.yml`:
  `$DOCKER_URL/$IMAGE_OS_SUFFIX/ci:<tag>`, `$DOCKER_URL/$IMAGE_OS_SUFFIX/dev:<tag>`,
  `$DOCKER_URL/$IMAGE_OS_SUFFIX/release:<tag>`;
- выбор ОС через `TARGET_OS` или `DOCKER_CI_SYSTEM`;
- используется скриптами в `scripts/docker/`, `scripts/ci/docker-build-*.sh`, `scripts/ci/docs.sh`, `scripts/ci/run-task.sh`, `scripts/dev/pre-push-docker.sh`.

## Скрипт: сборка Docker образов (CI + DEV + RELEASE)

Путь: `scripts/docker/build-images.sh`

Назначение:
- собрать локальный CI-образ из `dockerfile/Dockerfile.ci`;
- собрать локальный dev-образ из `dockerfile/Dockerfile.dev` на базе CI-образа;
- собрать локальный release-образ из `dockerfile/Dockerfile.release` на легком базовом образе ОС
  (только компилятор, CMake, Ninja, git и т.п. — без Doxygen/TeX и прочего dev/CI-стека).

Имена образов задаются через `scripts/docker/docker-paths.sh` и совпадают с `.gitlab-ci.yml`:
`$DOCKER_URL/$IMAGE_OS_SUFFIX/ci:<tag>`, `$DOCKER_URL/$IMAGE_OS_SUFFIX/dev:<tag>`,
`$DOCKER_URL/$IMAGE_OS_SUFFIX/release:<tag>`.

Запуск:

```sh
bash scripts/docker/build-images.sh
```

Переменные окружения:
- `DOCKERFILE_CI_NAME` (по умолчанию `dockerfile/Dockerfile.ci`);
- `DOCKERFILE_DEV_NAME` (по умолчанию `dockerfile/Dockerfile.dev`);
- `DOCKERFILE_RELEASE_NAME` (по умолчанию `dockerfile/Dockerfile.release`);
- `DOCKERFILE_CI` (алиас для обратной совместимости, приоритетнее `DOCKERFILE_CI_NAME`);
- `DOCKERFILE_DEV` (алиас для обратной совместимости, приоритетнее `DOCKERFILE_DEV_NAME`);
- `DOCKERFILE_RELEASE` (алиас для обратной совместимости, приоритетнее `DOCKERFILE_RELEASE_NAME`);
- `DOCKER_URL` (по умолчанию `circuitgen/generator`, либо `${REGISTRY_URL}/${GROUP_NAME}/${REPO_NAME}` если заданы);
- `TARGET_OS` — slug из `scripts/config/supported-os.sh` (задает `DOCKER_CI_SYSTEM`);
- `DOCKER_CI_SYSTEM` (по умолчанию `ubuntu:24.04`; из него выводится `IMAGE_OS_SUFFIX`);
- `LOCAL_IMAGE_TAG` — суффикс тега для локальных образов (по умолчанию `local`);
- `CI_IMAGE_TAG` / `DEV_IMAGE_TAG` / `RELEASE_IMAGE_TAG` — полные имена образов (если не заданы, вычисляются из путей выше).

Пример:

```sh
TARGET_OS=fedora-42 bash scripts/docker/build-images.sh
```

## Скрипт: сборка только Docker CI-образа

Путь: `scripts/docker/build-ci-image.sh`

Назначение:
- собрать только локальный CI-образ из `dockerfile/Dockerfile.ci`.

Запуск:

```sh
bash scripts/docker/build-ci-image.sh
```

## Скрипт: сборка только Docker dev-образа

Путь: `scripts/docker/build-dev-only-image.sh`

Назначение:
- собрать только локальный dev-образ из `dockerfile/Dockerfile.dev`;
- использовать уже существующий CI-образ как базовый.

Запуск:

```sh
bash scripts/docker/build-dev-only-image.sh
```

## Скрипт: сборка только Docker release-образа

Путь: `scripts/docker/build-release-only-image.sh`

Назначение:
- собрать только локальный release-образ из `dockerfile/Dockerfile.release`;
- базовый образ задается через `DOCKER_CI_SYSTEM` / `TARGET_OS` (`BASE_IMAGE` в Dockerfile), не через fat CI-образ.

Запуск:

```sh
bash scripts/docker/build-release-only-image.sh
```

## Скрипты Release

- `scripts/release/build.sh`  
  Оптимизированная release-сборка без тестов.
- `scripts/release/test.sh`  
  Release-сборка с тестами через preset `release-ci`.
- `scripts/release/install.sh`  
  Установка артефактов release-сборки.
- `scripts/release/suggest-next-version.sh`  
  Предлагаемый тег `vX.Y.Z` по коммитам после последнего SemVer-тега (Conventional Commits); см. [Versioning.md](Versioning.md).

Примеры:

```sh
bash scripts/release/build.sh
bash scripts/release/test.sh
INSTALL_PREFIX=prefix/release bash scripts/release/install.sh
bash scripts/release/suggest-next-version.sh --verbose
```

## Скрипты установки зависимостей

- `scripts/setup/install-deps-ubuntu-22.04.sh`  
  Устанавливает недостающие зависимости для Ubuntu 22.04.
- `scripts/setup/install-deps-ubuntu-24.04.sh`  
  Устанавливает недостающие зависимости для Ubuntu 24.04.
- `scripts/setup/install-deps-debian-13.sh`  
  Устанавливает недостающие зависимости для Debian 13 (trixie). Пин `clang-format` **18.1.8** через `install-clang-format-ci.sh` (колёсо PyPI), как в остальных образах CI.
- `scripts/setup/install-deps-fedora-42.sh`  
  Устанавливает недостающие зависимости для Fedora Workstation 42.
- `scripts/setup/install-deps-fedora-43.sh`  
  Устанавливает недостающие зависимости для Fedora Workstation 43.

Все install-скрипты:
- проверяют текущий дистрибутив и версию;
- проверяют, какие пакеты уже установлены;
- устанавливают только недостающие пакеты;
- проверяют наличие `codespell` и ставят его через `pip`, если пакетный менеджер его не дал;
- устанавливают `doxygen` из исходников с `-Duse_libclang=ON` (версия по умолчанию `1.13.2`), как в `dockerfile/Dockerfile.ci`.

Отдельный скрипт:
- `scripts/setup/install-doxygen-llvm.sh`  
  Сборка и установка Doxygen с LLVM/libclang поддержкой.

Проверка install-скриптов в Docker-образах:

```sh
bash scripts/setup/verify-installers-docker.sh
```

Проверка в одном конкретном образе:

```sh
bash scripts/setup/verify-installers-docker.sh ubuntu-24.04
```

Проверяемые системы совпадают со списком slug в `scripts/config/supported-os.sh` (и с матрицей в помеченных секциях `.gitlab-ci.yml` после `generate-gitlab-os-matrix.sh --write`).

## CI скрипты

Скрипты в `scripts/ci/` используются в `.gitlab-ci.yml` и являются единым интерфейсом для CI-джобов.

Для локального запуска CI-этапов доступны два режима:
- `CI_RUNNER=local` — запуск в текущей системе;
- `CI_RUNNER=docker` — запуск внутри локального CI-образа Docker.

Для `scripts/ci/docs.sh` дополнительно доступны параметры:
- `DOCS_RUNNER=auto|local|docker` (по умолчанию `auto`).
- `DOXYGEN_LANG_VARIANTS` — по умолчанию **`en=english;ru=russian`**. Формат `abbr=section1 section2;abbr2=...`; для каждого варианта — отдельное дерево `build/docs/{html,xml,latex,pdf}/<abbr>/`.
- `DOXYGEN_SKIP_DOT_GRAPHS`, `DOXYGEN_SKIP_REFMAN_PDF` — передаются в `cmake/docs-ci.cmake`.
- `DOXYGEN_ENABLED_SECTIONS` — устаревшее значение по умолчанию `english`, если явно не заданы варианты; при использовании **`DOXYGEN_LANG_VARIANTS`** секции задаются **для каждого варианта**. В `cmake/docs-ci.cmake` выставляется **`OUTPUT_LANGUAGE`** (русский, если для варианта секции ровно `russian`, иначе английский).

### Универсальные запускаторы

- `scripts/ci/run-task.sh <task>`  
  Запускает один CI-этап (`lint`, `sanitize`, `static-analysis`, `coverage`, `tests`, `examples`, `docs`) в выбранном режиме.
- `scripts/ci/run-all.sh`  
  Запускает полный CI-пайплайн проверок: `lint -> static-analysis -> sanitize -> coverage -> tests -> examples -> docs`.

Примеры:

```sh
# Запуск этапа в текущей системе
CI_RUNNER=local bash scripts/ci/run-task.sh lint

# Запуск этапа внутри локального Docker CI-образа
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-task.sh tests

# Полный прогон CI-этапов в Docker
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-all.sh
```

### Проверки и тесты

- `scripts/ci/lint.sh`  
  Запускает форматирование и орфографические проверки через CMake-скрипты, а также валидирует `.clang-format` и проверяет версию `clang-format`.
- `scripts/ci/sanitize.sh`  
  Конфигурирует пресет `ci-sanitize`, собирает и запускает тесты с санитайзерами.
- `scripts/ci/static-analysis.sh`  
  Собирает пресет `ci-static-analysis` (clang-tidy при компиляции) и запускает `cppcheck` по `compile_commands.json` (см. комментарии в скрипте).
- `scripts/ci/coverage.sh`  
  Конфигурирует пресет `ci-coverage`, запускает тесты и генерирует coverage-отчет.
- `scripts/ci/tests.sh`  
  Собирает `release-ci`, устанавливает артефакты и запускает тесты с JUnit-отчетом.
- `scripts/ci/examples.sh`  
  Собирает примеры в конфигурации **Debug** (`ci-examples-dev`) и **Release** (`release-examples`), затем запускает цель **`run-examples`** (см. `examples/CMakeLists.txt`, `docs/ru/BUILDING.md`).
- `scripts/ci/docs.sh`  
  Генерирует документацию в CI через `cmake/docs-ci.cmake` c включенным libclang-парсером Doxygen.  
  HTML через `m.css`; по умолчанию каталоги
  `build/docs/html/{en,ru}`, `build/docs/xml/{en,ru}` и т.д.
  Поддержка `dot` (Graphviz) настраивается автоматически в CMake-генерации
  документации (`HAVE_DOT`/`DOT_PATH`).
  По умолчанию **`DOXYGEN_LANG_VARIANTS="en=english;ru=russian"`** (см. `scripts/docs/build-doxygen-lang-variants.sh`).
  Поддерживаются языковые условные блоки Doxygen через алиасы
  `\english ... \lang_end` и `\russian ... \lang_end` (секции Doxygen `\if`).
  При локальном запуске по умолчанию использует Docker-образ `CI_IMAGE_TAG`
  (по умолчанию `circuitgen/generator/ubuntu-24.04/ci:local` через `scripts/docker/docker-paths.sh`).
  Скрипт завершится с ошибкой, если обнаружит Doxygen без поддержки `CLANG_ASSISTED_PARSING`.

### Согласованность matrix GitLab

- `scripts/ci/generate-gitlab-os-matrix.sh`  
  Обновляет помеченные секции матрицы в `.gitlab-ci.yml` из `scripts/config/supported-os.sh`. В пайплайне джоб `gitlab-os-matrix-check` запускает `--check`: при расхождении нужно выполнить `--write` и закоммитить файл.

### Docker образы в CI

- `scripts/ci/docker-build-ci.sh`  
  Собирает и публикует CI-образ (в CI используется matrix по поддерживаемым ОС).
- `scripts/ci/docker-build-dev.sh`  
  Собирает и публикует dev-образ на базе соответствующего CI-образа той же ОС.
- `scripts/ci/docker-build-release.sh`  
  Собирает и публикует release-образ для выбранной ОС (легкий базовый образ, см. `dockerfile/Dockerfile.release`).

Оба Docker-скрипта поддерживают переменные окружения из `.gitlab-ci.yml`:
`DOCKERFILE_CI_NAME`, `DOCKERFILE_DEV_NAME`, `DOCKERFILE_RELEASE_NAME`, `DOCKER_CI_SYSTEM`,
`DOCKER_CI_TAG`, `REGISTRY_URL`, `GROUP_NAME`, `REPO_NAME`, `DOCKER_URL`,
`DOCKER_CI_IMAGE`, `DOCKER_DEV_IMAGE`, `DOCKER_RELEASE_IMAGE`.

### Проверки по ОС (matrix)

- `scripts/ci/os-image-build-push.sh`  
  Для `TARGET_OS` собирает отдельный образ `.../os-<target>:<tag>` на базе соответствующей ОС,
  запускает внутри него `scripts/setup/install-deps-*.sh` и публикует образ в registry.
- `scripts/ci/os-full-check.sh`  
  Запускает в опубликованном OS-образе полный CI-прогон `scripts/ci/run-all.sh`
  (`lint -> static-analysis -> sanitize -> coverage -> tests -> examples -> docs`) и тем самым проверяет все шаги компиляции/тестов/документации.

Правила запуска в `.gitlab-ci.yml`:
- в `main` проверки выполняются для всех поддерживаемых ОС;
- в остальных ветках выполняется только `ubuntu-24.04`.

**English:** [Project scripts](../en/SCRIPTS.md)
