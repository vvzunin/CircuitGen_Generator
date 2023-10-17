#include <cstdio>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "Circuit.h"
#include "../reliability/Reliability.h"
#include "../FilesTools.h"

Circuit::Circuit(const OrientedGraph& i_graph, const std::vector<std::string>& i_logExpressions)
{
  d_graph = i_graph;
  d_graph.updateLevels();
  d_logExpressions = i_logExpressions;
}

void Circuit::computeHash()
{
  std::stringstream stream;
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numInputs << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numOutputs << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_maxLevel << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numEdges << '\n';
  stream << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(10) << d_circuitParameters.d_reliability << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_size << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_area << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_gates << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_sensitiveArea << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_sensitiveAreaPercent << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_sensitivityFactor << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_reliabilityPercent << '\n';

  for (const auto &[key, value] : d_circuitParameters.d_numElementsOfEachType)
    stream << "\t\t\"" << key << "\": " << value << '\n';

  for (const auto &[key, value] : d_circuitParameters.d_numEdgesOfEachType)
    stream << "\t\t\"" << key.first << "-" << key.second << "\": " << value << '\n';

  {
     //TODO: write logic of get SHA256
  }

}



void Circuit::updateCircuitsParameters()
{
  if (d_graph.size() == 0)
    return;

  d_graph.updateLevels();

  d_circuitParameters.d_name = d_circuitName;

  std::vector<std::string> inputs = d_graph.getVerticesByType("input");
  std::vector<std::string> outputs = d_graph.getVerticesByType("output");

  d_circuitParameters.d_numInputs = 0;
  for (int i = 0; i < inputs.size(); ++i)
    if (inputs[i].find("'b") == std::string::npos)
      d_circuitParameters.d_numInputs++;

  d_circuitParameters.d_numOutputs = outputs.size();

  d_circuitParameters.d_maxLevel = d_graph.getMaxLevel();

  d_circuitParameters.d_numEdges = 0;
  for (const auto& row : d_graph.getAdjacencyMatrix())
    for (const auto& el : row)
      if (el)
        d_circuitParameters.d_numEdges++;
        
  Reliability R(d_graph, 0.5);
  std::map<std::string, double> dict = R.runNadezhda(d_path, d_circuitName); // what? d_path
  

  //std::cout << R.calcReliabilityBase() << std::endl;
  //std::cout << R.valveRating() << std::endl;


// Algorithm for evaluating circuit reliability
  std::vector<std::vector<bool>> vec = {}; 
  std::vector<bool> first = {};
  for (int i = 0; i < inputs.size(); i++)
  {
      first.push_back(false);
  }
  vec.push_back(first);
  for (int i = 0; i < pow(2.0, float(inputs.size())); i++)
  {
      std::vector<bool> next = {};
      for (int j = 0; j < inputs.size(); j++) next.push_back(vec.back()[j]);
      for (int m = inputs.size() - 1; m >= 0; m--)
      {
          if (next[m] == false)
          {
              next[m] = true;
              break;
          }
          else
          {
              next[m] = false;
          }
      }
      vec.push_back(next);
  }
  /*
  for (int i = 0; i < pow(2.0, float(inputs.size())); i++)
  {
      for (int j = 0; j < inputs.size(); j++)
      {
          if (vec[i][j] == false) std::cout << 0 << "  ";
          else std::cout << 1 << "  ";
      }
      std::cout << "\n";

  }*/

  int numberOfIncoincidences = 0;
  int pos = -1;
  std::vector<int> vec_index = d_graph.getVertices("input");
  for (int i = 0; i < pow(2.0, float(inputs.size())); i++)
  {
      std::vector<bool> tmp = vec.back();
      std::vector<bool> tmp_wrong = vec.back();
      if (pos != -1) d_graph.d_vertices[pos].wrongVertex = false;
      vec.pop_back();
      for (int j = 0; j < vec_index.size(); j++)
      {
          d_graph.d_vertices[vec_index[j]].setValue(tmp.back());
          tmp.pop_back();
      }
      
    //  std::vector<bool> res_1 = {};
      for (int m = 1; m < d_graph.getMaxLevel(); m++)
      {
          std::vector<int> vec_2 = d_graph.getVerticesByLevel_2(m);
          for (int n = 0; n < vec_2.size(); n++)
          {
              std::vector<bool> vec_3 = {};
              std::vector<int> tmp_2 = d_graph.d_listOfEdgesToFrom[vec_2[n]];
              for (int j = 0; j < tmp_2.size(); j++)
              {
                  vec_3.push_back(d_graph.d_vertices[tmp_2[j]].getValue());
              }
              d_graph.d_vertices[vec_2[n]].setValue(d_graph.calc(vec_3, (d_graph.d_vertices[vec_2[n]]).getOperation()));
          //    res_1.push_back(d_graph.d_vertices[vec_2[n]].getValue());
          }
      }

      std::vector<int> vec_outputs_indices_without_error = d_graph.getVertices("output");
      for (int j = 0; j < vec_outputs_indices_without_error.size(); j++)
      {
          d_graph.d_vertices[vec_outputs_indices_without_error[j]].setValue(d_graph.d_vertices[(d_graph.d_listOfEdgesToFrom[vec_outputs_indices_without_error[j]])[0]].getValue());
      }
      std::vector<bool> result_without_error = {};
     

      for (int j = 0; j < vec_outputs_indices_without_error.size(); j++)
      {
          result_without_error.push_back(d_graph.d_vertices[vec_outputs_indices_without_error[j]].getValue());
      }
      
      pos = -1;


          /* Working version
      for (int j = 0; j < d_graph.d_vertices.size(); j++)
      {
          if (d_graph.d_vertices[j].getOperation() != "input" && d_graph.d_vertices[j].getOperation() != "const" && d_graph.d_vertices[j].getOperation() != "output")
          {
              d_graph.d_vertices[j].wrongVertex = true;
              pos = j;
              break;
          }
      }*/

      std::vector<int> indecies__ = {};
      for (int j = 0; j < d_graph.d_vertices.size(); j++)
      {
          if (d_graph.d_vertices[j].getOperation() != "input" && d_graph.d_vertices[j].getOperation() != "output" && d_graph.d_vertices[j].getOperation() != "const")
          {
              indecies__.push_back(j);
          }
      }

      // Choose random wrong vertex.
      srand((unsigned)time(NULL));
      int t = (rand()%indecies__.size());
      d_graph.d_vertices[indecies__[t]].wrongVertex = true;
      pos = indecies__[t];

      








      for (int j = 0; j < vec_index.size(); j++)
      {
          d_graph.d_vertices[vec_index[j]].setValue(tmp.back());
          tmp.pop_back();
      }

      //  std::vector<bool> res_1 = {};
      for (int m = 1; m < d_graph.getMaxLevel(); m++)
      {
          std::vector<int> vec_2 = d_graph.getVerticesByLevel_2(m);
          for (int n = 0; n < vec_2.size(); n++)
          {
              std::vector<bool> vec_3 = {};
              std::vector<int> tmp_2 = d_graph.d_listOfEdgesToFrom[vec_2[n]];
              for (int j = 0; j < tmp_2.size(); j++)
              {
                  vec_3.push_back(d_graph.d_vertices[tmp_2[j]].getValue());
              }
              d_graph.d_vertices[vec_2[n]].setValue(d_graph.calc(vec_3, (d_graph.d_vertices[vec_2[n]]).getOperation()));
              //    res_1.push_back(d_graph.d_vertices[vec_2[n]].getValue());
          }
      }


      std::vector<int> vec_outputs_indices_with_error = d_graph.getVertices("output");
      for (int j = 0; j < vec_outputs_indices_with_error.size(); j++)
      {
          d_graph.d_vertices[vec_outputs_indices_with_error[j]].setValue(d_graph.d_vertices[(d_graph.d_listOfEdgesToFrom[vec_outputs_indices_with_error[j]])[0]].getValue());
      }
      std::vector<bool> result_with_error = {};
      
      for (int j = 0; j < vec_outputs_indices_with_error.size(); j++)
      {
          result_with_error.push_back(d_graph.d_vertices[vec_outputs_indices_with_error[j]].getValue());
      }

     /*
      for (int j = 0; j < result_with_error.size(); j++)
      {
          std::cout << "with_error: " << result_with_error[j] << "\twithout_error: " << result_without_error[j] << "\n";
      }
      std::cout << "next: " << "\n";
      if (result_with_error != result_without_error) numberOfIncoincidences++;
      */
      /*
      for (int j = 0; j < vec_outputs_indices.size(); j++)
      {
          std::cout << "iteration number: " << i << d_graph.d_listOfEdgesToFrom[vec_outputs_indices[j]].size() << "\t value: " << d_graph.d_vertices[(d_graph.d_listOfEdgesToFrom[vec_outputs_indices[j]])[0]].getValue() << "\n";
      }
      std::cout << "\n\n";
      */

  }


d_circuitParameters.d_reliability = 1 - numberOfIncoincidences / pow(2.0, float(inputs.size()));
  





  d_circuitParameters.d_size = dict["size"];
  d_circuitParameters.d_area = dict["area"];
  d_circuitParameters.d_longestPath = dict["longestPath"];

  d_circuitParameters.d_gates = dict["gates"];
  d_circuitParameters.d_sensitivityFactor = dict["sensitive_factor"];
  d_circuitParameters.d_reliabilityPercent = dict["sensitivity_factor_percent"];
  d_circuitParameters.d_sensitiveArea = dict["sencitive_area"];
  d_circuitParameters.d_sensitiveAreaPercent = dict["sensitive_area_persent"];

  d_circuitParameters.d_numElementsOfEachType.clear();
  std::vector<GraphVertex> gv = d_graph.getVertices();

  for (const auto &[key, value] : d_settings->getLogicOperations())
    d_circuitParameters.d_numElementsOfEachType[key] = 0;

  for (const auto v : gv)
    for (const auto &[key, value] : d_settings->getLogicOperations())
      if (v.getOperation() == key)
        d_circuitParameters.d_numElementsOfEachType[v.getOperation()]++;
  
  d_circuitParameters.d_numEdgesOfEachType.clear();
  for (const auto &[key1, value1] : d_settings->getLogicOperations())
    for (const auto &[key2, vluae2] : d_settings->getLogicOperations())
      if (key1 != "output" && key2 != "input")
        d_circuitParameters.d_numEdgesOfEachType[std::make_pair(key1, key2)] = 0;

  for (int i = 0; i < gv.size(); ++i)
    for (int j = 0; j < gv.size(); ++j)
      if (d_graph.getAdjacencyMatrix(i, j))
        d_circuitParameters.d_numEdgesOfEachType[std::make_pair(gv[i].getOperation(), gv[j].getOperation())]++;

  computeHash();
}

bool Circuit::graphToVerilog(const std::string& i_path, bool i_pathExists)
{
  if (d_graph.empty())
    return false;

  d_graph.numberVerticesCorrectly();

 /* if (!i_pathExists) // TODO: work with directory
    if (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() + i_path))
      std::filesystem::create_directory(i_path);
  */    

  static std::string filename;
  static std::string s;

  int previousSizeOfFileName = filename.size();

  filename = d_path + "/" + d_circuitName + ".v";

  std::vector<std::string> inputs = d_graph.getVerticesByType("input");
  std::vector<std::string> outputs = d_graph.getVerticesByType("output");
  std::vector<std::string> consts = d_graph.getVerticesByType("const");
  
  int pos = (s.find_last_of('/')) + 1;
  int pos2 = (filename.find_last_of('/')) + 1;
  
  if (previousSizeOfFileName == 0) 
      s = std::filesystem::current_path().string() + "/" + filename;// static variable will be created one time and then will be used throught running of the program
  else 
      s.replace(pos, previousSizeOfFileName, filename, pos2, previousSizeOfFileName);

  bool f = std::filesystem::exists(s);

  std::ofstream w(filename);
  for (const auto& expr : d_logExpressions)
    w << "//" << expr << '\n';

  w << "module " << d_circuitName << "(\n";

  std::string in = "";

  const std::string inputModule = "\tinput";

  in += inputModule;
  for (const auto& in_i : inputs)
    if (in_i.find("x") != std::string::npos)
      in += " " + in_i + ",";

  if (in.length() > inputModule.length())
    w << in << '\n';

  w << "\toutput";
  bool first = true;
  for (const auto& out : outputs)
  {
    if (first)
    {
      w << " ";
      first = false;
    }
    else
    {
      w << ", ";
    }
    w << out;
  }
  w << "\n);\n";

  if (d_graph.size() - inputs.size() - outputs.size() - consts.size() > 0)
  {
    w << "\n\twire";
    bool first = true;
    for (const auto& vert : d_graph.getVertices())
    {
      if (vert.getOperation() != "input" && vert.getOperation() != "output" && vert.getOperation() != "const")
      {
        if (first)
        {
          w << " " << vert.getWireName();
          first = false;
        }
        else 
        {
          w << ", " << vert.getWireName();
        }
      }
    }
    w << ";\n" << std::endl;
  }

  for (int j = 0; j < d_graph.size(); ++j)
  {
    if (d_graph.getVertice(j).getOperation() != "input")
    {
      std::vector<int> inps;
      for (int i = 0; i < d_graph.size(); ++i)
        if (d_graph.getAdjacencyMatrix(i, j))
          inps.push_back(i);

      if (d_graph.getVertice(j).getOperation() != "output")
      {
        if (d_graph.getVertice(j).getOperation() != "const")
        {
          w << "\t" << d_graph.getVertice(j).getOperation() << " (" <<
            d_graph.getVertice(j).getWireName();
          // TODO: on prev line add instance name
          for (auto k : inps)
            w << ", " << d_graph.getVertice(k).getWireName();
          w << ");" << std::endl;
        }
      }
      else
      {
        if (inps.size() > 0)
        {
          w << "\tassign " << d_graph.getVertice(j).getWireName() << " = " <<
            d_graph.getVertice(inps[0]).getWireName() << ";" << std::endl;
        }
      }
    }
  }
  
  w << "endmodule" << std::endl;

  return true;
}

bool Circuit::saveParameters(bool i_pathExists) const
{
  if (true)
  {/*
    if (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() + d_path)) // TODO: make function isDirectory exists
    {
      //std::filesystem::create_directory(d_path);
    }
  */
  }

  std::string filename = d_path + "/" + d_circuitName + ".json";

  //if (std::filesystem::exists(filename))
  //  std::remove(filename.c_str());

  std::ofstream w(filename);

  w << "{" << std::endl;

  w << "\t\"name\": \"" << d_circuitParameters.d_name << "\"," << std::endl;
  w << "\t\"numInputs\": \"" << d_circuitParameters.d_numInputs << "\"," << std::endl;
  w << "\t\"numOutputs\": \"" << d_circuitParameters.d_numOutputs << "\"," << std::endl;
  w << "\t\"maxLevel\": \"" << d_circuitParameters.d_maxLevel << "\"," << std::endl;
  w << "\t\"numEdges\": \"" << d_circuitParameters.d_numEdges << "\"," << std::endl;
  //w << "\t\"\": \"" << d_circuitParameters. << "\"," << std::endl; TODO: what is this mean?
  w << "\t\"reliability\": \"" << std::fixed << std::setprecision(20) << d_circuitParameters.d_reliability << "\"," << std::endl;
  w << "\t\"size\": \"" << d_circuitParameters.d_size << "\"," << std::endl;
  w << "\t\"area\": \"" << d_circuitParameters.d_area << "\"," << std::endl;
  w << "\t\"longest_path\": \"" << d_circuitParameters.d_longestPath << "\"," << std::endl;
  w << "\t\"gates\": \"" << d_circuitParameters.d_gates << "\"," << std::endl;
  w << "\t\"sensitivity_factor\": \"" << d_circuitParameters.d_sensitivityFactor << "\"," << std::endl;
  w << "\t\"sinsitivity_factor_percent\": \"" << d_circuitParameters.d_reliabilityPercent << "\"," << std::endl;
  w << "\t\"sensitive_area\": \"" << d_circuitParameters.d_sensitiveArea << "\"," << std::endl;
  w << "\t\"sensitive_area_percent\": \"" << d_circuitParameters.d_sensitiveAreaPercent << "\"," << std::endl;
  //w << "\t\"\": \"" << d_circuitParameters << "\"," << std::endl; // TODO: what is this mean?
  w << "\t\"hash_code\": \"" << d_circuitParameters.d_hashCode << "\"," << std::endl;

  w << "\t\"numElementsOfEachType\": {" << std::endl;

  bool first = true;
  for (const auto &[key, value] : d_circuitParameters.d_numElementsOfEachType)
  {
    if (value != 0)
    {
      if (first)
      {
        first = false;
        w << "\t\t\"" << key << "\": " << value;
      } else 
      {
        w << "," << std::endl << "\t\t\"" << key << "\": " << value;
      }
    }
  }
  w << std::endl;

  w << "\t}," << std::endl;

  w << "\t\"numEdgesOfEachType\": {" << std::endl;
  first = true;
  for (const auto &[key, value] : d_circuitParameters.d_numEdgesOfEachType)
  {
    if (value != 0)
    {
      if (first)
      {
        first = false;
        w << "\t\t\"" << key.first << "-" << key.second << "\": " << value;
      }
      else 
      {
        w << "," << std::endl << "\t\t\"" << key.first << "-" << key.second << "\": " << value;
      }
    }
  }
  w << std::endl;

  w << "\t}" << std::endl;


  w << "}";

  return true;
}

bool Circuit::checkExistingHash() // TODO: is it really need return true when hash wrong?
{
  std::string path = FilesTools::getParentDirOf(d_path);
  if (path == "" || !std::filesystem::exists(path))
    return false;

  std::ifstream r(path);
  
  std::string hash = "";

  r >> hash;

  while (r >> hash)
    if (hash != d_circuitParameters.d_hashCode)
      return false; //TODO: costul

  return false;
}

bool Circuit::generate(bool i_pathExists)
{
  if (!i_pathExists)
    //d_path += d_circuitName;

  if (!graphToVerilog(d_path, i_pathExists))
    return false;

  updateCircuitsParameters();

  if (!saveParameters())
    return false;
  //TODO: costul
  //if (checkExistingHash() || d_circuitParameters.d_reliability == 0 || d_circuitParameters.d_gates == 0)
  //{
    //if (!i_pathExists)
    //  std::filesystem::remove_all(d_path);
  //}
  //else
  //{
  //  std::string path = FilesTools::getParentDirOf(d_path) + "/hashCodes.txt";
  //  std::ofstream w(path, std::ios_base::out | std::ios_base::app);
  //  w << d_circuitParameters.d_hashCode;
  //}

  return true;
}

void Circuit::setTable(const TruthTable& i_tt)
{
  d_tTable = i_tt;
}

void Circuit::setPath(const std::string& i_path)
{
  d_path = i_path;
}

void Circuit::setCircuitName(const std::string& i_circName)
{
  d_circuitName = i_circName;
}

bool Circuit::addVertex(const std::string i_vertexName, const std::string& i_operation, const std::string& i_wireName)
{
  return d_graph.addVertex(i_vertexName, i_operation, i_wireName);
}

int Circuit::getIndexOfWireName(const std::string& i_wireName)
{
  return d_graph.getIndexOfWireName(i_wireName);
}

GraphVertex Circuit::getVertice(int i) const
{
  return d_graph.getVertice(i);
}

bool Circuit::addEdge(const std::string& i_vertexFrom, const std::string& i_vertexTo, bool i_isExpression)
{
  return d_graph.addEdge(i_vertexFrom, i_vertexTo, i_isExpression);
}

bool Circuit::addDoubleEdge(const std::string& i_vertexFromFirst, const std::string& i_vertexFromSecond, const std::string& i_vertexTo, bool i_isExpression)
{
  return d_graph.addDoubleEdge(i_vertexFromFirst, i_vertexFromSecond,
    i_vertexTo, i_isExpression);
}

void Circuit::setVerticeOperation(int i_vertice, const std::string& i_operation)
{
  d_graph.setVerticeOperation(i_vertice, i_operation);
}
