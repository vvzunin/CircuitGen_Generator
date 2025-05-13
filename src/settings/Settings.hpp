#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <CircuitGenGraph/GraphUtils.hpp>

/// @file Settings.hpp

namespace CG_Gen {

enum LibrariesTypes { SKY_LIB };

/// @brief GenerationTypes
/// Enumeration of the types of digital circuit generation.
/// This enumeration defines the various types of digital circuit generation
/// that can be used to create a variety of logic circuits.

enum GenerationTypes {
  FromRandomTruthTable,  /// Generating a circuit from a random truth table
  RandLevel,             /// Random level (experimental)
  RandLevelExperimental, /// Experimental random level generation
  NumOperation,          /// Generating a circuit with numerical operations
  Comparison,            /// The comparison block
  Summator,              /// Adder
  Multiplier,            /// Multiplier
  Subtractor,            /// Subtractor
  Multiplexer,           /// Multiplexer
  Demultiplexer,         /// Demultiplexer
  Encoder,               /// Encoder
  Decoder,               /// Decoder
  Genetic,               /// Genetic generation of the circuit
  Parity,                /// Parity
  ALU,                   /// Arithmetic Logic Unit (ALU)
  MealyMoore,            /// Mealy and Moore
  DotToGraph, /// Dot to graph converter (Mealy and Moore only for now)
  Cascade     /// Cascade
};            /* Simple */

static const std::map<std::string, GenerationTypes> GenerationTypes2Name = {
    {"From Random Truth Table", FromRandomTruthTable},
    {"Rand Level", RandLevel},
    {"Rand Level Experimental", RandLevelExperimental},
    {"Num Operation", NumOperation},
    {"Comparison", Comparison},
    {"Summator", Summator},
    {"Multiplier", Multiplier},
    {"Subtractor", Subtractor},
    {"Multiplexer", Multiplexer},
    {"Demultiplexer", Demultiplexer},
    {"Encoder", Encoder},
    {"Decoder", Decoder},
    {"Genetic", Genetic},
    {"Parity", Parity},
    {"ALU", ALU},
    {"MealyMoore", MealyMoore},
    {"DotToGraph", DotToGraph},
    {"Cascade", Cascade}};

/// @todo: To add Description some fields
/// class Settings
///
/// This is the detailed one. More details. Private...
/// @param d_name This is a string field for storing the name of the settings
/// @param d_singleton Singleton ensures that only one instance of the class
/// exists in the application
/// @param d_path The path to the settings file
/// @param d_csvdataset Contains the name of the CSV file for the dataset. By
/// default, "dataset.csv"
/// @param d_fileName The name of the settings file. The default value is
/// "settings.dat"
/// @param d_datasetPath This is a string field containing the path to the
/// directory with the dataset. The default value is "./dataset"
/// @param d_libraryPath This is a string field that contains the path to the
/// library directory. The default value is set to "Generator/libs"
/// @param d_numThreads The number of threads that are used in the application.
/// The default value is 4
/// @param d_logicOperations This is an associative std::map container that maps
/// strings (keys) into pairs of strings and integers. It is used to store
/// logical operations and their associated parameters, such as the symbolic
/// representation of the operation and its priority
/// @param d_operationsToHierarchy This is an associative std::map container
/// that maps integers to string vectors. It is used to store a hierarchy of
/// logical operations
/// @param d_operationsToName It is used to match symbolic representations of
/// logical operations and their names.
/// @param d_maxInputs The maximum number of inputs. The default value is 50
/// @param d_maxOutputs The maximum number of outputs. The default value is 50
///
///

class Settings {
public:
  Settings(const std::string &i_path) {}

  static void resetSingletone() { d_singleton = nullptr; }
  Settings(Settings &other) = delete;
  void operator=(const Settings &) = delete;

  /// @brief getInstance Gets a single instance of the Settings class
  /// The method provides creation and receipt of a single instance of the
  /// Settings class with the specified value of the settings path. If an
  /// instance already exists, the method returns a pointer to it,
  /// otherwise it creates a new instance, loads the settings from the
  /// file and returns a pointer to it.
  /// @param i_value The value of the path to the settings
  /// @return std::shared_ptr<Settings> A pointer to a single instance of
  /// the Settings class
  /// @code
  /// // Creating a single instance of the Settings class, if it hasn't been
  /// // created yet, and we get a pointer to it
  /// std::shared_ptr<Settings>        settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Now we can use the settings Instance object to access the methods
  /// // and members of the Settings class
  /// std::string datasetPath = settingsInstance->getDatasetPath();
  /// std::cout << "Dataset path: " << datasetPath << std::endl;
  /// @endcode

  static std::shared_ptr<Settings> getInstance(const std::string &i_value);

  /// @brief getInstanceName Gets the name of the current instance of settings
  /// @return std::string Name of the current instance of settings

  std::string getInstanceName() const;

  /// @brief getDatasetPath Returns the path to the dataset
  /// @return std::string The path to the dataset

  std::string getDatasetPath() const;

  /// @brief setDatasetPath Sets the path to the dataset
  /// @param i_datasetPath a string representing the path to the dataset

  void setDatasetPath(const std::string &i_datasetPath);

  /// @brief getGenerationMethodPrefix Gets the prefix of the generation
  /// method by its corresponding GenerationTypes
  /// The method takes the GenerationTypes type variable of the generation
  /// method and returns the corresponding prefix. If the passed GenerationTypes
  /// does not match any of the known methods, std::out_of_range exception is
  /// thrown.
  /// @param i_methodType A GenerationTypes variable containing the name of the
  /// generation method
  /// @return std::string Prefix of the generation method
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object
  /// std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get the prefix of the generation method by its name
  /// GenerationTypes method = GenerationTypes::RandLevel;
  /// std::string prefix = settingsInstance->getGenerationMethodPrefix(method);
  /// std::cout << "Prefix for method " << method << ": " << prefix <<
  /// std::endl;
  /// @endcode

  std::string
  getGenerationMethodPrefix(const GenerationTypes i_methodType) const;

  /// @brief getLibraryPath Returns the path to the library
  /// @return std::string Library path

  std::string getLibraryPath() const;

  /// @brief getLibraryNameFromEnum Gets the library name by its enumerated
  /// type
  /// @param library The enumerated type `LibrariesTypes` representing the
  /// library
  /// @return std::string Library name

  std::string getLibraryNameFromEnum(const LibrariesTypes &library) const;

  /// @brief getMaxInputs Gets the maximum number of inputs
  /// @return uint32_t Maximum number of inputs

  uint32_t getMaxInputs() const;

  /// @brief getMaxOutputs Returns the maximum number of outputs
  /// @return uint32_t Maximum number of outputs

  uint32_t getMaxOutputs() const;

  /// @brief getNumThread Retrieves the number of threads used for processing
  /// @return uint16_t The number of threads configured for processing
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get the number of threads configured for processing
  /// uint16_t numThreads = settingsInstance->getNumThread();
  /// std::cout << "Number of threads: " << numThreads << std::endl;
  /// @endcode

  uint16_t getNumThread() const;
  void setNumThread(uint16_t i_numThreads);

  /// @brief parseGateToString Converts an enum value of a gate to its
  /// corresponding string representation
  /// @param gate The enum value representing the gate
  /// @return std::string The string representation of the provided gate enum
  /// value This method converts an enum value representing a gate to its
  /// corresponding string representation.
  /// It retrieves the string representation from the internal map date
  /// ToString, which maps enum values of gates to their string
  /// representations.
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Convert the enum value Gates::GateAnd to its corresponding string
  /// representation std::string gateString =
  /// settingsInstance->parseGateToString(Gates::GateAnd); std::cout << "String
  /// representation of Gates::GateAnd: " << gateString << std::endl;
  /// @endcode

private:
  /// @brief SaveSettings Saves the current settings to a file
  /// This method saves the current settings of the Settings object to a file
  /// specified by d_fileName. It writes various settings parameters, such as
  /// dataset information, Nadezhda dictionary, number of threads, logical
  /// operations, operation hierarchies, operation names, and maximum
  /// inputs/outputs, to the file in a structured format
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Save the current settings to a file
  /// settingsInstance->SaveSettings();
  /// @endcode

  void SaveSettings();

  std::string d_name;
  static std::shared_ptr<Settings> d_singleton;
  std::string d_path;
  std::string d_csvdataset = "dataset.csv";
  std::string d_fileName = "settings.dat";
  std::string d_datasetPath = "./dataset";
  std::string d_libraryPath = "Generator/libs";
  // Settings d_instance;
  uint16_t d_numThreads = 4;

  std::map<GenerationTypes, std::string> generationTypeToPrefix = {
      {GenerationTypes::FromRandomTruthTable, "CCGRTT"},
      {GenerationTypes::RandLevel, "CCGRCG"},
      {GenerationTypes::RandLevelExperimental, "CCGRCGE"},
      {GenerationTypes::NumOperation, "CCGRVC"},
      {GenerationTypes::Genetic, "CCGGA"},
      {GenerationTypes::Summator, "CCGTCSM"},
      {GenerationTypes::Comparison, "CCGTCC"},
      {GenerationTypes::Encoder, "CCGECR"},
      {GenerationTypes::Subtractor, "CCGTCSB"},
      {GenerationTypes::Parity, "CCGTCP"},
      {GenerationTypes::Multiplier, "CCGTCM"},
      {GenerationTypes::Demultiplexer, "CCGTCDMP"},
      {GenerationTypes::Multiplexer, "CCGTCMP"},
      {GenerationTypes::Decoder, "CCGDCR"},
      {GenerationTypes::ALU, "CCGALU"},
      {GenerationTypes::MealyMoore, "CCGMM"},
      {GenerationTypes::DotToGraph, "CCGDTG"},
      {GenerationTypes::Cascade, "CCGCCD"}};
  /*
    SimpleGenerator
  */

  uint32_t d_maxInputs = 50;
  uint32_t d_maxOutputs = 50;
};

} // namespace CG_Gen
