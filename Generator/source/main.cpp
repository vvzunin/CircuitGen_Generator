#include <map>
#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include <unistd.h>
#include <getopt.h>


#include <generatorAPI.h>

using namespace std::chrono;

int main(int argc, char **argv)
{
    // std::string json_path;
    // std::string json_path = "../Generator/docs/sampleAll.json";
    std::string json_path = "../jsons_for_generator/data_3.json";
    // Use getopt to parse command line arguments

    // const char *const short_opts = "j:n:";
    // const option long_opts[] = {
    //     {"json_path", required_argument, nullptr, 'j'},
    //     {"num_nodes", required_argument, nullptr, 'n'}};
    // int c;

    // int opt;
    // while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1)
    // {
    //     switch (opt)
    //     {
    //     case 'j':
    //         json_path = optarg;
    //         break;
    //     case '?':
    //         // Unknown option or missing argument
    //         break;
    //     default:
    //         std::cerr << "Unknown error while parsing command line arguments." << std::endl;
    //         return 1;
    //     }
    // }

    runGenerationFromJson(json_path);
}