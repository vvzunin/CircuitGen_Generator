#pragma once

#include <string>
#include <memory>
#include <map>
#include <utility>
#include <vector>

enum generationTypes
{
    none,
    truthTableToGraphWithoutOptimization,
    truthTableToGraphWithOptimization
};

enum LibrariesTypes
{
    SKY_LIB
};

/// class Settings
/// 
/// This is the detailed one. More details. Private...
/// @param d_name This is a string field for storing the name of the settings 
/// @param d_singleton Singleton ensures that only one instance of the class exists in the application
/// @param d_path The path to the settings file
/// @param d_csvdataset Contains the name of the CSV file for the dataset. By default, "dataset.csv"
/// @param d_fileName The name of the settings file. The default value is "settings.dat"
/// @param d_datasetPath This is a string field containing the path to the directory with the dataset. The default value is "./dataset"
/// @param d_libraryPath This is a string field that contains the path to the library directory. The default value is set to "Generator/libs"
/// @param d_pathToNadezhda This is a string field that contains the path to the directory with Nadezhda data. The default value is set to "./Generator/source/data/Nadezhda". However, this path is not in the project*
/// @param d_nadezhda ???
/// @param d_numThreads The number of threads that are used in the application. The default value is 4
/// @param d_logicOperations This is an associative std::map container that maps strings (keys) into pairs of strings and integers. It is used to store logical operations and their associated parameters, such as the symbolic representation of the operation and its priority
/// @param d_operationsToHierarchy This is an associative std::map container that maps integers to string vectors. It is used to store a hierarchy of logical operations
/// @param d_operationsToName It is used to match symbolic representations of logical operations and their names.
/// @param d_maxInputs The maximum number of inputs. The default value is 50
/// @param d_maxOutputs The maximum number of outputs. The default value is 50
/// 
///

class Settings
{
protected:
    Settings(const std::string &i_path) : d_path(i_path) {}

public:
    Settings(Settings &other) = delete;
    void operator=(const Settings &) = delete;

    /// @brief getInstance The method is a static method that returns a pointer to the Settings object using the Singleton pattern.
   /// @param i_value used to initialize the path to the file or directory associated with the settings
   /// */

    static std::shared_ptr<Settings> getInstance(const std::string &i_value);

    /// @brief loadSettings
    /// The loading algorithm: 1. Fills in the hierarchy of operations based on the settings of logical operations, where operations with the same priority are collected at the appropriate level of the hierarchy.
    /// 2. Creates a mapping to convert operations to their names.
    /// 3. If the settings file exists, reads the settings from it, including the paths to the Nadezhda tools, the number of threads, logical operations and their parameters, the hierarchy of operations, the conversion of operation names, as well as the maximum number of inputs and outputs
    /// 4. Updates the corresponding variables and data structures of the Settings class with the loaded values from the settings file
    /// */

    void loadSettings();

    /// @brief getInstanceName The method returns the name of the settings instance
   /// @return d_name the value of the variable that is initialized in the constructor of the Settings class
   /// */

    std::string getInstanceName() const;

    /// @brief getLogicOperation The method returns a pair of values associated with a logical operation based on the operation name passed as an argument
   /// @param i_op a string that contains the name of the logical operation whose parameters you want to get. This parameter is key.
   /// @return parameters for a logical operation (example - "and"), 
   /// */

    std::pair<std::string, int> getLogicOperation(const std::string &i_op);

    /// @brief getLogicOperationsKeys The method returns a vector of strings containing the keys (names) of all logical operations available in the Settings object
    /// @return the names of the logical operations available in the Settings object, as a vector of strings. Each element of the vector represents the name of one of the logical operations
    /// */

    std::vector<std::string> getLogicOperationsKeys();

    /// @brief getLogicOperationsWithGates The method returns a pair of vectors. The first vector contains a Boolean value indicating whether the corresponding logical operation is one of the gates, such as NOT or BUF. The second vector contains the names of all logical operations, excluding those specified in the i_not Included vector
   /// @param i_notIncluded A string vector containing the names of logical operations that should not be included in the resulting list of gate operations.For example, if i_not Included contains the strings "not" and "xor", then the NOT and XOR operations will be excluded from the resulting list. The resulting list will contain only those operations whose names are not contained in i_notIncluded.
   /// @return a list of logical operations with information about whether each of them is a gate or not, excluding the operations specified in the i_notIncluded vector.
   /// */

    std::pair<std::vector<bool>, std::vector<std::string>> getLogicOperationsWithGates(std::vector<std::string> i_notIncluded = {});

    /// @brief The method converts the operation name to the corresponding operation name stored in the Settings object
    /// @param i_op a string that contains the name of the logical operation for which you want to get the corresponding operation name
    /// @return the name of the operation corresponding to the specified operation name. For example, if i_op is equal to "and", the method returns "and", if the "and" operation was converted to "logical And" in the Settings object, then the method returns "logical And".
    /// */

    std::string fromOperationsToName(const std::string &i_op) const;

    /// @brief getDatasetPath The method returns a string containing the path to the dataset
   /// @return the path to the dataset
   /// */

    std::string getDatasetPath() const;

    /// @brief getGenerationMethodPrefix The method is designed to get the prefix of the generation method by its name
   /// @param i_s Name of the generation method
   /// @return the corresponding prefix of this method. If the passed name does not match any of the supported methods, the method will display an error message and return the value "ftt"
   /// */

    std::string getGenerationMethodPrefix(const std::string &i_s) const;

    /// @brief getLibraryPath The method returns a string containing the path to the library (library path).
    /// @return The path to the library that is used in the Settings object.
    /// <returns></returns>

    std::string getLibraryPath() const;

    /// @brief getLibraryNameFromEnum The method returns the library name based on the passed Libraries Types enumeration.
    /// @param library the value of the Libraries Types enumeration that points to a specific library
    /// @return library name. Default - sky130.lib
    /// */

    std::string getLibraryNameFromEnum(const LibrariesTypes &library) const;

    /// @brief getMaxInputs The method returns the maximum number of inputs set in the settings
    /// @return the maximum number of inputs set in the Settings object
    /// */

    int getMaxInputs() const;

    /// @brief getMaxOutputs The method returns the maximum number of outputs set in the settings
    /// @return The maximum number of outputs set in the Settings object
    /// */

    int getMaxOutputs() const;

    /// @brief getLogicOperations The method returns a copy of the display containing information about logical operations
   /// @return The returned display contains key-value pairs, where the key is the name of the logical operation, and the value is a pair consisting of its name and priority
   /// */

    std::map<std::string, std::pair<std::string, int>> getLogicOperations() const;

    /// @brief getPathNadezhda The method returns a string containing the path to Nadezhda resources
    /// @return paths (string) to Nadezhda resources
    /// */

    std::string getPathNadezhda() const;

    /// @brief getNadezhdaVar The method returns a string containing the value of a variable from Nadezhda resources by the specified key
    /// @param key a string that is the key to access the value of a variable from Nadezhda resources
    /// @return the values of the variable from Nadezhda resources according to the specified key. For example, if the key is "python", the method returns the path to the Python executable file from Nadezhda resources
    /// */

    std::string getNadezhdaVar(const std::string &key) const;

    /// @brief fromOperationsToHierarchy The method returns a string vector representing the hierarchy of operations for a given key
   /// @param key An integer value that is the key to access the hierarchy of operations in the Settings object.
   /// @return This method returns a string vector representing the hierarchy of operations for the level or type defined by the key. The returned vector contains the names of operations at this level of the hierarchy. For example, if the method is called with the key key, which represents the level of the hierarchy of operations, the method will return a string vector containing the names of operations at this level.

    std::vector<std::string> fromOperationsToHierarchy(int key) const;

    /// @brief getNumThread The method returns the number of threads set in the settings
    /// @return The number of threads set in the Settings object.
    /// */

    int getNumThread() const;

private:
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
    int d_numThreads = 4;
    std::map<std::string, std::pair<std::string, int>> d_logicOperations =
        {
            {"input", {"", 10}},
            {"output", {"=", 0}},
            {"const", {"1'b0", 9}},
            {"and", {"and", 4}},
            {"nand", {"nand", 3}},
            {"or", {"or", 2}},
            {"nor", {"nor", 1}},
            {"not", {"not", 7}},
            {"buf", {"buf", 8}},
            {"xor", {"xor", 6}},
            {"xnor", {"xnor", 5}}

    };
    std::map<int, std::vector<std::string>> d_operationsToHierarchy;
    std::map<std::string, std::string> d_operationsToName;
    int d_maxInputs = 50;
    int d_maxOutputs = 50;
};
