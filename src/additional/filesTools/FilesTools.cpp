#include "FilesTools.hpp"

namespace FilesTools {
std::vector<std::string> getDirectories(std::string& path) {
  std::vector<std::string> res;

  for (const auto& file : std::filesystem::directory_iterator(path)) {
    if (std::filesystem::is_directory(file)) {
      std::string path      = file.path().string();
      size_t      lastSlash = 0;
      for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == std::filesystem::path::preferred_separator) {
          lastSlash = i + 1;
        }
      }
      path.erase(0, lastSlash);
      res.push_back(path);
    }
  }
  return res;
}

bool isDirectoryExists(const std::string& i_path) {
  try {
    std::filesystem::path pathObj(i_path);
    if (std::filesystem::exists(pathObj)
        && std::filesystem::is_directory(pathObj))
      return true;
  } catch (std::filesystem::filesystem_error& e) {
    std::cerr << e.what() << std::endl;
  }
  return false;
}

std::string getParentDirOf(const std::string& i_path) {
  std::filesystem::path p = i_path;
  return p.parent_path().string();
}

std::string loadStringFile(const std::filesystem::path& p) {
  std::string   str;
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  file.open(p, std::ios_base::binary);
  std::size_t sz = static_cast<std::size_t>(file_size(p));
  str.resize(sz, '\0');
  file.read(&str[0], sz);
  return str;
}
}  // namespace FilesTools
