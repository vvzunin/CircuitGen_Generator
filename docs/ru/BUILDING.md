# Сборка с помощью CMake

## Сборка

Для повседневной работы рекомендуется использовать пресеты из `CMakePresets.json` и `CMakeUserPresets.json`.
`CMakeUserPresets.json` является локальным файлом (добавлен в `.gitignore`), поэтому после клонирования создайте его из шаблона:

```sh
cp CMakeUserPresets.json.example CMakeUserPresets.json
```

В проекте по умолчанию используется генератор `Ninja`.

### Пресеты CMake (справка)

В репозитории используются [пресеты CMake](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html): схема **version 6**, `cmakeMinimumRequired` **3.26** (см. `CMakePresets.json` в корне).

| Файл | Назначение |
|------|------------|
| `CMakePresets.json` | Общие пресеты в git: **release**, **release-ci**, **release-examples**, CI-профили (**ci-ubuntu**, **ci-coverage**, **ci-sanitize**, **ci-static-analysis**, …), **ci-examples-dev**, а также скрытые базовые пресеты (**dev-mode**, наборы флагов компилятора, Ninja/C++17). |
| `CMakeUserPresets.json` | **Только локально** (в `.gitignore`). После клона: `cp CMakeUserPresets.json.example CMakeUserPresets.json`. Задает **dev**, **coverage**, **dev-msvc**, … и подключает `CMakePresets.json` через `include`. |

Типичная цепочка **конфигурация → сборка → тесты** (Debug):

```sh
cmake --preset=dev
cmake --build --preset=dev -j"$(nproc)"
ctest --preset=dev
```

**Release с тестами** только из закоммиченных пресетов (как в CI, без `CMakeUserPresets.json`):

```sh
cmake --preset=release-ci
cmake --build --preset=release-ci -j"$(nproc)"
ctest --preset=release-ci
```

Список доступных пресетов: `cmake --list-presets`.

**Сводка по трем репозиториям:** переключатели режима разработчика и примеров отличаются только именами переменных кэша CMake (их выставляет скрытый набор **dev-mode**, от которого наследуются `dev` и многие CI-пресеты):

| Репозиторий | Режим разработчика | Примеры |
|-------------|-------------------|---------|
| Generator | `CircuitGenGenerator_DEVELOPER_MODE` | `CircuitGenGenerator_BUILD_EXAMPLES` |
| Graph | `CircuitGenGraph_DEVELOPER_MODE` | `CircuitGenGraph_BUILD_EXAMPLES` |
| Parameters | `OptimizationsVerilogLib_DEVELOPER_MODE` | `optimizationsveriloglib_BUILD_EXAMPLES` |

### CMake: новые исходники и `CMakeLists.txt`

Код собирается в **библиотеки** рядом с файлами; родительские каталоги подключают дочерние через `add_subdirectory`.

1. **Каталог** — размещайте файлы под `src/` (и публичные заголовки под `include/…`, если API экспортируется).
2. **Регистрация** — в родительском `CMakeLists.txt` добавьте `add_subdirectory(<подкаталог>)`, если создали новую папку.
3. **Листовой `CMakeLists.txt`** — типичный каркас внутренней статической библиотеки:

   ```cmake
   add_library(myLeaf STATIC MyLeaf.cpp)
   target_include_directories(myLeaf PUBLIC
     $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
   )
   target_link_libraries(myLeaf PUBLIC …)  # нужные уже существующие цели
   add_folders(MyLeaf)  # группировка в IDE (cmake/folders.cmake)
   ```

4. **Связь наверх** — исполняемый файл или «большая» библиотека, использующая ваш код, должны указать `myLeaf` в `target_link_libraries`.
5. **Переконфигурация** — после любого изменения `CMakeLists.txt` снова запустите CMake (`cmake --preset=dev` или эквивалент).

**Особенности по репозиториям**

- **Generator:** много мелких статических библиотек в `src/generators/simple/<имя>/CMakeLists.txt`; образец — `src/generators/simple/simple/CMakeLists.txt`. Родитель `src/generators/simple/CMakeLists.txt` вызывает цепочку `add_subdirectory`.
- **Graph:** основная цель `CircuitGenGraph` задается в `src/CMakeLists.txt` списками `SOURCES`, `LIBS` и заголовками в `include/CircuitGenGraph/` (`PUBLIC_HEADER` и правила установки). Новые `.cpp` и заголовки добавляйте туда при расширении библиотеки.
- **Parameters:** основная библиотека и CLI OpenLane в `src/CMakeLists.txt` (`SOURCES` для `CircuitGenParameters`, цель **`CircuitGenParameters_exe`** с именем исполняемого файла **`CircuitGenParameters`** — как у `CircuitGenGenerator_exe` / `CircuitGenGenerator`; точка входа `CircuitGenToOpenLane.cpp`; алиасы `OptimizationsVerilogLib::…`). Подкаталог `examples/` включается при `-D optimizationsveriloglib_BUILD_EXAMPLES=ON` на верхнем уровне; новые модули — через расширение `SOURCES` или отдельный `add_library` по аналогии с соседними целями.

Базовые сценарии:

```sh
# Простая локальная Debug-сборка
bash scripts/dev/build-debug.sh

# Debug-сборка с тестами
cmake --preset=dev
cmake --build --preset=dev
ctest --preset=dev

# Локальное покрытие
bash scripts/dev/coverage.sh

# Релизная сборка (без тестов)
bash scripts/release/build.sh

# Релизная сборка для CI (с тестами)
bash scripts/release/test.sh

# Сборка с примерами (Debug через пресет dev, Release — release-examples)
bash scripts/dev/build-examples.sh
bash scripts/release/build-examples.sh

# Установка release-артефактов
bash scripts/release/install.sh
```

### Примеры (examples)

Каталог `examples/` подключается к сборке только при **`CircuitGenGenerator_BUILD_EXAMPLES=ON`**. В пресете **dev** (см. `CMakeUserPresets.json.example`) и в **`ci-examples-dev`** из `CMakePresets.json` это уже включено через **dev-mode**. Для **Release** примеры по умолчанию выключены; используйте пресет **`release-examples`** или передайте `-D CircuitGenGenerator_BUILD_EXAMPLES=ON` при конфигурации.

Цель **`run-examples`** собирает все исполняемые примеры и последовательно их запускает (см. `examples/CMakeLists.txt`).

**Локально — как dev (Debug, пресет `dev`):**

```sh
cp CMakeUserPresets.json.example CMakeUserPresets.json   # один раз после клонирования
bash scripts/dev/build-examples.sh
```

Эквивалентно: `bash scripts/dev/build-debug.sh`, затем `cmake --build build/dev --target run-examples`.

**Локально — как Release с примерами:**

```sh
bash scripts/release/build-examples.sh
```

Эквивалентно вручную:

```sh
cmake --preset=release-examples
cmake --build --preset=release-examples -j "$(nproc)"
cmake --build --preset=release-examples --target run-examples -j "$(nproc)"
```

**Без скриптов (только пресеты из `CMakePresets.json`):**

```sh
# Debug + examples (аналог dev, удобно в CI и без CMakeUserPresets)
cmake --preset=ci-examples-dev
cmake --build --preset=ci-examples-dev -j "$(nproc)"
cmake --build --preset=ci-examples-dev --target run-examples -j "$(nproc)"

# Release + examples
cmake --preset=release-examples
cmake --build --preset=release-examples -j "$(nproc)"
cmake --build --preset=release-examples --target run-examples -j "$(nproc)"
```

JSON-файлы в `examples/json/` — входные данные для `CircuitGenGenerator::runGenerationFromJson`. Среди C++-примеров: **`empty_example`** (дымовой тест), **`example_print_version`**, запуск по JSON — **`example_run_comparison_json`**, **`example_run_truth_table_json`**, **`example_run_parity_json`** (общий исходник `example_run_preset_json.cpp`, путь к JSON задается на этапе конфигурации CMake через `add_json_example`), а также **`example_run_json_for_graph`** (`runGenerationFromJsonForGraph`, `add_for_graph_example`). См. `examples/CMakeLists.txt`.

### Сборка с MSVC

Обратите внимание, что MSVC по умолчанию не включает часть строгих диагностик. В проекте предусмотрен пресет `dev-msvc` в `CMakeUserPresets.json`, который наследует `flags-msvc` из [CMakePresets.json](../../CMakePresets.json):

```sh
cmake --preset=dev-msvc
cmake --build build/dev-msvc
ctest --test-dir build/dev-msvc --output-on-failure --no-tests=error
```

### Сборка на Apple Silicon

CMake правильно поддерживает сборку на Apple Silicon, начиная с версии 3.20.1. Убедитесь, что у вас установлена [последняя версия][1].

## Установка

Этот проект не требует каких-либо специальных флагов командной строки для установки, чтобы все было просто. Предварительным условием является то, что проект уже должен быть собран с использованием вышеуказанных команд.

Для запуска приведенных ниже команд требуется как минимум CMake 3.15, поскольку это версия, в которой был добавлен [Установить проект][2].

Вот команда для установки артефактов режима выпуска:

```sh
cmake --install build/release
```

## Локальная сборка dev-контейнера

Для локальной сборки окружения разработки (по аналогии с CI) используйте:

```sh
bash scripts/docker/build-images.sh
```

Скрипт соберет локальный базовый CI-образ, затем dev- и release-образы на его основе через
`dockerfile/Dockerfile.dev` и `dockerfile/Dockerfile.release`.
При необходимости можно собирать образы по отдельности:

```sh
bash scripts/docker/build-ci-image.sh
bash scripts/docker/build-dev-only-image.sh
bash scripts/docker/build-release-only-image.sh
```

Подробности по доступным скриптам приведены в [SCRIPTS.md](SCRIPTS.md).

## Документация (Doxygen + m.css + PDF)

Сборка документации запускается через:

```sh
bash scripts/ci/docs.sh
```

Что генерируется (по умолчанию **английский и русский** в отдельных деревьях):
- `build/docs/html/en`, `build/docs/html/ru` — HTML через `m.css`;
- `build/docs/xml/en`, `build/docs/xml/ru` — XML-выгрузка Doxygen;
- `build/docs/latex/en`, `build/docs/latex/ru` — LaTeX-исходники;
- `build/docs/pdf/en`, `build/docs/pdf/ru` — итоговый PDF (`CircuitGenGenerator.pdf` в каждой папке; Doxygen по-прежнему собирает `latex/refman.pdf`, затем CMake копирует).

По умолчанию `scripts/ci/docs.sh` и `scripts/dev/build-docs.sh` используют `DOXYGEN_LANG_VARIANTS="en=english;ru=russian"` (см. `scripts/docs/build-doxygen-lang-variants.sh`). Чтобы собрать **только один** язык:

```sh
DOXYGEN_LANG_VARIANTS="en=english" bash scripts/ci/docs.sh
```

Для каждого варианта Doxygen **`OUTPUT_LANGUAGE`** (подписи в HTML, LaTeX, поиске) соответствует варианту: `ru=russian` — русский интерфейс, `en=english` — английский. Это задается в `cmake/docs-ci.cmake` вместе с подписями навбара m.css в `conf.py`.

**Локально** мультиязычный вывод совпадает с CI, но лежит в `build/dev/docs/.../{en,ru}/`: запустите **`bash scripts/dev/build-docs.sh`** (конфигурирует preset `dev` для `compile_commands.json`, затем тот же генератор, что и в CI).

Опционально: при **`BUILD_MCSS_DOCS=ON`** цель CMake **`docs`** (`cmake/docs.cmake`) собирает **один** язык в `build/dev/docs/html` (без подпапок `en`/`ru`); язык задается кэшем **`DOXYGEN_DOCUMENTATION_LANGUAGE`** (`english` или `russian`). После смены выполните повторную конфигурацию `cmake`.

Для сборки PDF нужен LaTeX toolchain (`pdflatex`, `makeindex`), он устанавливается
скриптами `scripts/setup/install-deps-*.sh` и в CI-образе `dockerfile/Dockerfile.ci`.
Поддержка Graphviz (`dot`) в Doxygen включается автоматически через CMake
(`HAVE_DOT`/`DOT_PATH` выставляются по наличию `dot` в системе).

Двухпроходная сборка по умолчанию (`en=english` и `ru=russian`) выводит в каждой папке текст одного языка. Чтобы в **одном** дереве были активны **обе** секции Doxygen, задайте вариант со списком секций, например:

```sh
DOXYGEN_LANG_VARIANTS="all=english russian" bash scripts/ci/docs.sh
```

Результат: `build/docs/html/all/` (и соответствующие `xml` / `latex` / `pdf`).

Проверки перед push можно запускать в контейнере dev-образа:

```sh
bash scripts/dev/pre-push-docker.sh
```

## CI запуск через скрипты

GitLab CI запускает команды через скрипты в `scripts/ci/`, а не через длинные inline-команды в `.gitlab-ci.yml`.
Это упрощает поддержку и позволяет локально воспроизвести шаги CI:

```sh
bash scripts/ci/lint.sh
bash scripts/ci/static-analysis.sh
bash scripts/ci/sanitize.sh
bash scripts/ci/coverage.sh
bash scripts/ci/tests.sh
bash scripts/ci/examples.sh
bash scripts/ci/docs.sh
```

Для унифицированного локального запуска используйте:

```sh
# В текущей системе
CI_RUNNER=local bash scripts/ci/run-task.sh lint

# В локальном Docker CI-образе
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-task.sh coverage

# Полный прогон CI-этапов
CI_RUNNER=docker CI_IMAGE_TAG=circuitgen/generator/ubuntu-24.04/ci:local bash scripts/ci/run-all.sh
```

## Проверяемые ОС в CI

Список поддерживаемых ОС задается в **`scripts/config/supported-os.sh`**. Помеченные блоки **джобов по одной ОС** в **`.gitlab-ci.yml`** **генерируются** из него скриптом **`scripts/ci/generate-gitlab-os-matrix.sh`** (`--write` после правок списка ОС). В пайплайне джоб **`gitlab-os-matrix-check`** (стадия `validate`) выполняет **`--check`**: если закоммиченный YAML не совпадает с генератором, пайплайн падает.

Отдельный этап CI (`os-system-validation-*`) использует разные правила для веток:
- для `main` запускается matrix по всем поддерживаемым ОС;
- для любой другой ветки запускается только `ubuntu-24.04` (slug должен совпадать с `DEFAULT_TARGET_OS_SLUG` в `supported-os.sh`, если вы меняете дефолт).

Для каждой выбранной системы CI:
- собирает отдельный Docker-образ `.../os-<target>:<tag>`;
- публикует этот образ в registry;
- запускает внутри него полный прогон `scripts/ci/run-all.sh`
  (`lint -> static-analysis -> sanitize -> coverage -> tests -> examples -> docs`), тем самым проверяя не только setup,
  но и все шаги компиляции/тестирования/документации.

Актуальный перечень slug смотрите в `scripts/config/supported-os.sh` (или в сгенерированных маркерах матрицы в `.gitlab-ci.yml`).

Пошаговый чек-лист при добавлении новой ОС (список в `supported-os.sh`, install-скрипт, release-toolchain, регенерация YAML, правки `.gitlab-ci.yml`, проверки): см. раздел **«Практика при добавлении новой ОС»** в [SCRIPTS.md](SCRIPTS.md).

## Docker образы CI/DEV/RELEASE по ОС

На этапе `docker` для каждой поддерживаемой ОС выполняется отдельный джоб `docker-images-<slug>`; он собирает и публикует образы `ci`, `dev` и `release` для этой ОС. Образ `release` собирается из `dockerfile/Dockerfile.release` на легком
базовом образе (только toolchain для исполняемого файла), без dev/документационного набора из CI.
Имена путей вида `.../<slug>/ci:<tag>` перечислены в `scripts/config/supported-os.sh` (slug совпадает с суффиксом `IMAGE_OS_SUFFIX` в CI).

### Пакет CMake

Этот проект экспортирует пакет CMake для использования с CMake командой [`find_package`][3]:

* Package name: `CircuitGenGenerator`
* Target name: `CircuitGenGenerator::CircuitGenGenerator`

Пример подгрузки библиотеки:
```cmake
FetchContent_Declare(
  CircuitGen_Generator
  GIT_REPOSITORY https://github.com/vvzunin/CircuitGen_Generator
  GIT_TAG v1.0.0-alpha
)
FetchContent_MakeAvailable(CircuitGen_Generator)
```

> [!CAUTION]
> В качестве GIT_TAG необходимо выбрать последнюю доступную версию проекта.


Пример добавления библиотеки в проект:
```cmake
target_link_libraries(
    app PRIVATE
    CircuitGenGenerator::CircuitGenGenerator
)
```

### Дальнейшее использование
После подключения библиотеки для использования доступны три различные функции. Для их использования требуется подключить хедер CircuitGenGenerator.hpp

```
#include <CircuitGenGenerator/CircuitGenGenerator.hpp>
```

#### runGenerationFromJson
На вход получает путь до json файла. Не возвращает ничего
#### runGenerationFromJsonForGraph
Аналогично, получает на вход путь до файла json. В отличие от предыдущей функции, возвращает следующую структуру:
`std::vector<std::pair<std::string, std::vector<GraphPtr>>>`. Для `std::pair<std::string, std::vector<GraphPtr>>` существует псевдоним ResultGraph.
Первым значением в паре является путь до папки, где находятся сгенерированные verilog-файлы. Второе значение пары, вектор, содержит ссылки на графы, сгенерированные по данному пути. На каждый объект верхнего уровня в JSON-файле формируется один элемент вектора (используется тот же путь генерации, что и у `runGenerationFromJson`, с возвратом графов в память).
#### runGenerationFromJsonForPath
Аналогично, получает на вход путь до файла json. Возвращает `std::vector<std::pair<std::string, std::vector<std::string>>>`. В отличие от предыдущей функции, вместо графов возвращаются их имена, используемые как имена папок с созданными Verilog-файлами соответствующих графов, а также в качестве имен файлов.

### Note to packagers

Для `CMAKE_INSTALL_INCLUDEDIR` задан путь, отличный от просто `include`, если проект настроен как проект верхнего уровня, чтобы избежать косвенного включения других библиотек при установке с общим префиксом. Просмотрите файл [install-rules.cmake](../../cmake/install-rules.cmake) для получения полного набора правил установки.

**English:** [Building with CMake](../en/BUILDING.md)

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/command/find_package.html
