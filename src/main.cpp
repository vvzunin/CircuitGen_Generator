#include "CircuitGenGenerator/CircuitGenGenerator.hpp"
#include "dummy.hpp"
#include <getopt.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std::chrono;

INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) {
  el::Configurations conf("./include/path/to/my-conf.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);
  LOG(INFO) << "Launch of generation.";
  std::string json_path;
  // Use getopt to parse command line arguments
  const char *const short_opts = "j:n:";
  const option long_opts[] = {{"json_path", required_argument, nullptr, 'j'},
                              {"num_nodes", required_argument, nullptr, 'n'}};
  int c;

  int opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) !=
         -1) {
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
  
  // json_path = "../../examples/json/sampleALU.json";
  // std::clog << std::filesystem::current_path() << std::endl;
  CircuitGenGenerator::runGenerationFromJson(json_path);
<<<<<<< HEAD

  return 0;
}
