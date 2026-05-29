# Adding a new generator

To add a new generator, update the following files.

## 1.1 [Settings.hpp](../../src/settings/Settings.hpp)

Edit the **GenerationTypes** enum and add the generator name. In this guide we use **NewGeneratorName** as an example.

## 1.2 [Settings.hpp](../../src/settings/Settings.hpp)

In the same file, update **generationTypeToPrefix** with a new prefix for generated `.v`, `.json`, and other files. The prefix must start with three letters: **CCG**, followed by an abbreviation of the method. For the example name:

```cpp
{GenerationTypes::NewGeneratorName, "CCGNGN"}
```

**CCG** stands for **Combinational Circuit Generator**; replace **NGN** with a clearer abbreviation for your method.

## 2. [GenerationParameters.hpp](../../src/generators/GenerationParameters.hpp)

Add a new class for generator-specific parameters. Name it **Generator** + \<GeneratorName\> + **Parameters** — e.g. **GeneratorNewGeneratorNameParameters**.

> [!IMPORTANT]
> Do not add parameters for the number of inputs and outputs; that information lives in **GenerationParameters** in the same file.

In **GenerationParameters**, add a *private* member of the new class named **d_generator** + \<GeneratorName\> + **Parameters** — e.g. **d_generatorNewGeneratorNameParameters**. Add a getter and setter: the getter returns the struct; the setter accepts values and assigns them.

## 3. [SimpleGenerators.hpp](../../src/generators/simple/SimpleGenerators.hpp) and [SimpleGenerators.cpp](../../src/generators/simple/SimpleGenerators.cpp)

Implement the generator. In **SimpleGenerators.hpp**, declare:

```cpp
GraphPtr generatorNewGeneratorName(...);
```

The method must return **GraphPtr** (`std::shared_ptr<OrientedGraph>`) and take every parameter it needs. Input parameters must use the **i_** prefix.

> [!IMPORTANT]
> Input variable names must start with **i_**.

In **SimpleGenerators.cpp**, implement:

```cpp
GraphPtr SimpleGenerators::generatorNewGeneratorName(...) {
   ...
}
```

## 4. [DataBaseGenerator.hpp](../../src/database/dataBaseGenerator/DataBaseGenerator.hpp) and [DataBaseGenerator.cpp](../../src/database/dataBaseGenerator/DataBaseGenerator.cpp)

In **DataBaseGenerator**, add a method that takes a const reference to generation parameters *i_param*, constructs **SimpleGenerators**, calls your generator with parameters from *i_param* in the declared order, stores the result in **GraphPtr**, builds **Circuit** from the graph, calls `setPath` with *d_mainPath*, `setCircuitName` with `i_param.getName()`, then `generate` with `i_param.getMakeGraphMLClassic()`, `i_param.getMakeGraphMLPseudoABCD()`, `i_param.getMakeGraphMLOpenABCD()`.

<!--
Currently only getMakeGraphMLClassic(), getMakeGraphMLPseudoABCD(), getMakeGraphMLOpenABCD() are wired; extend as needed.
-->

Example implementation:

```cpp
void DataBaseGenerator::generateNewGeneratorName(GenerationParameters &i_param) {
  SimpleGenerators sg;
  ...
  GraphPtr graph = sg.generatorNewGeneratorName(...);
  Circuit c (graph);
  c.setPath(d_mainPath);
  c.setCircuitName(i_param.getName());
  c.generate(
    i_param.getMakeGraphMLClassic(),
    i_param.getMakeGraphMLPseudoABCD(),
    i_param.getMakeGraphMLOpenABCD()
  );
}
```

Header declaration:

```cpp
void generateNewGeneratorName(const GenerationParameters& i_param);
```

In **DataBaseGenerator.cpp**, inside **getGenerateMethod**, add a **case** for the new type:

```cpp
case GenerationTypes::NewGeneratorName:
  generateMethodFunc = &DataBaseGenerator::generateNewGeneratorName;
  break;
```

## 5. [CircuitGenGenerator.cpp](../../src/CircuitGenGenerator.cpp)

In **runGenerationFromJson**, after initializing *GenerationTypes gt*, parse the JSON and set the type when `type_of_generation` matches:

```cpp
else if (data["type_of_generation"] == "NewGeneratorName")
	gt = GenerationTypes::NewGeneratorName;
```

If the generator needs extra fields, read them from **data** and pass them into **GenerationParameters** via your setter:

```cpp
gp.setNewGeneratorNameParameters(...);
```

That completes wiring. Add a JSON file with the parameters your generator expects.

**Русский:** [Добавление генератора](../ru/NewGenerator.md)
