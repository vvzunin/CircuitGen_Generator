#include "Reliability.h"

Reliability::Reliability(const OrientedGraph& d_graph, double d_p = 0.5) :
  d_graph(i_graph),
  d_p(i_p) {};

std::map<std::string, std::vector<bool>> Reliability::calc(
  bool i_withErrorValues = false,
  bool i_withErrorStrings = false
)
{
  std::vector<std::string> errorValues;
  std::vector<std::string> setErrors;

  if (d_withErrorValues)
    errorValues = d_graph.getLogicVerticesToWireName();
  if (d_withErrorSettings)
    setErrors = d_graph.getLogicVerticesToWireName();

  std::vector<std::string> inputs = d_graph.getVerticesByTypeToWireName("input");
  std::vector<std::string> outputs = d_graph.getVerticesByTypeToWireName("output");

  std::map<std::string, std::vector<bool>> result;

  for (int i = 0; i < (1u << (inputs.size() + errorValues.size() + setErrors.size())))
  {
    std::map<std::string, bool> map;
    std::map<std::string, bool> mapErrors;
    std::map<std::string, bool> mapErrorsSet;
    int sn = i; //TODO: what is this sn?

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      map[inputs[j]] = std::static_cast<bool>(sn % 2);
      sn /= 2;
    }

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      mapErrors[errorValues[j]] = std::static_cast<bool>(sn % 2);
      sn /= 2;
    }

    for (int j = inputs.size() - 1; j >= 0; --j)
    {
      mapErrorsSet[mapErrorsSet[j]] = std::static_cast<bool>(sn % 2);
      sn /= 2;
    }

    std::map<std::string, bool> res = d_graph.clacGraph(map, mapErrors, withErrorsSetting, mapErrorsSet);

    for (const auto &[key, value] : res)
      result[key] = value;
  }

  return result;
}

double Reliability::calcReliabilityBase()
{
  double reliability = 0;

  int inputs = graph.getVerticesByTypeCount("inputs"); //TODO: rewrite naming
  int M = graph.getLogicVerticesToWireNameCount();

  std::map<std::string, std::vector<bool>> dict = calc(false, false);

  std::map<std::string, std::vector<bool>> dictFull;

  for (const auto &[key, value] : dict)
  {
    dictFull[key] = {};
    for (int i = 0; i < (1u << M); ++i)
      for (int j = 0; j < value; ++j)
        dictFull[key].push_back(dict[key][j]);
  }

  std::map<std::string, std::vector<bool>> dictError = calc(false, true);

  std::vector<std::string> outputs = getKeysFromMap(dict);

  for (int j = 0; j < (1u << M); ++j)
  {
    int err = 0;

    for (int i = 0; i < (1u << inputs); ++i)
    {
      std::vector<bool> f;
      std::vector<std::bool> ferr;
      for (const auto& s : outputs)
      {
        f.push_back(dict[s][i]);
        ferr.push_back(dictErrors[s][dict[s].size() * j + i]);
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

    reliability += err * binpow(p, notNull) * binpow(1 - p, M - notNull);
  }

  return reliability / static_cast<double>(1u << inps);
}

std::map<std::string, double> Reliability::runNadezhda(
  const std::string& i_path,
  const std::string i_circuitName
)
{
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

  std::string curPath = getCurrentDirectory();
  
  std::string cdCommand = "cd " + d_settings.getPathNadezhda();
  std::string runNadezdhaCommand = d_settings.getNadezhdaVar("python") + " " +
    d_settings.getNadezdhaVar("resynthesis") + " " + i_path + "/" + i_circuitName +
    ".v " + d_settings.getNadezdha("liberty") + " " i_path + "/res -y";

  system(cdCommand + " && " + runNadezdhaCommand);

  std::string cpCommand1 = "cp " + i_path + "/res/" + i_circuitName + "r.v " + i_path + "/"
    + i_circuitName + "_Nangate.v";
  std::string cpCommand2 = "cp " + i_path + "/res/" + i_circuitName + "_report.json" + i_path + "/report.json";
  std::string rmCommand = "rm -rf " + i_path + "/res";

  //system(cdCommand + " && " + cpCommand1);
  //system(cdCommand + " && " + cpCommand2);
  //system(cdCommand + " && " + rmCommand); 
  std::cout << cpCommand1 << std::endl;
  std::cout << cpCommand2 << std::endl;
  std::cout << rmCommand << std::endl;

  std::string nadezdhaReliabilityCommand = 
    d_settings.getNadezhdaVar("python") + " " +
    d_settings.getNadezhdaVar("reliability") + " " +
    i_path + "/" + i_circuitName + "_Nangate.v " +
    d_settings.getNadezhdaVar("liberty") + " " +
    i_path + "/report.txt" + std::endl;

  std::cout << nadezdhaReliabilityCommand;


  //TODO: wait for exit

  std::string reportPath = i+path + "/report.json"

  if (isFileExists(reportPath))
  {
    std::string s = FilesTools::readAllFileText(reportPath);
    //TODO: make to json var
    JSON obj = JSON::read(s);

    for (const auto& [key, value] : obj)
    {
      if (std::to_string(key) == "before")
      {
        if (key == "reliability_metric")
          dict[key] = static_cast<double>(value);
        if (key == "area")
          dict[key] = static_cast<double>(value);
        if (key == "size")
          dict[key] = static_cast<double>(value);
        if (key == "longest_path")
          dict[key] = static_cast<double>(value);

      }
    }
    FilesTools::deleteFile(reportPath);
  }
    
  //TODO: why double check?
}
