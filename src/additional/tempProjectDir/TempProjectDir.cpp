#include "TempProjectDir.hpp"

namespace CG_Gen {

TempProjectDir::TempProjectDir(const std::filesystem::path &i_path,
                               const std::filesystem::path &i_baseDir) {

  if (i_baseDir.empty()) {
    throw std::runtime_error("Base directory is empty");
  }

  if (!i_baseDir.is_absolute()) {
    throw std::runtime_error("Wrong base directory");
  }
  d_baseDir = i_baseDir;

  try {
    if (i_path.is_relative()) {
      d_path = std::filesystem::absolute(i_path);
    } else {
      d_path = i_path;
    }
    d_path = d_path.lexically_normal();

    auto rel = std::filesystem::relative(d_path, d_baseDir);
    if (rel.string().find("..") != std::string::npos) {
      throw std::runtime_error("Path out of base directory");
    }

    if (std::filesystem::exists(d_path)) {
      if (std::filesystem::is_directory(d_path)) {
        throw std::runtime_error("Directory already exists: " +
                                 d_path.string());
      }
    }

    if (!std::filesystem::create_directories(d_path)) {
      throw std::runtime_error("Creation of directory failed");
    }
  } catch (std::exception &e) {
    std::cerr << "Error occurred during temporary directory creation: "
              << e.what() << std::endl;
    throw;
  }
}

TempProjectDir::~TempProjectDir() {
  try {
    if (!d_path.empty() && std::filesystem::exists(d_path)) {
      std::filesystem::remove_all(d_path);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error occurred during deliting the directory" << e.what()
              << std::endl;
  }
}

bool TempProjectDir::copyFile(const std::filesystem::path &i_source,
                              const std::filesystem::path &i_destination) {
  try {
    if (d_path.empty()) {
      throw std::runtime_error("Temporary directory was not initialized");
    }

    if (!std::filesystem::exists(i_source)) {
      std::cerr << "Source file does not exist" << std::endl;
      return false;
    }

    if (!std::filesystem::is_regular_file(i_source)) {
      std::cerr << "Source path is not a file" << std::endl;
      return false;
    }

    std::filesystem::path destinationPath;
    if (i_destination.is_absolute()) {
      if (i_destination.string().find(d_path.string()) != 0) {
        std::cerr << "Error in source/destination paths" << std::endl;
        return false;
      }
      destinationPath = i_destination;
    } else {
      destinationPath = d_path / i_destination;
    }

    std::filesystem::copy_file(
        i_source, destinationPath,
        std::filesystem::copy_options::overwrite_existing);

    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error occurred during file coping: " << e.what() << std::endl;
    return false;
  }
}

bool TempProjectDir::createFile(const std::string &i_filename,
                                const std::string i_content) {
  try {
    if (d_path.empty()) {
      throw std::runtime_error("Temporary directory was not initialized");
    }

    if (i_filename.empty()) {
      throw std::runtime_error("Name of the file is empty");
    }

    std::filesystem::path filePath = d_path / i_filename;

    std::ofstream file(filePath);
    if (!file.is_open()) {
      throw std::runtime_error("Unable to open file " + filePath.string());
    }

    file << i_content;
    file.close();

    if (!file.good()) {
      throw std::runtime_error("Error during file flashing" +
                               filePath.string());
    }

    return true;
  } catch (std::exception &e) {
    std::cerr << "Error during file creation " << e.what() << std::endl;
    return false;
  }
}

std::filesystem::path
TempProjectDir::createSubDirectory(const std::string &i_name) {
  try {
    if (d_path.empty()) {
      throw std::runtime_error("Temporary directory was not initialized");
    }

    if (i_name.empty() ||
        i_name.find_first_of("\\/:*?\"<>|") != std::string::npos) {
      throw std::runtime_error("Incorrect subdirectory name: " + i_name);
    }

    std::filesystem::path subdirPath = d_path / i_name;

    if (std::filesystem::exists(subdirPath)) {
      throw std::runtime_error("Subdirectory already exists: " +
                               subdirPath.string());
    }

    if (!std::filesystem::create_directories(subdirPath)) {
      throw std::runtime_error("Unable to create directory: " +
                               subdirPath.string());
    }

    return subdirPath;
  } catch (std::exception &e) {
    std::cerr << "Error during subdirectory creation: " << e.what()
              << std::endl;
    return "";
  }
}
} // namespace CG_Gen