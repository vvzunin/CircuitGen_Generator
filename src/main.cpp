#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <easyloggingpp/easylogging++.h>
#include <getopt.h>
#include <unistd.h>

#include "CircuitGenGenerator/CircuitGenGenerator.hpp"
INITIALIZE_EASYLOGGINGPP

using namespace std::chrono;

void initLogging(std::string testName, std::string subtestName) {
  el::Configurations conf("easylogging++.conf");
  el::Loggers::reconfigureAllLoggers(conf);
  el::Loggers::reconfigureAllLoggers(
      el::ConfigurationType::Filename,
      "logs/" + testName + "/" + subtestName + ".log"
  );
  el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
  el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
}

int main(int argc, char** argv) {
  initLogging("main", "main");
  // LOG(INFO) << "Program started";

  std::string       json_path;
  // Use getopt to parse command line arguments

  const char* const short_opts  = "j:n:";
  const option      long_opts[] = {
      {"json_path", required_argument, nullptr, 'j'},
      {"num_nodes", required_argument, nullptr, 'n'}};
  int32_t opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1
  ) {
    switch (opt) {
      case 'j':
        json_path = optarg;
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
  CircuitGenGenerator::runGenerationFromJson(json_path);

  return 0;
}