#include <cassert>
#include <cstdlib>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>


#include "Reliability.h"
#include "../FilesTools.h"


namespace
{
  template<typename T1, typename T2>
  std::vector<T1> getKeysFromMap(const std::map<T1, T2>& m)
  {
    std::vector<T1> res;
    for (const auto &[key, value] : m)
      res.push_back(key);

    return res;
  }
}

Reliability::Reliability(const OrientedGraph& i_graph, double i_p) :
  d_graph(i_graph),
  d_p(i_p) {};

std::map<std::string, std::vector<bool>> Reliability::calc(
  bool i_withErrorValues,
  bool i_withErrorSetting
  // a flag that detects an error on one valve (i-om)
  int i_withOneValveError
)
{
  std::vector<std::string> errorValues;
  std::vector<std::string> setErrors;

  if (i_withErrorValues)
    errorValues = d_graph.getLogicVerticesToWireName();
  if (i_withErrorSetting)
    setErrors = d_graph.getLogicVerticesToWireName();

  std::vector<std::string> inputs = d_graph.getVerticesByTypeToWireName("input");
  std::vector<std::string> outputs = d_graph.getVerticesByTypeToWireName("output");

  std::map<std::string, std::vector<bool>> result;

  for (int i = 0; i < (1u << (inputs.size() + errorValues.size() + setErrors.size())); ++i)
  {
    std::map<std::string, bool> map;
    std::map<std::string, bool> mapErrors;
    std::map<std::string, bool> mapErrorsSet;
    int sn = i;

    assert(inputs.size() != 0);

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      map[inputs[j]] = sn % 2;
      sn /= 2;
    }

    sn = i;

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      mapErrors[errorValues[j]] = sn % 2;
      sn /= 2;
    }

    sn = i;

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      mapErrorsSet[errorValues[j]] = sn % 2;
      sn /= 2;
    }

    std::map<std::string, bool> res = d_graph.calcGraph(map, i_withErrorValues, mapErrors,i_withErrorSetting, mapErrorsSet);

    for (const auto &[key, value] : res)
      result[key].push_back(value);
  }

  return result;
}

double Reliability::calcReliabilityBase()
{
  double reliability = 0;

  int inputs = d_graph.getVerticesByType("inputs").size(); //TODO: rewrite naming
  int M = d_graph.getLogicVerticesToWireName().size();

  std::map<std::string, std::vector<bool>> dict = calc(false, false);

  std::map<std::string, std::vector<bool>> dictFull;

  for (const auto &[key, value] : dict)
  {
    dictFull[key] = {};
    for (int i = 0; i < (1u << M); ++i)
      for (int j = 0; j < value.size(); ++j)
        dictFull[key].push_back(dict[key][j]);
  }

  std::map<std::string, std::vector<bool>> dictError = calc(false, true);

  std::vector<std::string> outputs = getKeysFromMap<std::string>(dict);

  for (int j = 0; j < (1u << M); ++j)
  {
    int err = 0;

    for (int i = 0; i < (1u << inputs); ++i)
    {
      std::vector<bool> f;
      std::vector<bool> ferr;
      for (const auto& s : outputs)
      {
        f.push_back(dict[s][i]);
        ferr.push_back(dictError[s][dict[s].size() * j + i]);
      }

      if (f != ferr)
        ++err;

      // TODO: does we really need std::cout << std::endl;?
    }
    int t = j;
    int notNull = 0;

    while(t > 0)
    {
      notNull += t % 2;
      t /= 2;
    }

    reliability += err * pow(d_p, notNull) * pow(1 - d_p, M - notNull);
  }

  return reliability / static_cast<double>(1u << inputs);
}

std::map<std::string, double> Reliability::runNadezhda(
  const std::string& i_path,
  const std::string i_circuitName
)
{
  /* This part of the code will work if someone manages to install the program Nadezhda which is not work on Ubuntu and MAC.
  std::map<std::string, double> dict;
  dict["reliability_metric"] = 0;
  dict["area"] = 0;
  dict["size"] = 0;
  dict["longest_path"] = 0;
  dict["gates"] = 0;
  dict["sensitivity_factor"] = 0;
  dict["sensitivity_factor_percent"] = 0;
  dict["sensitive_area"] = 0;
  dict["sensitive_area_percent"] = 0;

  std::string curPath = std::filesystem::current_path().string();
  
  std::string cdCommand = "cd " + d_settings->getPathNadezhda();
  std::string runNadezdhaCommand = d_settings->getNadezhdaVar("python") + " " +
    d_settings->getNadezhdaVar("resynthesis") + " " + i_path + "/" + i_circuitName +
    ".v " + d_settings->getNadezhdaVar("liberty") + " " + i_path + "/res -y";
  
  std::string cpAndNadezdha = cdCommand + " && " + runNadezdhaCommand;

  std::system(cpAndNadezdha.c_str());

  std::string cpCommand1 = "cp " + i_path + "/res/" + i_circuitName + "r.v " + i_path + "/"
    + i_circuitName + "_Nangate.v";
  std::string cpCommand2 = "cp " + i_path + "/res/" + i_circuitName + "_report.json" + i_path + "/report.json";
  std::string rmCommand = "rm -rf " + i_path + "/res";

  std::system(cpCommand1.c_str());
  std::system(cpCommand2.c_str());
  std::system(rmCommand.c_str()); 
  //std::cout << cpCommand1 << std::endl;
  //std::cout << cpCommand2 << std::endl;
  //std::cout << rmCommand << std::endl;

  std::string nadezdhaReliabilityCommand = 
    d_settings->getNadezhdaVar("python") + " " + "./Nadezhda/" +
    d_settings->getNadezhdaVar("reliability") + " " +
    i_path + "/" + i_circuitName + "_Nangate.v " +
    d_settings->getNadezhdaVar("liberty") + " " +
    i_path + "/report.txt\n";

  //std::cout << nadezdhaReliabilityCommand;


  //TODO: wait for exit or proof of work
  std::system(nadezdhaReliabilityCommand.c_str());

  std::string reportPath = i_path + "/report.json";

  if (std::filesystem::exists(reportPath))
  {
    //std::string s = FilesTools::loadStringFile(reportPath);
    //TODO: make to json var
    std::ifstream jsonFile(reportPath);
    nlohmann::json obj = nlohmann::json::parse(jsonFile);

    for (auto it = obj.begin(); it != obj.end(); ++it)
    {
      if (it.key() == "before")
      {
        for (auto nit = it.value().begin(); nit != it.value().end(); ++nit)
        {
          if (nit.key() == "reliability_metric")
            dict[nit.key()] = static_cast<double>(nit.value());
          if (nit.key() == "area")
            dict[nit.key()] = static_cast<double>(nit.value());
          if (nit.key() == "size")
            dict[nit.key()] = static_cast<double>(nit.value());
          if (nit.key() == "longest_path")
            dict[nit.key()] = static_cast<double>(nit.value());
        }
      }
    }
    std::filesystem::remove(reportPath);
  }
    
  //TODO: why double check?

  //if (std::filesystem::exists(reportPath))
  return dict;
  */
  return {};
}

double Reliability::valveRating()
{
    // input and output vectors in the circuit
    std::vector<std::string> inputs = d_graph.getVerticesByTypeToWireName("input");
    std::vector<std::string> outputs = d_graph.getVerticesByTypeToWireName("output");
    // keeps a list of valves
    std::vector<std::string> vect_valves = d_graph.getLogicVerticesToWireName();
    // Table of reference values
    std::map<std::string, std::vector<bool>> error_start = this->calc(); // X
    // truth table construction
    // vector that stores the value of each o_i
    std::vector<double> arr_oi;
    // number of inputs in the schematic - Check
    int count_inputs = inputs.size();
    for (size_t i = 0; i < d_graph.getLogicVerticesToWireName().size(); i++)
    {
        std::map<std::string, std::vector<bool>> error_i_valve = this->calc(false, false, i);
        // sum of errors is passed to vector o_i - stores things. number
        arr_oi.push_back(sumErrorBetweenReferenceAndOther(error_start, error_i_valve));
        arr_oi[i] /= pow(2, count_inputs);
    }
    // Found o_i

    // Find the error range

    // holds the total probability
    double average_value = 0;
    // Ask if the cycle runs on all valves
    for (size_t i = 0; i < d_graph.getLogicVerticesToWireName().size(); i++)
    {
        double tmp = 0;
        tmp = arr_oi[i] * d_p * pow(1 - d_p, count_inputs - 1) + (0.5 * (1 - (pow(1 - d_p, count_inputs)) - count_inputs * d_p * pow(1 - d_p, count_inputs - 1)));
        average_value += tmp;
    }

    return average_value;

}

// function that returns the sum of errors on (compares between the reference and any second)
int Reliability::sumErrorBetweenReferenceAndOther(std::map<std::string, std::vector<bool>> i_errorStart, std::map<std::string, std::vector<bool>> i_otherTable)
{
    // TODO:
    // Make a key check between i_errorStart and i_otherTable, if it does not match - print -1;

    int err = 0;


    // size
    int size_maybe_err = i_errorStart[i_errorStart.begin()->first].size();

    for (int i = 0; i < size_maybe_err; ++i)
    {
        std::vector<bool> f;
        std::vector<bool> ferr;
        for (const auto& [key,value] : i_errorStart)
        {
            f.push_back(dict[s][i]);
            ferr.push_back(dictError[s][dict[s].size() * j + i]);
        }

        if (f != ferr)
            ++err;
    }
