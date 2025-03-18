#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include "Settings.hpp"

namespace CG_Gen {

std::shared_ptr<Settings> Settings::d_singleton = nullptr;

std::shared_ptr<Settings> Settings::getInstance(const std::string &i_value) {
  /**
   * This is a safer way to create an instance. instance = new Singleton is
   * dangeruous in case two instance threads wants to access at the same time
   */
  if (d_singleton == nullptr) {
    d_singleton = std::make_shared<Settings>(i_value);
  }
  return d_singleton;
}

std::string Settings::getInstanceName() const {
  return d_name;
}

uint16_t Settings::getNumThread() const {
  return d_numThreads;
}

void Settings::setNumThread(uint16_t i_numThreads) {
  d_numThreads = i_numThreads;
}

std::string Settings::getPathNadezhda() const {
  return d_pathToNadezhda;
}

std::string Settings::getNadezhdaVar(const std::string &key) const {
  return d_nadezhda.at(key);
}

std::string Settings::getDatasetPath() const {
  return d_datasetPath;
}

void Settings::setDatasetPath(const std::string &i_datasetPath) {
  d_datasetPath = i_datasetPath;
}

std::string Settings::getLibraryPath() const {
  return d_libraryPath;
}

std::string
Settings::getGenerationMethodPrefix(const GenerationTypes i_methodType) const {
  return generationTypeToPrefix.at(i_methodType);
}

std::string
Settings::getLibraryNameFromEnum(const LibrariesTypes &library) const {
  switch (library) {
    case SKY_LIB:
    default:
      return "sky130.lib";
  }
}

uint32_t Settings::getMaxInputs() const {
  return d_maxInputs;
}

uint32_t Settings::getMaxOutputs() const {
  return d_maxOutputs;
}

} // namespace CG_Gen
