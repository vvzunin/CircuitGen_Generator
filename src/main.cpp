#include <api/generatorAPI.h>
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

int main(int argc, char **argv) {
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

  // json_path = "../../doc/sampleAll.json";
  runGenerationFromJson(json_path);
}