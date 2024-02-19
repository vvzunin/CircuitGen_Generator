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
  c.generate(
      i_param.getMakeFirrtl(),
      i_param.getMakeBench(),
      i_param.getCalculateStatsAbc(),
      i_param.getLibraryName(),
      i_param.getMakeOptimizedFiles()
   );
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
<details>
<summary><strong>1. Опциональные параметры:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**seed**|Сид для генератора случайных чисел|int|&#9744;|Псевдослучайное число|"seed": 2|
   |**multithread**|Флаг, отвечающий за запуск генерации в многопоточном режиме.|bool|&#9744;|false|"multithread": true|
   |**calculate_stats_abc**|Флаг, отвечающий за проведение обсчета схема с использованием abc.|bool|&#9744;|false|"calculate_stats_abc": true|
   |**make_optimized_files**|Флаг, отвечающий за генерацию файлов verilog и aig, которые содержат схемы с некоторыми оптимизациями, в частности resyn2 и balance. Файлы создаются в той же директории, что и сгенерированный verilog файл.|bool|&#9744;|false|"make_optimized_files": true|
   |**library_name**|Имя библиотеки, с использованием которой abc производит обсчет схемы. Является обязательным при использовании флагов calculate_stats_abc и/или make_optimized_files.|string|&#9745;|""|"library_name": "sky130"|
   |**make_firrtl**|Флаг, отвечающий за генерацию firrtl файлов на основе Verilog.|bool|&#9744;|false|"make_firrtl": true|
   |**make_bench**|Флаг, отвечающий за генерацию bench файлов на основе Verilog.|bool|&#9744;|false|"make_bench": true|
   |**create_id_directories**|Флаг, отвечающий за создание директорий dataset_id и id самой генерации.|bool|&#9744;|true|"create_id_directories": true|
   |**gates_inputs_info**|Содержит количество возможных входов для логических элементов. ОБЯЗАТЕЛЬНЫМ является указание всех логических элементов, т.е. and, nand, or, nor, xor, xnor. Указывается допустимое количество входов в виде массива int.|map<string, vector\<int>>|&#9745;|"gates_inputs_info": {<br/>&nbsp;&nbsp;"and": [2],<br/>&nbsp;&nbsp;"nand": [2],<br/>&nbsp;&nbsp;"or": [2],<br/>&nbsp;&nbsp;"nor": [2],<br/>&nbsp;&nbsp;"xor": [2],<br/>&nbsp;&nbsp;"xnor": [2]<br/>}|"gates_inputs_info": {<br/>&nbsp;&nbsp;"and": [2],<br/>&nbsp;&nbsp;"nand": [2],<br/>&nbsp;&nbsp;"or": [2, 4, 8],<br/>&nbsp;&nbsp;"nor": [2],<br/>&nbsp;&nbsp;"xor": [2, 10],<br/>&nbsp;&nbsp;"xnor": [2]<br/>}|\
</details>

<details>
<summary><strong>2. Определение пути генерации:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**dataset_id**|Обозначение датасета схем|int|&#9744;|0|"dataset_id": "0"|
   |**id**|Обозначение подкатегории датасета|int|&#9744;|0|"id": 0|
</details>

<details>
<summary><strong>3. Общие параметры генерации:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**min_in**|Минимальное количество входов|int|&#9745;|-|"min_in": 5|
   |**max_in**|Максимальное количество входов|int|&#9745;|-|"max_in": 5|
   |**min_out**|Минимальное количество выходов|int|&#9745;|-|"min_out": 5|
   |**max_out**|Максимальное количество выходов|int|&#9745;|-|"max_out": 5|
   |**repeat_n**|Количество повторений для каждого набора (num_in-num_out)|int|&#9745;|-|"repeat_n": 5|
</details>

<details>
<summary><strong>4. Выбор типа генерации:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**type_of_generation**|Выбор используемого типа генерации|Одно из значений списка:<br/>"From Random Truth Table"<br/>"Rand Level"<br/>"Rand Level Experimental"<br/>"Num Operation"<!--<br/>"Genetic"-->|&#9745;|-|"type_of_generation": "Rand Level"|

В зависимости от типа генерации необходимо описать требуемые параметры:
<details>
<summary><strong>1. From Random Truth Table:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**CNFF**|Необходимо ли создать схему с использованием СДНФ|bool|&#9744;|false|"CNFF": false|
   |**CNFT**|Необходимо ли создать схему с использованием СКНФ|bool|&#9744;|false|"CNFT": false|
</details>

<details>
<summary><strong>2. Rand Level:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**min_level**|Минимальное количество уровней в схеме|int|&#9744;|0|"min_level": 1|
   |**max_level**|Максимальное количество уровней в схеме|int|&#9744;|0|"max_level": 1|
   |**min_elem**|Минимальное количество элементов в схеме|int|&#9744;|0|"min_elem": 1|
   |**max_elem**|Максимальное количество элементов на каждом уровне|int|&#9744;|0|"max_elem": 1|
</details>

<details>
<summary><strong>3. Rand Level Experimental:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**min_level**|Минимальное количество уровней в схеме|int|&#9744;|0|"min_level": 1|
   |**max_level**|Максимальное количество уровней в схеме|int|&#9744;|0|"max_level": 1|
   |**min_elem**|Минимальное количество элементов в схеме|int|&#9744;|0|"min_elem": 1|
   |**max_elem**|Максимальное количество элементов на каждом уровне|int|&#9744;|0|"max_elem": 1|
   |**gates_inputs_info**|Число входов для каждого логического элемента|map|&#9744;|0|"gates_inputs_info": {
      "and": [32, 4],
      "nand": [2, 16, 8],
      "or": [32, 8],
      "nor": [16, 4, 8],
      "xor": [2, 32, 4],
      "xnor": [2, 16, 8]
    }|
</details>

<details>
<summary><strong>4. Num Operation:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**leave_empty_out**|Оставлять ли пустые выходы|bool|&#9745;|-|"leave_empty_out": true|
   |**num_\<type\>**|Количество логических элементов каждого типа из возможных: and, nand, or, nor, not, buf, xor, xnor;|int|&#9745;|-|"num_and": 1|
</details>

<!--
<details>
<summary><strong>4. Genetic:</strong></summary>

   | Название | Описание | Тип | Обязательность | Значение по умолчанию | Пример |
   | :--- | :--- | :---: | :---: | :--- | :--- |
   |**chromosome_type**|Тип хромосомы из поддерживаемых|Одно из значений списка:<br/>"Truth Table"|&#9744;|-|"chromosome_type": "Truth Table"|
   |||||||
   |**playback_type**|Тип рекомбинации из поддерживаемых|Одно из значений списка:<br/>"CrossingEachExitInTurnMany"<br/>"CrossingUniform"<br/>"CrossingTriadic"<br/>"CrossingReducedReplacement"<br/>"CrossingShuffling"|&#9745;|-|"playback_type": "CrossingEachExitInTurnMany"|
   |**ref_points**|Количество точек для CrossingEachExitInTurnMany|int|&#9744;|1|"ref_points": 1|
   |||||||
   |**selection_type_parent**|Тип отбора родителей|Одно из значений списка:<br/>"Panmixia"<br/>"Inbringing"<br/>"Outbrinding"<br/>"Tournament"<br/>"Roulette"|&#9745;|-|"selection_type_parent": "Panmixia"|
   |**tourSize**|Размер турнира для Tournament |int|&#9744;|1|"tour_size": 1|   
   |||||||
   |**mut_type**|Тип мутации хромосом из поддерживаемых |Одно из значений списка:<br/>"Binary"<br/>"Density"<br/>"AccessionDel"<br/>"InsertDel"<br/>"Exchange"<br/>"Delete"|&#9745;|-|"mut_type": "Binary"|
   |**mut_chance**|Шанс мутации |float|&#9744;|0.5|"mut_chance": 1.0|
   |**swap_type**|Тип обмена |int (0, 1 или 2)|&#9744;|0|"swap_type": 0|
   |**ratio_in_table**|Распределение 0 и 1 в таблице истинности|float|&#9744;|1.0|"ratio_in_table": 1.0|
   |**chrom**|Тип хромосомы |Одно из значений списка:<br/>|&#9744;|-|"chrome": "Truth Table"|
   |**chrom**|Тип хромосомы |Одно из значений списка:<br/>|&#9744;|-|"chrome": "Truth Table"|
   |||||||
   |**selection_type**|Тип отбора после мутации|Одно из значений списка:<br/>"Base"|&#9744;|-|"selection_type": "Base"|
   |**population_size**|Размер начальной популяции|int|&#9744;|1|"population_size": 1|
   |**cycles**|Максимальное количество циклов генерации|int|&#9744;|1|"cycles": 1|
   |**out_ratio**|Значение критерия окончания работы генетического алгоритма|float|&#9744;|1.0|"out_ratio": 1.0|
   |**mask_prob**|Вероятность для RecombinationCrossingTriadic и CrossingUniform|float|&#9744;|1.0|"mask_prob": 1.0|
   |**rec_num**|Количество рекомбинаций|int|&#9744;|1|"rec_num": 1|
   |**surv_num**|Количество выживших|int|&#9744;|-|"surv_num": 1|
</details>
-->
</details>


В [примере](docs/sampleAll.json) JSON файла указаны все возможные параметры генерации (кроме сида), что позволяет использовать его для всех параметров генерации с минимальными изменениями.
В дополнении в той же папке имются индивидуальные JSON файлы под каждый тип генерации:
1. [From Random Truth Table](docs/sampleTruthTable.json)
2. [Rand Level](docs/sampleRandLevel.json)
3. [Num Operation](docs/sampleNumOperation.json)
<!--4. [Genetic](docs/sampleGenetic.json) -->


### Файлы, созданные при генерации 
После генерации схемы создается папка, имя которой совпадает с именем созданной схемы. Помимо самой схемы, в папке по умолчанию генерируется json файл, содержащий информацию о созданной схеме. 


#### Содержимое  выходного json файла
##### Данные по умолчанию
По умолчанию данный файл содержит следующие параметры:<br />
`name` - имя схемы<br />
`numInputs` - число входов<br />
`numOutputs` - число выходов<br />
`maxLevel` - наибольшее возможное количество уровней схемы, т.е. степень "вложенности"<br />
`numEdges` - число связей между логическими элементами, т.е. и-или, вход-или и т.п.<br />
`reliability` - "устойчивость" схемы, рассчитывается при числе входов <= 15. Имеет значение от 0 до 1 включительно <br />
`size` - ?<br />
`area` - площадь итоговой схемы<br />
`longest_path` - наибольший путь (сколько элементов)<br />
`gates` - ?<br />
`sensitivity_factor` - ?<br />
`sinsitivity_factor_percent` - ?<br />
`sensitive_area` - ?<br />
`sensitive_area_percent` - ?<br />
`hash_code` - ? <br />
`numElementsOfEachType` - хеш-таблица (словарь), содержащий в качестве ключей названия элементов в схеме и в качестве значений - 
количество соответсвующих элементов <br />
`numEdgesOfEachType` - количество связей каждого типа между элементами. <br />
<br />
Помимо этих данных, при использовании флагов `calculate_stats_abc`, `make_optimized_files` содержимое файла также дополняется.


##### Данные при использовании флага calculate_stats_abc <br />
При использовании данного флага файл дополняется хеш-таблицей (словарем) `abcStats`. При успешном обсчете схемы с использованием
утилиты abc, словарь содержит следующие значения:
<br />

`area` - площадь схемы <br />
`delay` - задержка распространения <br />
`edge` - количество связей между логическими элементами <br />
`fileRead` - флаг, был ли считан файл <br />
`inputs` - число входов <br />
`inputsNumberCorrect` - флаг, совпадает ли число входов по данным abc с данными после генерации <br />
`lat` - ? <br />
`lev` - количество уровней в схеме <br />
`nd` - число логических элементов в схеме <br />
`outputs` - число выходов <br />
`outputsNumberCorrect` - флаг, совпадает ли число выходов по данным abc с данными после генерации <br />
<br />

##### Данные при использовании флага make_optimized_files <br />
При использовании данного флага создается два словаря, `abcStatsBalance` и `abcStatsResyn2`. Их содержимое идентично. <br />

`area` - площадь схемы <br />
`delay` - задержка распространения <br />
`edge` - количество связей между логическими элементами <br />
`fileRead` - флаг, был ли считан файл <br />
`inputs` - число входов <br />
`lat` - ? <br />
`lev` - количество уровней в схеме <br />
`nd` - число логических элементов в схеме <br />
`outputs` - число выходов <br />


##### Данные при ошибке при использовании любого из вышеупомянутых флагов.
В случае ошибки любой из словарей содержит два значения: <br />
`fileRead` - флаг, был ли считан файл <br />
`error` - сообщение о том, кака ошибка произошла при использовании данной утилиты <br />


#### Файлы, созданные при использовании флага make_optimized_files
При использовании данного флага дополнительно создается некоторое количество файлов. Каждый созданный verilog файл дублируется aig файлом. 
Создается 5 файлов. Один из них является дубликатом основного файла схемы в формате aig. Четрые других содержат оптимизированные схемы. 
Два файла в формате aig дублируют файлы verilog. Фактически генерируется две схемы, одна с использованием метода resyn2, второй - с использованием комбинации 
методов balance и rewrite. 


#### Файлы, созданные при использовании флага make_firrtl
При использовании данного флага создается дубликат изначальной схемы в формате firrtl. Файл, как и прочие сгененированные 
дополнительные файлы, находится в папке с именем схемы

[&#8593; Contents](#content_rus)
