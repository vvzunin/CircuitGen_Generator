# Генератор комбинационных схем

![License: MIT](https://img.shields.io/github/license/vvzunin/CircuitGen_Generator)
![GitHub forks](https://img.shields.io/github/forks/vvzunin/CircuitGen_Generator)
![GitHub Repo stars](https://img.shields.io/github/stars/vvzunin/CircuitGen_Generator)
![GitHub watchers](https://img.shields.io/github/watchers/vvzunin/CircuitGen_Generator)

![GitHub CI](https://github.com/vvzunin/CircuitGen_Generator/actions/workflows/ci.yml/badge.svg)
[![codecov](https://codecov.io/gh/vvzunin/CircuitGen_Generator/graph/badge.svg?token=U88U82QFX8)](https://codecov.io/gh/vvzunin/CircuitGen_Generator)
![GitHub Release](https://img.shields.io/github/v/release/vvzunin/CircuitGen_Generator)
![GitHub Release Date](https://img.shields.io/github/release-date/vvzunin/CircuitGen_Generator)

![GitHub commit activity](https://img.shields.io/github/commit-activity/m/vvzunin/CircuitGen_Generator)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/vvzunin/CircuitGen_Generator/latest)
![GitHub last commit](https://img.shields.io/github/last-commit/vvzunin/CircuitGen_Generator)

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/vvzunin/CircuitGen_Generator)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr/vvzunin/CircuitGen_Generator)

<font size="5">**Оглавление:**</font>
<a name="content_rus"></a> 
- [Правила именования переменных](#hacking)
- [Добавление нового генератора](#generator_add_rus)
- [Сборка программы](#generator_build_rus)
- [Запуск генерации комбинационных схем из командной строки](#generator_run_one_json_rus)
- [JSON файлы](#JSON_files)
- [Лицензия](#license)

Сборка и запуск производятся из операционной системы Linux.

Программа запускалась на Ubuntu 22.04 с использованием WSL (Windows Subsystem for Linux).
Руководство разработчика доступно по [ссылке](https://drive.google.com/file/d/1eKWMpF0Ig5r5ZI81dJjRoibctzezNE-D/view?usp=sharing).

> [!CAUTION]
> Генетический алгоритм временно убран из методов генрации схем для полной переработки.

## Режим разработчика
<a name="hacking"></a> 

Несколько советов, которые помогут Вам создать и протестировать этот проект в качестве разработчика и потенциального участника представлены [здесь](HACKING.md).

[&#8593; Contents](#content_rus)

## Добавление нового генератора
<a name="generator_add_rus"></a> 

Процесс добавления нового генератора описан в отдельном [файле](NewGenerator.md).

[&#8593; Contents](#content_rus)

## Сборка программы
<a name="generator_build_rus"></a> 

Для сборки программы необходимо выполнить следующие команды из начальной директории:
```
chmod +x buildGenerator.sh
./buildGenerator.sh
```

Подробная схема сборка описана [здесь](BUILDING.md).

[&#8593; Contents](#content_rus)

## Запуск генерации комбинационных схем из командной строки
<a name="generator_run_one_json_rus"></a>
Для проведения генерации из командной строки необходимо подготовить JSON файл с описанием параметров генерации, создать папку `dataset` в начальной директории, а после выполнить следующую команду:
```
build/CircuitGenGenerator --json_path <path_to_json>
```

[&#8593; Contents](#content_rus)

## JSON файлы
<a name="JSON_files"></a>
Для генерации комбинационных схем с использованием командной строки необходимо создать JSON файл.

Подробное описание структуры файлов представлено [здесь](json.md).

[&#8593; Contents](#content_rus)

# Лицензия
<a name="license"></a>

Смотрите файл с [лицензией](LICENSE.md).

[&#8593; Contents](#content_rus)