# Добавление нового генератора

Для добавления новых генераторов необходимо внести корректировки в следующие файлы:
## 1.1 [Settings.hpp](src/settings/Settings.hpp)
В файле необходимо отредактировать перечисление типа **GenerationTypes**, добавив в него название генератора. В качестве примера назовем его **NewGeneratorName**.
## 1.2 [Settings.hpp](src/settings/Settings.hpp)
В этом же необходимо внести изменения в поле **generationTypeToPrefix**. Необходимо добавить новый префикс для генерируемых в результате файлов формата .v, .json и других. Префикс должен начинаться с трех букв — **CCG**. Далее следует аббревиатура названия метода генерации. Используя название генератора из примера, получаем следующую вставку:
```
{GenerationTypes::NewGeneratorName, "CCGNGN"}
```
**CCG** — **Combinational Circuit Generator**, вместо **NGN** можно указать более подходящее на взгляд автора обозначения для созданного метода генерации.
## 2. [GeneratorParameters.hpp](src/generators/GenerationParameters.hpp)
В файле необходимо создать новый класс, в который нужно будет добавить дополнительные параметры для использования нового генератора. Название класса должно соответствовать требованию: **Generator** + <имя генератор> + **Parameters**. Используя генератор из примера, класс должен назвываться так: **GeneratorNewGeneratorNameParameters**.
> [!IMPORTANT]
> Не нужно добавлять параметры, для количества входов и выходов схемы. Вся информация о них находится в классе 

**GenerationParameters** в этом же файле.

Далее необходимо в классе **GenerationParameters** создать в разделе *private* переменную ранее созданного класса. Название переменной соответствует следующему требованию: **d_generator** + <имя генератор> + **Parameters**. Для примера переменная будет иметь следующее название: **d_generatorNewGeneratorNameParameters**.
Для данной переменной необходимо создать геттер и сеттер. Геттер возвращает саму переменную, сеттер — получает на вход переменные для данного класса и записывает в переменную с параметрами.
## 3. [SimpleGenerators.hpp](src/generators/simple/SimpleGenerators.hpp) и [SimpleGenerators.cpp](src/generators/simple/SimpleGenerators.cpp)
В данных файлах необходимо реализовать сам генератор (метод для генерации схемы). В **SimpleGenerators.h** необходимо добавить описание метода генерации:
```
GraphPtr generatorNewGeneratorName(...);
```
В качестве результата метод должен возвращать сгенерированную схему в формате **GraphPtr**, являющуюся, в свою очердедь, псевдонимом для типа **std::shared_ptr<OrientedGraph>**. В качестве входных данных метод должен принимать все необходмые для его использования переменные.
> [!IMPORTANT]
> Имена входных переменных должны начинаться с префикса **i_**.

В **SimpleGenerators.cpp** необходимо реализовать сам генератор:
```
GraphPtr SimpleGenerators::generatorNewGeneratorName(...) {
   ...
}
```
## 4. [DataBaseGenerator.hpp](src/database/DataBaseGenerator.hpp) и [DataBaseGenerator.cpp](src/database/DataBaseGenerator.cpp)
В классе **DataBaseGenerator** необходимо реализовать метод, который будет на вход получать константную ссылку на параметры генерации *i_param*,  которая содержит все необходимые параметры генерации. В данном методе необходимо создать объект класса **SimpleGenerator** и запустить в нем ранее созданный метод, в который нужно передать все необходимые параметры из *i_param* в том же порядке, в котором они были описаны в реализации метода. Результат необходимо записать в переменную типа **GraphPtr**. После этого необходимо создать переменную типа **Circuit** и в качестве параметра конструктора передать полученный граф. После этого необходимо задать путь генерации (setPath) в качестве которого выступает *d_mainPath*. Также нужно задать название схемы (setCircuitName) присутствующее в параметрах генерации (i_param.getName()). После этого необходимо запустить генерацию схемы в формате Verilog и обсчет параметров (generate), передав набор параметров: i_param.getMakeGraphML().
<!--
На данный момент в коде используется только i_param.getMakeGraphML(). По мере реализации нужно добавить другие параметры из списка ниже (или ввести новые)
i_param.getLibraryName(), i_param.getCalculateStatsAbc(), i_param.getMakeOptimizedFiles(), i_param.getMakeFirrtl(), i_param.getMakeBench(), i_param.getMakeGraphML()
-->

Используя приведенные ранее примеры названий методов, получаем следующий код для реализации метода:
```
void DataBaseGenerator::generateNewGeneratorName(GenerationParameters &i_param) {
  SimpleGenerators sg;
  ...
  GraphPtr graph = sg.generatorNewGeneratorName(...);
  Circuit c (graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(i_param.getMakeGraphML());
}
```
И код для описания метода в header:
```
void generateNewGeneratorName(const GenerationParameters& i_param);
```
Далее в файле [DataBaseGenerator.cpp](src/database/DataBaseGenerator.cpp) необходимо в функции **getGenerateMethod** реализовать обработку нового имени генератора (новый case в switch-конструкции). Используя название генератора из примера, получаем следующую вставку:
```
case GenerationTypes::NewGeneratorName:
  generateMethodFunc =
    &DataBaseGenerator::generateNewGeneratorName;
  break;
```
## 5. [CircuitGenGenerator.cpp](src/CircuitGenGenerator.cpp)
Последним шагом является редактирование файла **CircuitGenGenerator.cpp**. В функцию **runGenerationFromJson** после инициализации *GenerationTypes gt* необходимо добавить условие на выбор метода генерации. Используя ранее заданное название генератора в качестве примера, получим следующий участок кода:
```
else if (data["type_of_generation"] == "NewGeneratorName")
	gt = GenerationTypes::NewGeneratorName;
```
Если для работы генератора требуются дополнительные параметры, то следует обратиться к переменной data, содержащей данные из json-файла с параметрами для генерации, и передать их в класс **GenerationParameters** (имя переменной — **gp**) с помощью созданного ранее сеттера:
```
gp.setNewGeneratorNameParameters(...);
```
На этом добавление генератора в программу закончено. Осталось только добавить в файл json названия параметров.