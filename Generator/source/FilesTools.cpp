#include "FilesTools.h"

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

  bool isDirectoryExists(const std::string& i_path)
  {
    try
    {
      std::filesystem::path pathObj(i_path);
      if (std::filesystem::exists(pathObj) && std::filesystem::is_directory(pathObj))
        return true;
    }
    catch(std::filesystem::filesystem_error & e)
    {
      std::cerr << e.what() << std::endl;
    }
    return false;
  }

  std::string getParentDirOf(const std::string& i_path)
  {
    std::filesystem::path p = i_path;
    return p.parent_path().string();
  }

  std::string loadStringFile(const std::filesystem::path& p)
  {
    std::string str;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(p, std::ios_base::binary);
    std::size_t sz = static_cast<std::size_t>(file_size(p));
    str.resize(sz, '\0');
    file.read(&str[0], sz);
    return str;
  }
}
