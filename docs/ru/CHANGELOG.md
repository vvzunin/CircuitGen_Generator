# Журнал изменений

Все заметные изменения **CircuitGen Generator** документируются в этом файле.

Формат основан на [Keep a Changelog](https://keepachangelog.com/ru/1.1.0/); версии соответствуют [Semantic Versioning](https://semver.org/lang/ru/) — см. [Versioning.md](Versioning.md).

**English:** [CHANGELOG.md](../en/CHANGELOG.md)

## [Unreleased]

### Added

- Генерация на **Chisel** и интеграция в CLI.
- Примеры API и JSON (`examples/`); флаг `save_circuit_parameters_json`.
- Деплой Doxygen-документации на Synology NAS из CI.
- Обзор функционала в `docs/ru|en/FUNCTIONALITY.md`.
- Журнал изменений в `docs/ru|en/CHANGELOG.md`.

### Changed

- Крупный рефакторинг CMake, GitLab CI (мульти-ОС), Docker и `docs/` (синхронизация с Graph/Parameters).
- Обновление зависимости **CircuitGen Graph** (v1.5.2+); правки API.
- Документация: `BUILDING`, CI markdown, `NewGenerator`, README.

### Fixed

- `runGeneration`: вызов callback во всех ветках.
- Генетический/автоматный генератор: слияние init/transition DFF.
- CI: Java/Chisel sanitize, LaTeX/PDF, NAS Auth v3.

---

## [1.3.0] - 2024-08-02

### Added

- Интеграция **easylogging++**; подготовка тестов к структурированному логированию.

### Changed

- Оптимизации CMake; ручной запуск workflow на любой ветке.
- Версия проекта.

### Fixed

- `empty_project`; команда форматирования; лишние логи.

---

## [1.2.0] - 2024-07-01

### Changed

- Обновление **clang**, codecov, версии Graph.

### Fixed

- Параллельный запуск генерации; тесты.

---

## [1.1.0] - 2024-06-09

### Added

- Расширение набора генераторов и сценариев пакетной генерации.
- Улучшения конвейера документации (Doxygen/HTML).

### Changed

- Крупное обновление CI, CMake и структуры проекта.

### Fixed

- Множественные исправления генераторов, тестов и документации.

---

## [1.0.1] - 2024-04-05

### Changed

- GitHub/GitLab CI; Doxygen (`Doxyfile.in`); README.

### Fixed

- Ошибки сборки и генерации.

---

## [1.0.0-alpha] - 2024-04-02

### Added

- Подключение как CMake-пакет (`FetchContent` / find_package).
- Пример использования CMake package; обновление `BUILDING.md`.

### Changed

- README и структура установки.

---

## [0.1.4-alpha] - 2024-02-13

### Added

- `min_level`; оптимизации памяти.

### Fixed

- Ошибки в RandLevel и смежных алгоритмах.

---

## [0.1.3-alpha] - 2024-02-02

### Changed

- `CMakeLists.txt`.

---

## [0.1.2-alpha] - 2024-01-29

### Added

- Формат **bench**; проверка входов/выходов схемы.

### Changed

- README; RandLevel.

---

## [0.1.1-alpha] - 2024-01-26

### Added

- Образцы JSON; публикации по методам генерации.

### Changed

- `generatorAPI`; комментарии в коде.

### Fixed

- Ошибки API.

---

## [0.1.0-alpha] - 2024-01-25

> Git-тег: `v0.1.0-aplpha` (опечатка в имени тега).

### Added

- Первая альфа-версия генератора комбинационных схем: JSON/API, алгоритмы RandLevel и др.
- CMake-сборка, расчет надежности, адаптация под GCC 9.4.

### Changed

- Рефакторинг CMake и тестовой генерации.

---

## Как обновлять

При релизе `vX.Y.Z`:

1. Перенесите пункты из **Unreleased** в `## [X.Y.Z] - YYYY-MM-DD`.
2. Создайте тег: `git tag vX.Y.Z`.
3. Подсказка версии: `bash scripts/release/suggest-next-version.sh`.

Обновляйте **оба** файла: `docs/ru/CHANGELOG.md` и `docs/en/CHANGELOG.md`.
