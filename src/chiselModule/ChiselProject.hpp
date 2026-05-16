#pragma once

#include "additional/tempProjectDir/TempProjectDir.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace CG_Gen {

struct ModuleInfo {
  std::string d_name;
  bool d_hasParams;
};

/// class ChiselProject
/// This class is for temporary Chisel project management. mainly used for
/// executing .scala files and generating verilog out of Chisel description
/// @param d_tempDirPath Path for temporary project directory
/// @param d_baseDir Absolute path for root directory of whole project
/// (CircuitGen Generator)
/// @param d_outputDir Path for directory where verilog files will be placed
/// @param d_mainObject Name of main executable object for SBT
/// @param d_temProject An instance of TempProjectDir class, where project will
/// be executed
/// */

class ChiselProject {
public:
  ChiselProject(const std::filesystem::path &i_baseDir,
                const std::filesystem::path &i_tempDirPath,
                const std::filesystem::path &i_outputDir,
                const std::filesystem::path &i_inputFile);

  /// @brief makeAbsolutePath method makes absolute path from relative
  /// @param i_relativePath relative path to be transformed
  /// @return absolute path made from relative path
  /// */

  std::filesystem::path
  makeAbsolutePath(const std::filesystem::path &i_relativePath) const;

  ChiselProject(const ChiselProject &) = delete;
  ChiselProject &operator=(const ChiselProject &) = delete;

  /// @brief checkPackages method checks packages and dependencies required for
  /// compilation and execution of .scala files
  /// @return true if all packages are installed and false otherwise
  /// */

  bool checkPackages();

  /// @brief createVerilog method starts compilation of .scala files and creates
  /// their verilog descriptions
  /// @return true if creation was successful and false otherwise
  /// */

  bool createVerilog();

private:
  std::filesystem::path d_tempDirPath;
  std::filesystem::path d_baseDir;
  std::filesystem::path d_outputDir;
  std::string d_mainObject;
  TempProjectDir d_tempProject;

  /// @brief createMainModule method creates entry point for chisel project in
  /// case of its absence in initial file
  /// @param i_inputFile Path for initial .scala file with Chisel description
  /// @param i_outputPath Path for directory where verilog files will be placed
  /// @return Name of main object for SBT that will be compiled
  /// */

  std::string createMainModule(const std::filesystem::path &i_inputFile,
                               const std::filesystem::path &i_outputPath) const;

  /// @brief adaptMainModule method adapts existing main module with verilog
  /// output directory path setting
  /// @param i_inputFile Path for initial .scala file with Chisel description
  /// @param i_outputPath Path for directory where verilog files will be placed
  /// @return Name of main object for SBT that will be compiled
  /// */

  std::string adaptMainModule(const std::filesystem::path &i_inputFile,
                              const std::filesystem::path &i_outputPath) const;

  /// @brief findAllModules method searches all individual modules in initial
  /// user's file
  /// @param i_inputFile Path for initial .scala file with Chisel description
  /// @return vector of ModuleInfo structure instances containing information
  /// about each module found */

  std::vector<ModuleInfo>
  findAllModules(const std::filesystem::path &i_inputFile) const;

  /// @brief hasAnyParameterizedModules method checks if there are any modules
  /// in initial user's file which accept parameters as input
  /// @param i_modules vector of ModuleInfo structure instances describing all
  /// existing modules in initial user's file
  /// @return true if parameterized modules exist and false otherwise
  /// */

  bool hasAnyParameterizedModules(std::vector<ModuleInfo> &i_modules) const;

  /// @brief ifMainInInput method checks if there is an entry point for Chisel
  /// project in initial user's file
  /// @param i_inputFile Path for initial .scala file with Chisel description
  /// @return true if Main module exists and false otherwise
  /// */

  bool ifMainInInput(const std::filesystem::path &i_inputFile) const;

  /// @brief createBuildFile method authomatically generates building file for
  /// Chisel project
  /// @param i_projectDir Path for temporary Chisel project directory
  /// @param i_scalaVersion Current version of Scala being used
  /// @param i_chiselVersion Current version of Chisel being used
  /// @return Path for generated Build file
  /// */

  std::filesystem::path
  createBuildFile(const std::filesystem::path &i_projectDir,
                  const std::string &i_scalaVersion = "2.13.12",
                  const std::string &i_chiselVersion = "6.0.0") const;

  /// @brief cleanGeneratedFiles method removes side-generated files, such as
  /// .json and .fir in output directory
  /// @param i_outputPath Path for directory where verilog files will be placed
  /// */

  void cleanGeneratedFiles(const std::filesystem::path &i_outputPath);
};
} // namespace CG_Gen