# Добавление нового генератора

Для добавления новых генераторов необходимо внести корректировки в следующие файлы:
## 1. [DataBaseGeneratorParameters.h](source/DataBase/DataBaseGeneratorParameters.h)
В файле необходимо отредактировать перечисление типа **GenerationTypes**, добавив в него название генератора. В качестве примера назавем его **NewGeneratorName**.
## 2. [GeneratorParametrs.h](source/generators/GenerationParameters.h)
В файле необходимо создать новый класс, в который нужно будет добавить дополнительные параметры для использования нового генератора. Название класса должно соответствовать требованию: **Generator** + <имя генератор> + **Parameters**. Используя генератор из примера, класс должен назвываться так: **GeneratorNewGeneratorNameParameters**.
> [!IMPORTANT]
> Не нужно добавлять параметры, для количества входов и выходов схемы. Вся информация о них находится в классе 

**GenerationParameters** в этом же файле.

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