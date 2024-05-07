# Сборка с помощью CMake

## Сборка

Для упрощения сборки этот проект не требует каких-либо специальных флагов командной строки.

Вот шаги для сборки в режиме выпуска с помощью генератора одной конфигурации, такого как Unix Makefiles:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

Вот шаги для сборки в режиме выпуска с помощью генератора нескольких конфигураций, такого как Visual Studio:

```sh
cmake -S . -B build
cmake --build build --config Release
```

### Сборка с MSVC

Обратите внимание, что MSVC по умолчанию не соответствует стандартам, и вам необходимо передать некоторые флаги, чтобы он работал правильно. См. предустановку `flags-msvc` в файле [CMakePresets.json](CMakePresets.json), где указаны флаги и переменная, которую нужно предоставить CMake во время настройки.

### Сборка на Apple Silicon

CMake правильно поддерживает сборку на Apple Silicon, начиная с версии 3.20.1. Убедитесь, что у вас установлена [последняя версия][1].

## Установка

Этот проект не требует каких-либо специальных флагов командной строки для установки, чтобы все было просто. Предварительным условием является то, что проект уже должен быть собран с использованием вышеуказанных команд.

Для запуска приведенных ниже команд требуется как минимум CMake 3.15, поскольку это версия, в которой был добавлен [Установить проект][2].

Вот команда для установки артефактов режима выпуска с помощью генератора одной конфигурации, такого как Unix Makefiles:

```sh
cmake --install build
```

Вот команда для установки артефактов режима выпуска с помощью генератора нескольких конфигураций, такого как Visual Studio:

```sh
cmake --install build --config Release
```

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
Первым значением в паре является путь до папки, где находятся сгенерированные verilog-файлы. Второе значение пары, вектор, содержит ссылки на графы, сгенерированные по данному пути.
#### runGenerationFromJsonForPath
Аналогично, получает на вход путь до файла json. Возвращает `std::vector<std::pair<std::string, std::vector<std::string>>>`. В отличие от предыдущей функции, вместо графов возвращаются их имена, используемые как имена папок с созданными Verilog-файлами соответствующих графов, а также в качестве имен файлов. 

### Note to packagers

Для `CMAKE_INSTALL_INCLUDEDIR` задан путь, отличный от просто `include`, если проект настроен как проект верхнего уровня, чтобы избежать косвенного включения других библиотек при установке с общим префиксом. Просмотрите файл [install-rules.cmake](cmake/install-rules.cmake) для получения полного набора правил установки.

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/command/find_package.html
