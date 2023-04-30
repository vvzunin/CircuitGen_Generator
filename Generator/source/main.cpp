#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include <nlohmann/json.hpp>

#include <unistd.h>
#include <getopt.h>

#include "./DataBase/DataBaseGenerator.h"
#include "./DataBase/DataBaseGeneratorParameters.h"

int main(int argc, char** argv)
{

  std::cout << std::filesystem::current_path() << std::endl;

  int num_nodes = 0;
  std::string json_path;

    // Use getopt to parse command line arguments

  const char* const short_opts = "j:n:";
  const option long_opts[] = {
    {"json_path", required_argument, nullptr, 'j'},
    {"num_nodes", required_argument, nullptr, 'n'}
  };
  int c;

  int opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
    switch (opt) {
      case 'j':
        json_path = optarg;
        break;
      case 'n':
        num_nodes = std::stoi(optarg);
        break;
      case '?':
        // Unknown option or missing argument
        break;
      default:
        std::cerr << "Unknown error while parsing command line arguments." << std::endl;
        return 1;
    }
  }
  std::cout << "JSON path: " << json_path << std::endl;
  std::cout << "Num nodes: " << num_nodes << std::endl;

  std::cout << std::filesystem::current_path() << std::endl;

  if (std::filesystem::exists(json_path))
  {
    std::cout << "All ok, file finded" << std::endl;
  } else 
  {
    std::cout << "Where is the file???" << std::endl;
  }

  std::ifstream f(json_path);
  nlohmann::json data = nlohmann::json::parse(f);
  data = *(data.begin() + 1);
  std::cout << "red json" << std::endl;
  
  std::cout << data.dump(4);
  
  std:: cout << data["min_in"] << std::endl;
  


  GenerationTypes gt;
  if (data["type_of_generation"] == "From Random Truth Table")
  {
    gt = GenerationTypes::FromRandomTruthTable;
  }
  std::string request_id = data["request_id"];
  assert(request_id != "");
  int minInputs = data["min_in"];
  int maxInputs = data["max_in"];
  int minOutputs = data["min_out"];
  int maxOutputs = data["max_out"];
  int repeats = data["repeat_n"];
  int maxLevel = data["max_level"];
  int maxElement = data["max_elem"];
  bool limit = data["limit_generation"];
  bool CNFF = data["CNFF"];
  bool CNFT = data["CNFT"];
  bool LeaveEmptyOut = data["leave_empty_out"];
  int numOfSurv =  data["surv_num"];
  std::string mutType = data["mut_type"];
  int mutChance = data["mut_chance"];
  int swapType = data["swap_type"];
  double ratioInTable = data["ratio_in_table"];
  int recNum = data["rec_num"];
  int refPoints = data["ref_points"];
  int tourSize = data["tour_size"];
  std::string selectionTypeParent = data["selection_type_parent"];
  int inputs = minInputs;
  int outputs = minOutputs;
  std::map<std::string, int> m;
  std::vector<std::string> v = {"num_and", "num_nand", "num_or", "num_not", "num_nor", "num_buf", "num_xor", "num_xnor"}; 
  for(auto& el : data.items())
  {
	  if(std::find(v.begin(), v.end(), el.key()) != v.end()) m.insert({el.key(), el.value()});
  }
    
  if (gt == GenerationTypes::FromRandomTruthTable)
  {
    //inputs = (random() % (maxInputs - minInputs)) + minInputs;
    //outputs = (random() % (maxOutputs - minOutputs)) + minOutputs;
  }

  //JSON params = JSON::Read("params.json");

  //TODO:: make function that return DataBaseGeneratorParameters from json

  GenerationParameters gp("My_first_test", request_id, inputs, outputs, repeats, maxLevel, maxElement);
  gp.setCNFF(CNFF);
  gp.setCNFT(CNFT);
  gp.setLimit(limit);
  gp.setNumOperationParameters(m, LeaveEmptyOut);
//  gp.setGeneticParameters(numOfSurv, mutType, mutChance, swapType, ratioInTable, recNum, refPoints, tourSize,  selectionTypeParent);
  DataBaseGeneratorParameters dbgp(minInputs, maxInputs, minOutputs, maxOutputs, repeats, gt, gp);

  DataBaseGenerator generator(dbgp);


  generator.generateType(dbgp, false);

  
}
