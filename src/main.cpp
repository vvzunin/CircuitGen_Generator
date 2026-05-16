#include "CircuitGenGenerator/CircuitGenGenerator.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <easyloggingpp/easylogging++.h>
#include <filesystem>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <vector>
INITIALIZE_EASYLOGGINGPP

using namespace std::chrono;

void initLogging(std::string testName, std::string subtestName) {
  el::Configurations conf("easylogging++.conf");
  el::Loggers::reconfigureAllLoggers(conf);
  el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename,
                                     "logs/" + testName + "/" + subtestName +
                                         ".log");
  el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
  el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
}

int main(int argc, char **argv) {
  initLogging("main", "main");
  // LOG(INFO) << "Program started";

  std::string json_path;
  std::string chisel_path;
  std::string project_root = PROJECT_SOURCE_DIR;

  bool isChisel = false;

  // Use getopt to parse command line arguments

  const char *const short_opts = "j:n:c:";
  const option long_opts[] = {{"json_path", required_argument, nullptr, 'j'},
                              {"num_nodes", required_argument, nullptr, 'n'},
                              {"chisel_path", required_argument, nullptr, 'c'}};
  int32_t opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) !=
         -1) {
    switch (opt) {
      case 'j':
        json_path = optarg;
        break;
      case 'c':
        chisel_path = optarg;
        isChisel = true;
        break;
      case '?':
        // Unknown option or missing argument
        break;
      default:
        std::cerr << "Unknown error while parsing command line arguments."
                  << std::endl;
        return 1;
    }
  }
  // LOG(INFO) << "Starting generation ...";
  // json_path = "../../examples/json/sampleRandLevel.json";
  // std::clog << std::filesystem::current_path() << std::endl;

  std::cout << "generator Version: " << CircuitGenGenerator::getVersion()
            << std::endl;

  if (isChisel) {
    if (!CircuitGenGenerator::runChiselGeneration(chisel_path, project_root)) {
      return 1;
    }
  } else {
    CircuitGenGenerator::runGenerationFromJson(json_path);
  }

  return 0;
}