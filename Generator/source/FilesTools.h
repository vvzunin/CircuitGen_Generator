#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace FilesTools
{
  std::vector<std::string> getDirectories(std::string& path)
  {
    std::vector<std::string> res;

    for (const auto & file : std::filesystem::directory_iterator(path))
    {
      if (std::filesystem::is_directory(path))
        res.push_back(file.path());
    }
    return res;
  }
}
