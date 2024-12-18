#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <CircuitGenGraph/DefaultSettings.hpp>

/// @file Settings.hpp

enum LibrariesTypes { SKY_LIB };

/// @brief GenerationTypes
/// Enumeration of the types of digital circuit generation.
/// This enumeration defines the various types of digital circuit generation
/// that can be used to create a variety of logic circuits.

enum GenerationTypes {   /// Generating a circuit from a random truth table
  FromRandomTruthTable,  /// Random level (experimental)
  RandLevel,             /// Experimental random level generation
  RandLevelExperimental, /// Generating a circuit with numerical operations
  NumOperation,          /// Genetic generation of the circuit
  Genetic,               /// Adder
  Summator,              /// The comparison block
  Comparison,            /// The encoder
  Encoder,               /// Subtractor
  Subtractor,            /// Multiplexer
  Multiplexer,           /// Demultiplexer
  Demultiplexer,         /// Multiplier
  Multiplier,            /// Decoder
  Decoder,               /// Parity
  Parity,                /// Arithmetic Logic Unit (ALU)
  ALU
};

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
/// @param d_pathToNadezhda This is a string field that contains the path to the
/// directory with Nadezhda data. The default value is set to
/// "./Generator/source/data/Nadezhda". However, this path is not in the
/// project*
/// @param d_nadezhda ???
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

class Settings : public DefaultSettings {
public:
  Settings(const std::string &i_path) : DefaultSettings(i_path) {}

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

  /// @brief loadSettings Downloads settings from a file
  /// The method loads the settings from a file with the name specified in
  /// the data member in_filename. If the file exists, the method reads the
  /// settings values from it and updates the corresponding data members of
  /// the class

  void loadSettings();

  /// @brief getInstanceName Gets the name of the current instance of settings
  /// @return std::string Name of the current instance of settings

  std::string getInstanceName() const;

  /// @brief getLogicOperationsKeys Returns the keys of logical operations
  /// @return std::vector<Gates> A vector containing the keys of logical
  /// operations

  std::vector<Gates> getLogicOperationsKeys();

  /// @brief getLogicOperationsWithGates Returns logical operations along with
  /// information about the presence of a single input
  /// The method returns a pair of vectors: the first vector contains
  /// information about whether each a logical operation has only one
  /// input(true if this is the case, false otherwise),
  /// and the second vector contains the keys(enumerated values) of all
  /// available logical operations
  /// @return std::pair<std::vector<bool>, std::vector<Gates>> A pair of
  /// vectors: information about the presence of a single input and the keys
  /// of logical operations
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// // existing object
  /// std::shared_ptr<Settings>        settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get logical operations together with information about the presence
  /// // of a single input
  /// std::pair<std::vector<bool>, std::vector<Gates>> logicOperationsInfo =
  /// settingsInstance->getLogicOperationsWithGates();
  /// // Output information about each logical operation
  /// for (size_t i = 0; i < logicOperationsInfo.second.size(); ++i)
  /// {
  /// std::string operationName =
  /// settingsInstance->parseGateToString(logicOperationsInfo.second[i]);
  /// bool hasOneInput = logicOperationsInfo.first[i];
  /// std::cout << "Operation: " << operationName;
  /// if (hasOneInput)
  /// {
  ///   std::cout << " (Has one input)";
  /// }
  /// else
  /// {
  ///   std::cout << " (Does not have one input)";
  /// }
  /// std::cout << std::endl;
  /// }
  /// @endcode

  std::pair<std::vector<bool>, std::vector<Gates>>
  getLogicOperationsWithGates();

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

  /// @brief getLogicOperations all logical operations
  /// The method returns a dictionary containing all logical operations
  /// in the form of a pair, where the key is a string representing the
  /// name of the operation, and the value is a pair in which the first
  /// element is a string representing the name of the operation, and the
  /// second element is an integer value representing the identifier of
  /// the operation
  /// @return std::map<std::string, std::pair<std::string, int32_t>> Dictionary
  /// with logical operations

  std::map<std::string, std::pair<std::string, int32_t>>
  getLogicOperations() const;

  /// @brief getPathNadezhda Returns the path to Nadezhda
  /// @return std::string Path to Nadezhda

  std::string getPathNadezhda() const;

  /// @brief getNadezhdaVar Gets the value of a variable from the Nadezhda
  /// dictionary by key
  /// @param key The key used to search for a value in the Nadezhda dictionary
  /// @return std::string The value corresponding to the provided key in the
  /// Nadezhda dictionary

  std::string getNadezhdaVar(const std::string &key) const;

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
  std::string d_pathToNadezhda = "./Generator/source/data/Nadezhda";
  std::map<std::string, std::string> d_nadezhda = {
      {"python", "python3"},
      {"resynthesis", "Nadezhda/Scripts/resynthesis_local_rewriting.pyc"},
      {"reliability", "Nadezhda/Scripts/check_reliability.pyc"},
      {"liberty", "Nadezda/Test/Nangate.lib"}};
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
      {GenerationTypes::ALU, "CCGALU"}};

  uint32_t d_maxInputs = 50;
  uint32_t d_maxOutputs = 50;
};