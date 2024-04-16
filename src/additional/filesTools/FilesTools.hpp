#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/// namespace FilesTools
/// The Files Tools namespace contains a set of functions designed to work with
/// the file system
/// */

namespace FilesTools {

/// @brief getDirectories This function takes the path to a directory and
/// returns a string vector containing the names of all subdirectories of that
/// directory.
/// @param path The path to the directory for which you want to get a list of
/// subdirectories
/// @return A string vector containing the names of all subdirectories in the
/// specified directory
/// */

std::vector<std::string> getDirectories(std::string& path);

/// @brief isDirectoryExists This method checks if the specified directory
/// exists
/// @param i_path The path to the directory to be checked for existence
/// @return true if the directory exists and it is a directory; otherwise false.
/// */

bool                     isDirectoryExists(const std::string& i_path);

/// @brief getParentDirOf This method returns the parent directory for the
/// specified path
/// @param i_path The path to the file or directory to get the parent directory
/// for
/// @return A string representing the path to the parent directory of the
/// specified path
/// */

std::string              getParentDirOf(const std::string& i_path);

/// @brief loadStringFile This method loads the contents of the file as a string
/// @param p The path to the file whose contents you want to download
/// @return A string containing the contents of the file*
/// */

std::string              loadStringFile(const std::filesystem::path& p);
}  // namespace FilesTools
