#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace CG_Gen {

/// class TempProjectDir
/// This class is for temporary project directory creation and management
/// @param d_path Absolute path for directory for temporary project made by
/// this class
/// @param d_baseDir Absolute path for root directory of whole project
/// (CircuitGen Generator)
/// */

class TempProjectDir {
private:
  std::filesystem::path d_path;
  std::filesystem::path d_baseDir;

public:
  TempProjectDir(const std::filesystem::path &i_path,
                 const std::filesystem::path &i_baseDir);
  ~TempProjectDir();

  /// @brief createSubDirectory method for creating directories in temporary
  /// project
  /// @param i_name name of subdirectory
  /// @return absolute path for created subdirectory
  /// */

  std::filesystem::path createSubDirectory(const std::string &i_name);

  /// @brief copyFile method creating copy of selected file in specified
  /// directory
  /// @param i_source path for thr file being copeied
  /// @param i_destination the path to the directory to which the copied file
  /// will be copied (including filename with extension)
  /// @return true if copying was successful and false otherwise
  /// */

  bool copyFile(const std::filesystem::path &i_source,
                const std::filesystem::path &i_destination);

  /// @brief createFile method creates new file with specified name and content
  /// @param i_filename name of file being created
  /// @param i_content content of file being created
  /// @return true if creation was successful and false otherwise
  /// */

  bool createFile(const std::string &i_filename, const std::string i_content);
};

} // namespace CG_Gen