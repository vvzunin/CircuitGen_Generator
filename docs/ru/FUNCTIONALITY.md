# CircuitGen Generator — описание функционала

**Репозиторий:** [CircuitGen_Generator](https://hub.mos.ru/circuitgen/CircuitGen_Generator)  
**CMake-проект:** `CircuitGenGenerator`  
**Роль в экосистеме CircuitGen:** генерация наборов комбинационных и смешанных цифровых схем по JSON-конфигурации с выгрузкой в Verilog, GraphML и сопутствующие артефакты.

## Назначение

Generator — прикладной слой над библиотекой **Graph**. Он реализует множество **алгоритмов генерации** схем (от случайных уровней и таблиц истинности до генетических методов и специализированных блоков ALU, кодеров, автоматов) и оркестрирует полный цикл: построение графа → сохранение файлов → опциональная постобработка. Точка входа для пакетной генерации — исполняемый файл **`CircuitGenGenerator`** и JSON-описания заданий.

## Основные возможности

### Запуск по JSON

- Чтение параметров генерации из JSON (`runGenerationFromJson`, `runGenerationFromJsonForGraph`, `runGenerationFromJsonForPath`).
- Пакетный запуск нескольких схем с уникальными префиксами каталогов (см. [GeneratorsPrefixes.md](GeneratorsPrefixes.md), [json.md](json.md)).
- CLI: `CircuitGenGenerator --json_path <path_to_json>`.

### Алгоритмы генерации (`GenerationTypes`)

| Тип | Краткое описание |
|-----|----------------|
| `RandLevel` / `RandLevelExperimental` | Случайные комбинационные схемы по уровням |
| `FromRandomTruthTable` | Генерация по случайной таблице истинности |
| `Genetic` | Эволюционный поиск схем (хромосомы, мутации, скрещивания, отбор) |
| `NumOperation` | Числовые операции на битовых векторах |
| `Summator`, `Subtractor`, `Multiplier` | Арифметические блоки |
| `Comparison`, `Parity` | Сравнение, четность |
| `Encoder`, `Decoder`, `Multiplexer`, `Demultiplexer` | Кодеры и мультиплексирование |
| `ALU` | Арифметико-логическое устройство |
| `MealyMoore` | Конечные автоматы (Mealy/Moore) |
| `Cascade` | Каскадные структуры |
| `DotToGraph` | Построение графа из DOT-описания |

Каждый тип имеет префикс выходных папок вида `CCG…` (Combinational Circuit Generator).

### Архитектура генерации

- **`SimpleGenerator`** и наследники в `src/generators/simple/` — конкретные алгоритмы (arithmetic, alu, coder, plexer, …).
- **`GeneticGenerator`** — генетический пайплайн (родители, рекомбинация, мутации, отбор).
- **`DataBaseGenerator`** — диспетчер: по типу генерации вызывает нужный метод, оборачивает результат в **`Circuit`**.
- **`Circuit`** — связка `GraphPtr` + путь + имя; метод `generate()` пишет Verilog, GraphML и связанные файлы.
- **`GenerationParameters`** — единый контейнер параметров (число входов/выходов, флаги GraphML, ABC, FIRRTL и т.д.).

### Дополнительные режимы

- **`runChiselGeneration`** — генерация через Chisel (отдельный путь в toolchain).
- **`BasisConverter`** — преобразование базисов представления.
- Многопоточность: `ThreadPool`, `UnboundedMPMCQueue` для параллельных заданий.

### Выходные артефакты

- Verilog (`.v`) — основной RTL для симуляции и синтеза.
- GraphML (классический, pseudo-ABCD, open-ABCD) — при соответствующих флагах в параметрах.
- JSON-метаданные и структура каталогов с префиксом генератора.
- Интеграция с последующими шагами: ABC-статистика, FIRRTL, bench (параметры в `GenerationParameters`, часть — в развитии).

## Публичный API

| Компонент | Назначение |
|-----------|------------|
| `CircuitGenGenerator.hpp` | Экспортируемые функции запуска из JSON, версия |
| `export.hpp`, `info.hpp` | Макросы экспорта библиотеки, версия сборки |

Внутренняя логика: `src/generators/`, `src/database/`, `src/circuit/`, `src/settings/`.

## Сборка и артефакты

- CMake, пресеты `dev` / `release-ci`, скрипты `scripts/dev/build-debug.sh`, `scripts/release/build.sh`.
- Docker-образы CI/dev/release (`scripts/docker/`).
- Документация Doxygen, деплой на NAS (как в Graph/Parameters).
- Платформы: Linux (основной CI), также Windows/macOS через CMake (см. [README.md](../../README.md)).

## Зависимости

- **CircuitGen Graph** — модель схемы (`OrientedGraph`, `GraphPtr`).
- JSON-парсинг, файловая система, опционально JVM/SBT для Chisel (`scripts/setup/`).
- Для полного CI: Docker, Harbor, матрица ОС (`scripts/ci/generate-gitlab-os-matrix.sh`).

## Связь с другими репозиториями

| Репозиторий | Связь |
|-------------|--------|
| **Graph** | Все генераторы возвращают `GraphPtr`; экспорт Verilog делегируется графу |
| **Parameters** | Сгенерированный Verilog → Yosys/ABC/OpenLane |
| **CircuitGen** | Главный репозиторий, сценарии end-to-end |

## Расширение системы

Новый генератор: тип в `Settings.hpp`, класс параметров, реализация в `src/generators/simple/<name>/`, регистрация в `DataBaseGenerator` — [NewGenerator.md](NewGenerator.md).

## См. также

- [README.md](../../README.md) — сборка, запуск JSON  
- [json.md](json.md) — формат JSON  
- [GeneratorsPrefixes.md](GeneratorsPrefixes.md) — префиксы каталогов  
- [BUILDING.md](BUILDING.md) — сборка и CI  
- [CHANGELOG.md](CHANGELOG.md) — журнал изменений  
- English version: [FUNCTIONALITY.md](../en/FUNCTIONALITY.md)
