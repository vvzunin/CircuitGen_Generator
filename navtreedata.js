/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "CircuitGen_Generator", "index.html", [
    [ "Генератор комбинационных схем", "index.html", [
      [ "Установка необходимых пакетов", "index.html#autotoc_md1", [
        [ "Установка пакетов с помощью apt", "index.html#autotoc_md2", null ],
        [ "Установка cmake 3.28.1", "index.html#autotoc_md3", null ]
      ] ],
      [ "Режим разработчика", "index.html#autotoc_md4", null ],
      [ "Добавление нового генератора", "index.html#autotoc_md5", null ],
      [ "Сборка программы", "index.html#autotoc_md6", null ],
      [ "Запуск генерации комбинационных схем из командной строки", "index.html#autotoc_md7", null ],
      [ "JSON файлы", "index.html#autotoc_md8", null ],
      [ "Описание префикса папок генерации", "index.html#autotoc_md9", null ],
      [ "Лицензия", "index.html#autotoc_md10", null ]
    ] ],
    [ "Hacking", "md_HACKING.html", [
      [ "Режим разработчика", "md_HACKING.html#autotoc_md12", [
        [ "Правила именования переменных", "md_HACKING.html#autotoc_md13", null ],
        [ "Пресеты", "md_HACKING.html#autotoc_md14", null ],
        [ "Настройка, сборка и тестирование", "md_HACKING.html#autotoc_md15", null ],
        [ "Цели режима разработчика", "md_HACKING.html#autotoc_md16", [
          [ "<tt>coverage</tt>", "md_HACKING.html#autotoc_md17", null ],
          [ "<tt>docs</tt>", "md_HACKING.html#autotoc_md18", null ],
          [ "<tt>format-check</tt> и <tt>format-fix</tt>", "md_HACKING.html#autotoc_md19", null ],
          [ "<tt>run-exe</tt>", "md_HACKING.html#autotoc_md20", null ],
          [ "<tt>spell-check</tt> и <tt>spell-fix</tt>", "md_HACKING.html#autotoc_md21", null ]
        ] ],
        [ "Правила документирования кода", "md_HACKING.html#autotoc_md22", null ]
      ] ]
    ] ],
    [ "Вклад", "md_CONTRIBUTING.html", [
      [ "Нормы поведения", "md_CONTRIBUTING.html#autotoc_md24", null ],
      [ "Начальные шаги", "md_CONTRIBUTING.html#autotoc_md25", null ]
    ] ],
    [ "Сборка с помощью CMake", "md_BUILDING.html", [
      [ "Сборка", "md_BUILDING.html#autotoc_md27", [
        [ "Сборка с MSVC", "md_BUILDING.html#autotoc_md28", null ],
        [ "Сборка на Apple Silicon", "md_BUILDING.html#autotoc_md29", null ]
      ] ],
      [ "Установка", "md_BUILDING.html#autotoc_md30", [
        [ "Пакет CMake", "md_BUILDING.html#autotoc_md31", null ],
        [ "Дальнейшее использование", "md_BUILDING.html#autotoc_md32", [
          [ "runGenerationFromJson", "md_BUILDING.html#autotoc_md33", null ],
          [ "runGenerationFromJsonForGraph", "md_BUILDING.html#autotoc_md34", null ],
          [ "runGenerationFromJsonForPath", "md_BUILDING.html#autotoc_md35", null ]
        ] ],
        [ "Note to packagers", "md_BUILDING.html#autotoc_md36", null ]
      ] ]
    ] ],
    [ "Нормы поведения", "md_CODE_OF_CONDUCT.html", null ],
    [ "Стиль кодирования", "md_docs_CodeStyle.html", null ],
    [ "Описание префикса папок генерации", "md_GeneratorsPrefixes.html", null ],
    [ "JSON файлы", "md_json.html", null ],
    [ "Добавление нового генератора", "md_NewGenerator.html", [
      [ "1.1 <a href=\"src/settings/Settings.hpp\">Settings.hpp</a>", "md_NewGenerator.html#autotoc_md42", null ],
      [ "1.2 <a href=\"src/settings/Settings.hpp\">Settings.hpp</a>", "md_NewGenerator.html#autotoc_md43", null ],
      [ "2. <a href=\"src/generators/GenerationParameters.hpp\">GeneratorParameters.hpp</a>", "md_NewGenerator.html#autotoc_md44", null ],
      [ "3. <a href=\"src/generators/simple/SimpleGenerators.hpp\">SimpleGenerators.hpp</a> и <a href=\"src/generators/simple/SimpleGenerators.cpp\">SimpleGenerators.cpp</a>", "md_NewGenerator.html#autotoc_md45", null ],
      [ "4. <a href=\"src/database/DataBaseGenerator.hpp\">DataBaseGenerator.hpp</a> и <a href=\"src/database/DataBaseGenerator.cpp\">DataBaseGenerator.cpp</a>", "md_NewGenerator.html#autotoc_md46", null ],
      [ "5. <a href=\"src/CircuitGenGenerator.cpp\">CircuitGenGenerator.cpp</a>", "md_NewGenerator.html#autotoc_md47", null ]
    ] ],
    [ "Todo List", "todo.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", "namespacemembers_dup" ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", "functions_type" ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Related Functions", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", null ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"AuxiliaryMethodsTests_8cpp.html",
"Recombinations_8hpp.html",
"classGenerationParameters.html#a80ba5d709b75e68c17694f4be9c3c7b6",
"classRandomGeneratorWithSeed.html#a8032273cf9a79429192fba75159f0fde",
"classbasic__json.html#a5eff2f2def587632ebb64a2a1d921f39",
"classdetail_1_1binary__writer.html#ae6ab36b61e8ad346e75d9f9abc983d4c",
"classdetail_1_1lexer.html#a0a7d915c2d152fcf654550191d95130d",
"classel_1_1LogDispatchData.html#aa7f834fbd4c8440d25ba1958ccf51ea7",
"classel_1_1base_1_1SubsecondPrecision.html#a7b6681bcf8457b97da6d2ad5da4b45c3",
"dir_d28a4824dc47e487b107a5db32ef43c4.html",
"easylogging_09_09_8h.html#a9e8b154363eb8282279f660d0bbaaea1",
"globals_f.html",
"json_8hpp.html#a82dd889f447e7a1383b8757be27f66e9",
"json__fwd_8hpp.html#ae6eede511f01c9f33342044d36a388fa",
"namespacedetail.html#af0210e44153a964b7c8fa438b10123d4",
"structdetail_1_1internal__iterator.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';