#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace FilesTools
{
  std::vector<std::string> getDirectories(std::string& path);
  bool isDirectoryExists(const std::string& i_path);
  std::string getParentDirOf(const std::string& i_path);
  std::string loadStringFile(const std::filesystem::path& p);
}
