#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace FilesTools {
std::vector<std::string> getDirectories(std::string &path);
bool isDirectoryExists(const std::string &i_path);
std::string getParentDirOf(const std::string &i_path);
std::string loadStringFile(const std::filesystem::path &p);
}  // namespace FilesTools
