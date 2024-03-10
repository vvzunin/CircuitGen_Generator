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

// #include <api/generatorAPI.h>
#include <baseStructures/graph/OrientedGraph.h>

using namespace std::chrono;

int main(int argc, char **argv)
{

  OrientedGraph graph;
  graph.addInput("in1");
  graph.addInput("in2");
  graph.addInput("in3");

  for (const auto &[key, value] : graph.getBaseVertexes())
  {
    for (GraphVertexBase *vert : value)
      std::cout << vert->getName() << std::endl;
  }
  
  for (OrientedGraph *vert : graph.getSubGraphs())
      std::cout << vert->getName() << std::endl;

  // std::string json_path;
  // // std::string json_path = "../Generator/docs/sample.json";
  // // Use getopt to parse command line arguments

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

  // runGenerationFromJson(json_path);
}