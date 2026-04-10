# Format

Некоторые шаги, которые стоит сделать перед работой с проектом в VsCode

## Проблемы с поддержкой синтаксиса

Для работы с проектом в VSCode понадобятся следующие дополнения:

- **C/C++ Extension Pack**  
- **CMake Language Support**  
- **WSL** (при условии что вы работаете с помощью WSL)

Даже после установки дополнений VSCode может не распознавать фрагменты синтаксиса. Для исправления этой проблемы откройте панель команд через сочетание клавиш Ctrl + Shift + P и введите:

```
C/C++: Edit Configurations (UI)
```

В открывшейся вкладке настроек вам необходимо поставить нужный путь компилятора _Compiler path_ из открывающегося списка (для g++ путь _/usr/bin/g++_ и т.д.), проверить _include path_, который должен соответствовать форме

```
${workspaceFolder}/**
```

а также поставить актуальный стандарт C++.

Все изменения отобразятся в файле **c_cpp_properties.json**, созданным в папке .vscode, которая обязана присутствовать внутри корневой папки проекта. Содержимое файла должно выглядеть примерно так:

<details open>
  <summary>Код</summary>

  ```
  {  
    "configurations": [  
        {  
            "name": "Linux",  
            "includePath": [    
                "${workspaceFolder}/**"    
            ],  
            "defines": [],  
            "cStandard": "c23",   
            "cppStandard": "c++23",    
            "intelliSenseMode": "linux-clang-x64",  
            "compilerPath": "/usr/bin/g++"  
        }  
    ],  
    "version": 4  
  }
  ```

</details>

## Clang-format и settings.json

При работе с Clang-format может возникнуть ситуация, когда за неимением файла конфигурации **.clang-format** или ошибки при его прочтении программа форматирования обратится к находящемуся в папке .vscode файлу **settings.json**, в котором должны быть прописаны требования к формату. Примерный код внутри файла:

<details open>
  <summary>Код</summary>

  ```
  {
    "files.associations": {
        "ostream": "cpp",
        "any": "cpp",
        "array": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "*.tcc": "cpp",
        "bitset": "cpp",
        "cctype": "cpp",
        "charconv": "cpp",
        "chrono": "cpp",
        "cinttypes": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "codecvt": "cpp",
        "compare": "cpp",
        "complex": "cpp",
        "concepts": "cpp",
        "condition_variable": "cpp",
        "csignal": "cpp",
        "cstdarg": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cstring": "cpp",
        "ctime": "cpp",
        "cwchar": "cpp",
        "cwctype": "cpp",
        "deque": "cpp",
        "forward_list": "cpp",
        "list": "cpp",
        "map": "cpp",
        "set": "cpp",
        "string": "cpp",
        "unordered_map": "cpp",
        "unordered_set": "cpp",
        "vector": "cpp",
        "exception": "cpp",
        "algorithm": "cpp",
        "functional": "cpp",
        "iterator": "cpp",
        "memory": "cpp",
        "memory_resource": "cpp",
        "numeric": "cpp",
        "optional": "cpp",
        "random": "cpp",
        "ratio": "cpp",
        "regex": "cpp",
        "string_view": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "utility": "cpp",
        "format": "cpp",
        "fstream": "cpp",
        "initializer_list": "cpp",
        "iomanip": "cpp",
        "iosfwd": "cpp",
        "iostream": "cpp",
        "istream": "cpp",
        "limits": "cpp",
        "mutex": "cpp",
        "new": "cpp",
        "numbers": "cpp",
        "semaphore": "cpp",
        "shared_mutex": "cpp",
        "span": "cpp",
        "sstream": "cpp",
        "stdexcept": "cpp",
        "stop_token": "cpp",
        "streambuf": "cpp",
        "thread": "cpp",
        "typeinfo": "cpp",
        "valarray": "cpp",
        "variant": "cpp",
        "*.def": "cpp",
        "filesystem": "cpp",
        "future": "cpp",
        "ranges": "cpp",
        "cassert": "cpp",
        "text_encoding": "cpp",
        "source_location": "cpp"
      },
      "cmake.sourceDirectory": "/home/user/CiruitGen/CircuitGen_Graph",
      "C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle: Google, ColumnLimit: 80, BreakBeforeBraces: Attach }",
      "C_Cpp.default.compilerPath": "/usr/bin/g++"
  }
  ```

</details>

**English:** [Format.md](../en/Format.md)