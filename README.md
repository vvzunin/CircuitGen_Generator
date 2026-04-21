# Генератор комбинационных схем

**Язык:** Русский | [English](README.en.md)  
**Документация:** [Русский](docs/ru/README.md) | [English](docs/en/README.md)  
**Версионирование (SemVer):** [русский](docs/ru/Versioning.md) | [English](docs/en/Versioning.md)  
**Вклад:** [русский](docs/ru/CONTRIBUTING.md) | [English](docs/en/CONTRIBUTING.md)  
**Запросы на слияние (MR):** [русский](docs/ru/MergeRequests.md) | [English](docs/en/MergeRequests.md)

![License: MIT](https://img.shields.io/github/license/vvzunin/CircuitGen_Generator)
![GitHub forks](https://img.shields.io/github/forks/vvzunin/CircuitGen_Generator)
![GitHub Repo stars](https://img.shields.io/github/stars/vvzunin/CircuitGen_Generator)
![GitHub watchers](https://img.shields.io/github/watchers/vvzunin/CircuitGen_Generator)

[![codecov](https://codecov.io/gh/vvzunin/CircuitGen_Generator/graph/badge.svg?token=U88U82QFX8)](https://codecov.io/gh/vvzunin/CircuitGen_Generator)
![GitHub Release](https://img.shields.io/github/v/release/vvzunin/CircuitGen_Generator)
![GitHub Release Date](https://img.shields.io/github/release-date/vvzunin/CircuitGen_Generator)

![GitHub commit activity](https://img.shields.io/github/commit-activity/m/vvzunin/CircuitGen_Generator)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/vvzunin/CircuitGen_Generator/latest)
![GitHub last commit](https://img.shields.io/github/last-commit/vvzunin/CircuitGen_Generator)

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/vvzunin/CircuitGen_Generator)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr/vvzunin/CircuitGen_Generator)

![Alt](https://repobeats.axiom.co/api/embed/22944c53bda053bd3f0899dc855632dc9b8c38c2.svg "Repobeats analytics image")

<font size="5">**Оглавление:**</font>
<a name="content_rus"></a> 
- [Правила именования переменных](#hacking)
- [Добавление нового генератора](#generator_add_rus)
- [Сборка программы](#generator_build_rus)
- [Запуск генерации комбинационных схем из командной строки](#generator_run_one_json_rus)
- [JSON файлы](#JSON_files)
- [Описание префикса папок генерации](#prefix)
- [Лицензия](#license)

> [!IMPORTANT]  
> Главный репозиторий проекта: https://github.com/vvzunin/CircuitGen

Проект поддерживает сборку на Linux, Windows и macOS через CMake presets.
Основной сценарий разработки и CI тестировался на Ubuntu (в том числе в WSL).
Руководство разработчика доступно по [ссылке](https://drive.google.com/file/d/1eKWMpF0Ig5r5ZI81dJjRoibctzezNE-D/view?usp=sharing).

## Установка зависимостей

Актуальные списки пакетов и доп. шаги (CMake с Kitware при необходимости, **clang-format**, **lcov** 2+ на Ubuntu 22.04, Doxygen, TeX для документации и т.д.) — в скриптах **[scripts/setup/](scripts/setup/)** по ОС из CI-матрицы, например:

- [`install-deps-ubuntu-22.04.sh`](scripts/setup/install-deps-ubuntu-22.04.sh)
- [`install-deps-ubuntu-24.04.sh`](scripts/setup/install-deps-ubuntu-24.04.sh)
- [`install-deps-debian-13.sh`](scripts/setup/install-deps-debian-13.sh)
- [`install-deps-fedora-42.sh`](scripts/setup/install-deps-fedora-42.sh) / [`install-deps-fedora-43.sh`](scripts/setup/install-deps-fedora-43.sh)

Пример: `sudo bash scripts/setup/install-deps-ubuntu-24.04.sh`.

Подробнее: [BUILDING.md](docs/ru/BUILDING.md), [SCRIPTS.md](docs/ru/SCRIPTS.md).

## Режим разработчика
<a name="hacking"></a> 

Несколько советов, которые помогут Вам создать и протестировать этот проект в качестве разработчика и потенциального участника представлены [здесь](docs/ru/HACKING.md).

[&#8593; Contents](#content_rus)

## Добавление нового генератора
<a name="generator_add_rus"></a> 

Процесс добавления нового генератора описан в отдельном [файле](docs/ru/NewGenerator.md).

[&#8593; Contents](#content_rus)

## Сборка программы
<a name="generator_build_rus"></a> 

Для сборки программы необходимо выполнить следующие команды из начальной директории:
```
bash scripts/dev/build-debug.sh
```

Для сборки покрытия:
```
bash scripts/dev/coverage.sh
```

Для релизной сборки:
```
bash scripts/release/build.sh
```

Для релизной сборки с тестами (CI parity):
```
bash scripts/release/test.sh
```

Локальная сборка dev-контейнера (по аналогии с CI) выполняется так:
```
bash scripts/docker/build-images.sh
```
По умолчанию будут собраны образы `circuitgen/generator/ubuntu-24.04/ci:local`,
`circuitgen/generator/ubuntu-24.04/dev:local` и
`circuitgen/generator/ubuntu-24.04/release:local` (см. `scripts/docker/docker-paths.sh`).
Другую ОС можно выбрать через `TARGET_OS` или `DOCKER_CI_SYSTEM`:
```
TARGET_OS=fedora-42 bash scripts/docker/build-images.sh
```
Переопределить теги и registry-префикс можно через переменные окружения:
```
CI_IMAGE_TAG=my-ci DEV_IMAGE_TAG=my-dev RELEASE_IMAGE_TAG=my-release DOCKER_CI_SYSTEM=ubuntu:24.04 bash scripts/docker/build-images.sh
```

Подробная схема сборки описана [здесь](docs/ru/BUILDING.md), мануал по скриптам — [здесь](docs/ru/SCRIPTS.md).

[&#8593; Contents](#content_rus)

## Запуск генерации комбинационных схем из командной строки
<a name="generator_run_one_json_rus"></a>
Для проведения генерации из командной строки необходимо подготовить JSON файл с описанием параметров генерации, а после выполнить следующую команду:
```
build/CircuitGenGenerator --json_path <path_to_json>
```

[&#8593; Contents](#content_rus)

## JSON файлы
<a name="JSON_files"></a>
Для генерации комбинационных схем с использованием командной строки необходимо создать JSON файл.

Подробное описание структуры файлов представлено [здесь](docs/ru/json.md).

[&#8593; Contents](#content_rus)

## Описание префикса папок генерации
<a name="prefix"></a>
Каждый генератор по окончании работы создает папки с уникальным для данного генератора префиксом.

Подробное описание префиксов папок представлено [здесь](docs/ru/GeneratorsPrefixes.md).

[&#8593; Contents](#content_rus)

# Лицензия
<a name="license"></a>

Смотрите файл с [лицензией](LICENSE).

[&#8593; Contents](#content_rus)
