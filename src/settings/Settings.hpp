#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

enum generationTypes {
  none,
  truthTableToGraphWithoutOptimization,
  truthTableToGraphWithOptimization
};

enum LibrariesTypes {
  SKY_LIB
};

enum VertexTypes {
  input,
  output,
  constant,
  gate
};

enum Gates {
  GateAnd,
  GateNand,
  GateOr,
  GateNor,
  GateXor,
  GateXnor,
  GateNot,
  GateBuf,
  GateDefault,
};

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

class Settings {
protected:
  Settings(const std::string& i_path) : d_path(i_path) {}

public:
  Settings(Settings& other)                                   = delete;
  void                             operator=(const Settings&) = delete;

  /// @getInstance Gets a single instance of the Settings class
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
  /// @end_code

  static std::shared_ptr<Settings> getInstance(const std::string& i_value);

  /// @brief loadSettings Downloads settings from a file
  /// The method loads the settings from a file with the name specified in
  /// the data member in_filename. If the file exists, the method reads the
  /// settings values from it and updates the corresponding data members of
  /// the class

  void                             loadSettings();

  /// @brief getInstanceName Gets the name of the current instance of settings
  /// @return std::string Name of the current instance of settings

  std::string                      getInstanceName() const;

  /// @brief getLogicOperation Gets information about a logical operation by
  /// its name
  /// @param i_op A string containing the name of the logical operation
  /// @return std::pair<std::string, int> A pair containing the name and ID
  /// of the logical operation
  /// @code
  /// Settings settingsInstance;
  /// try {
  /// // Get information about the logical operation "and"
  /// std::pair<std::string, int> operationInfo =
  /// settingsInstance.getLogicOperation("and");
  /// // Output information about the logical operation
  /// std::cout << "Operation name: " << operationInfo.first << std::endl;
  /// std::cout << "Operation ID: " << operationInfo.second << std::endl;
  /// } catch (const std::out_of_range& e) {
  /// // Handle an exception if the operation is not found
  /// std::cerr << "Error: " << e.what() << std::endl;
  /// }
  /// @end_code
  /// @throws std::out_of_range If the passed operation name does not exist
  /// in the list of logical operations

  std::pair<std::string, int>      getLogicOperation(const std::string& i_op);

  /// @brief getLogicOperationsKeys Returns the keys of logical operations
  /// @return std::vector<Gates> A vector containing the keys of logical
  /// operations

  std::vector<Gates>               getLogicOperationsKeys();

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
  /// @end_code

  std::pair<std::vector<bool>, std::vector<Gates>> getLogicOperationsWithGates(
  );

  /// @brief fromOperationsToName Converts the operation to its name
  /// @param i_op a string representing the operation
  /// @return std::string Operation name
  /// @code
  /// // Creating an instance of the Settings class or getting it from
  /// an existing object
  /// std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// Convert the operation to its name
  /// std::string operationName;
  /// try
  /// {
  /// operationName = settingsInstance->fromOperationsToName("and");
  /// std::cout << "Operation name: " << operationName << std::endl;
  /// } catch (const std::out_of_range& e) {
  /// std::cerr << "Error: " << e.what() << std::endl;
  /// }
  /// @end_code
  /// @throw std::out_of_range If the passed operation does not exist in the
  /// list of operations

  std::string fromOperationsToName(const std::string& i_op) const;

  /// @brief getDatasetPath Returns the path to the dataset
  /// @return std::string The path to the dataset

  std::string getDatasetPath() const;

  /// @brief getGenerationMethodPrefix Gets the prefix of the generation
  /// method by its name
  /// The method takes the name of the generation method and returns the
  /// corresponding prefix. If the passed name does not match any of the
  /// known methods, an error message is displayed, and the default value
  /// "ftt" is returned.
  /// @param i_s A string containing the name of the generation method
  /// @return std::string Prefix of the generation method
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object
  /// std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get the prefix of the generation method by its name
  /// std::string method = "RandLevel";
  /// std::string prefix = settingsInstance->getGenerationMethodPrefix(method);
  /// std::cout << "Prefix for method " << method << ": " << prefix <<
  /// std::endl;
  /// @end_code

  std::string getGenerationMethodPrefix(const std::string& i_s) const;

  /// @brief getLibraryPath Returns the path to the library
  /// @return std::string Library path

  std::string getLibraryPath() const;

  /// @brief getLibraryNameFromEnum Gets the library name by its enumerated
  /// type
  /// @param library The enumerated type `LibrariesTypes` representing the
  /// library
  /// @return std::string Library name

  std::string getLibraryNameFromEnum(const LibrariesTypes& library) const;

  /// @brief getMaxInputs Gets the maximum number of inputs
  /// @return int Maximum number of inputs

  int         getMaxInputs() const;

  /// @brief getMaxOutputs Returns the maximum number of outputs
  /// @return int Maximum number of outputs

  int         getMaxOutputs() const;

  /// @brief getLogicOperations all logical operations
  /// The method returns a dictionary containing all logical operations
  /// in the form of a pair, where the key is a string representing the
  /// name of the operation, and the value is a pair in which the first
  /// element is a string representing the name of the operation, and the
  /// second element is an integer value representing the identifier of
  /// the operation
  /// @return std::map<std::string, std::pair<std::string, int>> Dictionary
  /// with logical operations

  std::map<std::string, std::pair<std::string, int>> getLogicOperations() const;

  /// @brief getPathNadezhda Returns the path to Nadezhda
  /// @return std::string Path to Nadezhda

  std::string                                        getPathNadezhda() const;

  /// @brief getNadezhdaVar Gets the value of a variable from the Nadezhda
  /// dictionary by key
  /// @param key The key used to search for a value in the Nadezhda dictionary
  /// @return std::string The value corresponding to the provided key in the
  /// Nadezhda dictionary

  std::string              getNadezhdaVar(const std::string& key) const;

  /// @brief fromOperationsToHierarchy Converts an operation key to its
  /// corresponding hierarchy
  /// @param key The key representing the operation
  /// @return std::vector<std::string> The hierarchy associated with the
  /// operation key
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get the hierarchy associated with the operation key 5
  /// std::vector<std::string> operationHierarchy =
  /// settingsInstance->fromOperationsToHierarchy(5);
  /// // Output the hierarchy
  /// for(const auto& element : operationHierarchy)
  /// {
  ///     std::cout << element << " ";
  /// }
  /// std::cout << std::endl;
  /// @end_code
  /// @throws std::out_of_range If the provided key does not exist in the
  /// internal map of operation keys to hierarchies

  std::vector<std::string> fromOperationsToHierarchy(int key) const;

  /// @brief getNumThread Retrieves the number of threads used for processing
  /// @return int The number of threads configured for processing
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Get the number of threads configured for processing
  /// int numThreads = settingsInstance->getNumThread();
  /// std::cout << "Number of threads: " << numThreads << std::endl;
  /// @end_code

  int                      getNumThread() const;

  /// @brief parseStringToGate Converts a string representation of a gate to
  /// its corresponding enum value
  /// @param i_gate The string representation of the gate
  /// @return Gates The enum value corresponding to the provided string
  /// representation of the gate
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Convert the string representation "and" to its corresponding enum value
  /// Gates gate = settingsInstance->parseStringToGate("and");
  /// std::cout << "Enum value of 'and': " << gate << std::endl;
  /// @end_code

  Gates                    parseStringToGate(std::string i_gate) const;

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
  /// @end_code

  std::string              parseGateToString(Gates gate) const;

  /// @brief parseVertexToString Converts an enum value of a vertex type to its
  /// corresponding string representation
  /// @param vertex The enum value representing the vertex type
  /// @return std::string The string representation of the provided vertex type
  /// enum value
  /// @code
  /// // Creating an instance of the Settings class or getting it from an
  /// existing object std::shared_ptr<Settings> settingsInstance =
  /// Settings::getInstance("/path/to/settings");
  /// // Convert the enum value VertexTypes::input to its corresponding string
  /// representation std::string vertexString =
  /// settingsInstance->parseVertexToString(VertexTypes::input); std::cout <<
  /// "String representation of VertexTypes::input: " << vertexString <<
  /// std::endl;
  /// @end_code

  std::string              parseVertexToString(VertexTypes vertex) const;

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
  /// @end_code

  void                             SaveSettings();

  std::string                      d_name;
  static std::shared_ptr<Settings> d_singleton;
  std::string                      d_path;
  std::string                      d_csvdataset  = "dataset.csv";
  std::string                      d_fileName    = "settings.dat";
  std::string                      d_datasetPath = "./dataset";
  std::string                      d_libraryPath = "Generator/libs";
  // Settings d_instance;
  std::string d_pathToNadezhda = "./Generator/source/data/Nadezhda";
  std::map<std::string, std::string> d_nadezhda = {
      {"python", "python3"},
      {"resynthesis", "Nadezhda/Scripts/resynthesis_local_rewriting.pyc"},
      {"reliability", "Nadezhda/Scripts/check_reliability.pyc"},
      {"liberty", "Nadezda/Test/Nangate.lib"}};
  int                                                d_numThreads      = 4;
  std::map<std::string, std::pair<std::string, int>> d_logicOperations = {
      {"input", {"", 10}},
      {"output", {"=", 0}},
      {"const", {"1'b0", 9}},
      {"and", {"and", 4}},
      {"nand", {"nand", 3}},
      {"or", {"or", 6}},
      {"nor", {"nor", 5}},
      {"not", {"not", 7}},
      {"buf", {"buf", 8}},
      {"xor", {"xor", 2}},
      {"xnor", {"xnor", 1}}

  };

  std::map<std::string, Gates> stringToGate = {
      {"and", Gates::GateAnd},
      {"nand", Gates::GateNand},
      {"or", Gates::GateOr},
      {"nor", Gates::GateNor},
      {"not", Gates::GateNot},
      {"buf", Gates::GateBuf},
      {"xor", Gates::GateXor},
      {"xnor", Gates::GateXnor}};

  std::map<Gates, std::string> gateToString = {
      {Gates::GateAnd, "and"},
      {Gates::GateNand, "nand"},
      {Gates::GateOr, "or"},
      {Gates::GateNor, "nor"},
      {Gates::GateNot, "not"},
      {Gates::GateBuf, "buf"},
      {Gates::GateXor, "xor"},
      {Gates::GateXnor, "xnor"},
      {Gates::GateDefault, "ERROR"}};

  std::vector<Gates> d_logicElements = {
      Gates::GateAnd,
      Gates::GateNand,
      Gates::GateOr,
      Gates::GateNor,
      Gates::GateXor,
      Gates::GateXnor,
      Gates::GateNot,
      Gates::GateBuf};

  std::map<VertexTypes, std::string> vertexToString = {
      {VertexTypes::input, "input"},
      {VertexTypes::output, "output"},
      {VertexTypes::constant, "const"},
      {VertexTypes::gate, "g"}};

  std::map<int, std::vector<std::string>> d_operationsToHierarchy;
  std::map<std::string, std::string>      d_operationsToName;
  int                                     d_maxInputs  = 50;
  int                                     d_maxOutputs = 50;
};