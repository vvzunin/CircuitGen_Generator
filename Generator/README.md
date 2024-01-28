# Генератор комбинационных схем

<font size="5">**Оглавление:**</font>
<a name="content_rus"></a> 
- [Правила именования переменных](#rules_rus)
- [Добавление нового генератора](#generator_add_rus)
- [Сборка программы](#generator_build_rus)
- [Запуск генерации комбинационных схем из командной строки](#generator_run_one_json_rus)
- [JSON файлы](#JSON_files)

Сборка и запуск производятся из операционной системы Linux.

Программа запускалась на Ubuntu 22.04 с использованием WSL (Windows Subsystem for Linux).
Руководство разработчика доступно по [ссылке](https://drive.google.com/file/d/1eKWMpF0Ig5r5ZI81dJjRoibctzezNE-D/view?usp=sharing).

## Правила именования переменных
<a name="rules_rus"></a> 

Правила именования переменных:
- d_anything означает поле класса;
- i_anything принимаемый аргумент в функцию.

[&#8593; Contents](#content_rus)

## Добавление нового генератора
<a name="generator_add_rus"></a> 

Для добавления новых генераторов необходимо внести корректировки в следующие файлы:
## 1. [DataBaseGeneratorParameters.h](source/DataBase/DataBaseGeneratorParameters.h)
В файле необходимо отредактировать перечисление типа **GenerationTypes**, добавив в него название генератора. В качестве примера назавем его **NewGeneratorName**.
## 2. [GeneratorParametrs.h](source/generators/GenerationParameters.h)
В файле необходимо создать новый класс, в который нужно будет добавить дополнительные параметры для использования нового генератора. Название класса должно соответствовать требованию: **Generator** + <имя генератор> + **Parameters**. Используя генератор из примера, класс должен назвываться так: **GeneratorNewGeneratorNameParameters**.
> [!IMPORTANT]
> Не нужно добавлять параметры, для количества входов и выходов схемы. Вся информация о них находится в классе **GenerationParameters** в этом же файле.

Далее необходимо в классе **GenerationParameters** создать в разделе *private* переменную ранее созданного класса. Название переменной соответствует следующему требованию: **d_generator** + <имя генератор> + **Parameters**. Для примера переменная будет иметь следующее название: **d_generatorNewGeneratorNameParametrs**.
Для данной переменной необходимо создать геттер и сеттер. Геттер возвращает саму переменную, сеттер — получает на вход переменные для данного класса и записывает в переменную с параметрами.
## 3. [SimpleGenerators.h](source/generators/SimpleGenerators.h) и [SimpleGenerators.cpp](source/generators/SimpleGenerators.cpp)
В данных файлах необходимо реализовать сам генератор (метод для генерации схемы). В **SimpleGenerators.h** необходимо добавить описание метода генерации:
```
OrientedGraph generatorNewGeneratorName(...);
```
В качестве результата метод должен возвращать сгенерированную схему в формате **OrientedGraph**. В качестве входных данных метод должен принимать все необходмые для его использования переменные.
> [!IMPORTANT]
> Имена входных переменных должны начинаться с префикса **i_**.
В **SimpleGenerators.cpp** необходимо реализовать сам генератор:
```
OrientedGraph SimpleGenerators::generatorNewGeneratorName(...) {
   ...
}
```
## 4. [DataBaseGenerator.h](source/DataBase/DataBaseGenerator.h) и [DataBaseGenerator.cpp](source/DataBase/DataBaseGenerator.cpp)
В классе **DataBaseGenerator** необходимо реализовать метод, который будет на вход получать константную ссылку на параметры генерации *i_param*,  которая содержит все необходимые параметры генерации. В данном методе необходимо создать объект класса **SimpleGenerator** и запустить в нем ранее созданный метод, в который нужно передать все необходимые параметры из *i_param* в том же порядке, в котором они были описаны в реализации метода. Результат необходимо записать в переменную типа **OrientedGraph**. После этого необходимо создать переменную типа **Circuit** и в качестве параметра конструктора передать полученный граф. После этого необходимо задать путь генерации (setPath) в качестве которого выступает *d_mainPath*. Также нужно задать название схемы (setCircuitName) присутствующее в параметрах генерации (i_param.getName()). После этого необходимо запустить генерацию схемы в формате Verilog и обсчет параметров (generate), передав набор параметров: i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles().

Используя привенные ранее примеры названий методов, поучиться следующий код дя реализации метода:
```
void DataBaseGenerator::generateNewGeneratorName(GenerationParameters &i_param) {
  SimpleGenerators sg;
  ...
  OrientedGraph graph = sg.generatorNewGeneratorName(...);
  Circuit c (graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
}
```
И код для описания метода в header:
```
void generateNewGeneratorName(const GenerationParameters& i_param);
```
Далее в файле [DataBaseGenerator.cpp](source/DataBase/DataBaseGenerator.cpp) необходимо в функции  **getGenerateMethod** реализовать обработку нового имени генератора и возвраать ссылку на созданную ранее функцию по запуску генератора. Используя название генератора из примера, должна получиться следующая вставка:
```
if (i_methodName == "NewGeneratorName")
   return std::bind(&DataBaseGenerator::generateNewGeneratorName, this, std::placeholders::_1);
```
## 5. [Settings.h](source/Settings.cpp)
В данном файле необходимо внести изменения в метод **getGenerationMethodPrefix**. Необходимо добавить новое имя для генерируемых в результате файлов .v и .json. В качестве начала имени файла должно использоваться **CCG**. Далее седует аббривиатура названия метода генерации.
Используя ранее выданный пример, должно получиться следующее:
```
if (i_s == "NewGeneratorName")
  return "CCGNGN";
```
**CCG** — **Combinational Circuit Generator**, вместо **NGN** можно указать более подходящее на взгляд автора обозначения для созданного метода генерации.
## 6. [main.cpp](source/main.cpp)
Последним шагом является редактирование файла **main.cpp**. В функцию **runGeneratorForJson** после инициализации *GenerationTypes gt* необходимо добавить условие на выбор метода генерации. Используя ранее заданное название генератора вв качестве примера, получим следующий участов кода:
```
if (data["type_of_generation"] == "NewGeneratorName")
	gt = GenerationTypes::NewGeneratorName;
```
Также, если требуется получить дополнительные параметры, их можно получить из переменной data, содержащей данные из json-файла с параметрами для генерации, и передать их в класс **GenerationParameters** (имя переменной - **gp**) с помощью созданного ранее сеттера:
```
gp.setNewGeneratorNameParameters(...);
```
На этом добавление генератора в программу закончено. Осталось только добавить в файл json названия параметров.

[&#8593; Contents](#content_rus)

## Сборка программы
<a name="generator_build_rus"></a> 
Для сборки программы необходимо выполнить следующую команду из начальной директории:
```
./buildGenerator.sh
```

## Сборка библиотеки (shared)
<a name="generator_build_rus"></a> 
Для сборки библиотеки (shared) необходимо выполнить следующую команду из начальной директории:
```
./buildGeneratorLibrary.sh
```

[&#8593; Contents](#content_rus)

## Запуск генерации комбинационных схем из командной строки
<a name="generator_run_one_json_rus"></a>
Для проведения генерации из командной строки необходимо подготовить JSON файл с описанием параметров генерации, создать папку `dataset` в начальной директории, а после выполнить следующую команду:
```
Generator/source/build/circuitgen --json_path <path_to_json>
```

[&#8593; Contents](#content_rus)

## JSON файлы
<a name="JSON_files"></a>
Для генерации комбинационных схем с использованием командной строки необходимо создать JSON файл.

Набор использованных методов описан в следующих статьях:
1) V. V. Zunin, A. Y. Romanov, Solovyev R. Developing Methods for Combinational Circuit Generation, in: 2022 International Russian Automation Conference (RusAutoCon). IEEE, 2022. [doi](https://doi.org/10.1109/RusAutoCon54946.2022.9896390)

JSON файл может содержать несколько наборов генерации:
```
[
    {
        набор генерации 1
    }
    {
        набор генерации 2
    }
]
```
Для каждого набора генерации необходимо задать набор параметров:
1) Опциональные параметры:
   1) seed - int; сид для генератора случайных чисел, -1 или отсутствие поля для псевдослучайного сида;
   2) multithread - bool; флаг, отвечающий за запуск генерации в многопоточном режиме. Отметим, что при использовании данного флага
   является бессмысленным использования seed из-за гонки потоков. По умолчанию - false, вычисления производятся последовательно.
   3) calculate_stats_abc - bool;  флаг, отвечающий за проведение обсчета схема с использованием abc. По умолчанию - false, обсчет 
   не производится
   4) make_optimized_files - bool; флаг, отвечающий за генерацию файлов verilog и aig, которые содержат схемы с некоторыми 
   оптимизациями, в частности resyn2 и balance. Файлы создаются в той же директории, что и сгенерированный verilog файл. 
   По умолчанию - false, генерация не производится. 
   5) library_name -  string; имя библиотеки, с использованием который abc производит обсчет схемы. Является обязательным при 
   использовании флагов calculate_stats_abc и/или make_optimized_files.
   6) make_firrtl - bool; флаг, отвечающий за генерацию firrtl файлов на основе verilog. По умолчанию - false, генерация не производится. 
   7) create_id_directories - bool; флаг, отвечающий за создание директорий dataset_id и id самой генерации. По умолчанию - true.
   8) gates_inputs_info - map (словарь); содержит количество возможных входов для логических элементов. ОБЯЗАТЕЛЬНЫМ является 
   указание всех логических элементов, т.е. and, nand, or, nor, xor, xnor.
   Указывается допустимое количество входов в виде массива int. Пример:
   ```
   "gates_inputs_info": {
      "and": [2],
      "nand": [2],
      "or": [2],
      "nor": [2, 4, 8],
      "xor": [2, 10],
      "xnor": [2, 3]
   }
   ```
   В данном примере у всех элементов может быть два входа, кроме того, у nor может быть 4 или 8 входов, у nor - 10, у nor - 3.
   По умолчанию имеет вид 
   ```
   "gates_inputs_info": {
      "and": [2],
      "nand": [2],
      "or": [2],
      "nor": [2],
      "xor": [2],
      "xnor": [2]
   }
   ```
2) Определение пути генерации:
   1) dataset_id - int; обозначение датасета схем;
   2) id - int; обозначение подкатегории датасета;
3) Общие параметры генерации:
   1) min_in - int; минимальное количество входов;
   2) max_in - int; максимальное количество входов;
   3) min_out - int; минимальное количество выходов;
   4) max_out - int; максимальное количество выходов;
   5) repeat_n - int; количества повторений для каждого набора (num_in-num_out);
4) Выбор типа генерации:
   1) Выбор происходит путем указания в "type_of_generation" типа генерации:
      1) From Random Truth Table;
      2) Rand Level;
      3) Num Operation;
      4) Genetic;
5) В зависимости от типа генерации необходимо описать требуемые параметры:
   1) From Random Truth Table:
      1) CNFF - bool; необходимо ли создать схему с использованием СДНФ;
      2) CNFT - bool; необходимо ли создать схему с использованием СКНФ;
   2) Rand Level:
      1) max_level - int; максимальное количество уровней в схеме;
      2) max_elem - int; максимальное количество элементов на каждом уровне;
   3) Num Operation:
      1) leave_empty_out - bool; оставлять ли пустые выходы;
      2) num_<type> - int; количество элементов каждого типа из возможных: and, nand, or, nor, not, buf, xor, xnor;
   4) Genetic:
      1) chromosome_type - тип хромосомы из возможных: Truth Table;
      2) playback_type - тип рекомбинации из возможных: CrossingEachExitInTurnMany, CrossingUniform, CrossingTriadic, CrossingReducedReplacement, CrossingShuffling;
         1) selection_type_parent - тип отбора родителей: Panmixia, Inbringing, Outbrinding, Tournament, Roulette;
         2) tourSize - int; размер турнира для Tournament;
         3) ref_points - int; для CrossingEachExitInTurnMany
      3) mut_type - тип мутации хромосом из возможных: Binary, Density, AccessionDel, InsertDel, Exchange, Delete;
         1) mut_chance - float; шанс мутации;
         2) swap_type - int (0, 1 или 2);
         3) ratio_in_table - float; распределение 0 и 1 в таблице истинности;
      4) selection_type - тип отбора после мутации: Base;
      5) population_size - int; размер начальной популяции;
      6) cycles - int; максимальное количество циклов генерации;
      7) out_ratio - float; значение критерия окончания работы генетического алгоритма;
      8) mask_prob - float; RecombinationCrossingTriadic и CrossingUniform;
      9) rec_num - int; количество рекомбинаций;
      10) surv_num - int; количество выживших.

В [примере](docs/sampleAll.json) JSON файла указаны все возможные параметры генерации (кроме сида), что позволяет использовать его для всех параметров генерации с минимальными изменениями.
В дополнении в той же папке имются индивидуальные JSON файлы под каждый тип генерации:
1. [From Random Truth Table](docs/sampleTruthTable.json)
2. [Rand Level](docs/sampleRandLevel.json)
3. [Num Operation](docs/sampleNumOperation.json)
4. [Genetic](docs/sampleGenetic.json)

[&#8593; Contents](#content_rus)
