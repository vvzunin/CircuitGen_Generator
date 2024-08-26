#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#include "Circuit.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <additional/filesTools/FilesTools.hpp>
#include <CircuitGenGraph/enums.hpp>

Circuit::Circuit(
    GraphPtr const                  i_graph,
    const std::vector<std::string>& i_logExpressions
) {
  d_graph = i_graph;
  d_graph->updateLevels();
  d_logExpressions = i_logExpressions;
}

void Circuit::computeHash() {
  std::stringstream stream;
  stream << std::setfill(' ') << std::setw(10)
         << d_circuitParameters.d_numInputs << '\n';
  stream << std::setfill(' ') << std::setw(10)
         << d_circuitParameters.d_numConstants << '\n';
  stream << std::setfill(' ') << std::setw(10)
         << d_circuitParameters.d_numOutputs << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_maxLevel
         << '\n';
  stream << std::setfill(' ') << std::setw(10) << d_circuitParameters.d_numEdges
         << '\n';

  for (auto [key, value] : d_circuitParameters.d_numElementsOfEachType)
    stream << "\t\t\"" << key << "\": " << value << '\n';

  for (auto [key, value] : d_circuitParameters.d_numEdgesOfEachType)
    stream << "\t\t\"" << key.first << "-" << key.second << "\": " << value
           << '\n';

  {
    // TODO: write logic of get SHA256
  }
}

void Circuit::updateCircuitParameters(GraphPtr i_graph) {
  if (i_graph->isEmptyFull())
    return;

  i_graph->updateLevels();
  LOG(INFO) << "Update ended. Calc started";

  d_circuitParameters.d_name = i_graph->getName();

  std::vector<std::shared_ptr<GraphVertexBase>> inputs =
      i_graph->getVerticesByType(VertexTypes::input);
  std::vector<std::shared_ptr<GraphVertexBase>> constants =
      i_graph->getVerticesByType(VertexTypes::constant);
  std::vector<std::shared_ptr<GraphVertexBase>> outputs =
      i_graph->getVerticesByType(VertexTypes::output);

  d_circuitParameters.d_numInputs    = inputs.size();
  d_circuitParameters.d_numConstants = constants.size();
  d_circuitParameters.d_numOutputs   = outputs.size();

  d_circuitParameters.d_maxLevel     = i_graph->getMaxLevel();

  d_circuitParameters.d_numEdges     = i_graph->getEdgesCount();
  // TODO: Добавить корректную реализацию
  // for (const auto &row : i_graph->getAdjacencyMatrixReference())
  //     for (auto el : row)
  //         if (el)
  //             d_circuitParameters.d_numEdges++;

  d_circuitParameters.d_numElementsOfEachType.clear();
  // const std::vector<GraphVertex> &gv = i_graph->getVerticesReference();

  for (auto [key, value] : i_graph->getGatesCount()) {
    d_circuitParameters
        .d_numElementsOfEachType[d_settings->parseGateToString(key)] = value;
    d_circuitParameters.d_numGates                                   += value;
  }

  d_circuitParameters.d_numElementsOfEachType["input"]  = inputs.size();
  d_circuitParameters.d_numElementsOfEachType["output"] = outputs.size();
  d_circuitParameters.d_numElementsOfEachType["const"]  = constants.size();

  d_circuitParameters.d_numEdgesOfEachType.clear();

  // calc gate-gate
  for (auto [from, sub] : i_graph->getEdgesGatesCount()) {
    for (auto [to, count] : sub) {
      d_circuitParameters.d_numEdgesOfEachType[{
          d_settings->parseGateToString(from),
          d_settings->parseGateToString(to)}] = count;
    }
  }

  // iterate through inputs
  for (auto inp : inputs) {
    for (auto child : inp->getOutConnections()) {
      std::string to = child->getGate() != Gates::GateDefault
                         ? d_settings->parseGateToString(child->getGate())
                         : child->getTypeName();
      ++d_circuitParameters.d_numEdgesOfEachType[{"input", to}];
    }
  }

  // iterate through outputs
  for (auto out : outputs) {
    for (auto child : out->getInConnections()) {
      if (auto ptr = child.lock()) {
        // here we do not parse pair input-output
        if (ptr->getType() == VertexTypes::input) {
          continue;
        }

        std::string from = ptr->getGate() != Gates::GateDefault
                             ? d_settings->parseGateToString(ptr->getGate())
                             : ptr->getTypeName();
        ++d_circuitParameters.d_numEdgesOfEachType[{from, "output"}];
      } else {
        throw std::invalid_argument("Dead pointer!");
      }
    }
  }

  // iterate through constants
  for (auto inp : constants) {
    for (auto child : inp->getOutConnections()) {
      // here we do not parse pair const-output
      if (child->getType() == VertexTypes::output) {
        continue;
      }
      std::string to = child->getGate() != Gates::GateDefault
                         ? d_settings->parseGateToString(child->getGate())
                         : child->getTypeName();

      ++d_circuitParameters.d_numEdgesOfEachType[{"const", to}];
    }
  }

  d_circuitParameters.d_hashCode = i_graph->calculateHash();
  // computeHash();
}

bool Circuit::graphToVerilog(const std::string& i_path, bool i_pathExists) {
  if (d_graph->isEmptyFull())
    return false;

  /* if (!i_pathExists) // TODO: work with directory
         if
     (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() +
     i_path)) std::filesystem::create_directory(i_path);
     */

  static std::string filename;
  static std::string s;

  size_t             previousSizeOfFileName = filename.size();

  if (!d_graph->getSubGraphs().empty()) {
    std::string folderSubgraphs = d_path + "/submodules";
    std::filesystem::create_directory(folderSubgraphs);
  }
  filename    = d_path + "/" + d_circuitName + ".v";

  size_t pos  = (s.find_last_of('/')) + 1;
  size_t pos2 = (filename.find_last_of('/')) + 1;

  if (previousSizeOfFileName == 0)
    s = std::filesystem::current_path().string() + "/"
      + filename;  // static variable will be created one time and then will be
                   // used through running of the program
  else
    s.replace(
        pos, previousSizeOfFileName, filename, pos2, previousSizeOfFileName
    );

  bool f = std::filesystem::exists(s);

  return d_graph->toVerilog(d_path, d_circuitName + ".v").first;
}

bool Circuit::graphToDOT(const std::string& i_path, bool i_pathExists) {
  LOG(INFO) << "Starting graphToDOT";
  if (d_graph->isEmptyFull()) {
    LOG(INFO) << "Graph empty. Returning";
    return false;
  }

  /* if (!i_pathExists) // TODO: work with directory
      if
  (!FilesTools::isDirectoryExists(std::filesystem::current_path().string() +
  i_path)) std::filesystem::create_directory(i_path);
  */

  // for (auto subGr : d_graph->getSubGraphs()) {
  //   d_graph->resetCounters(subGr);
  // }

  static std::string filename;
  static std::string s;

  size_t             previousSizeOfFileName = filename.size();

  if (!d_graph->getSubGraphs().empty()) {
    std::string folderSubgraphs = d_path + "/submodulesDOT";
    std::filesystem::create_directory(folderSubgraphs);
  }
  filename    = d_path + "/" + d_circuitName + ".dot";

  size_t pos  = (s.find_last_of('/')) + 1;
  size_t pos2 = (filename.find_last_of('/')) + 1;

  if (previousSizeOfFileName == 0)
    s = std::filesystem::current_path().string() + "/"
      + filename;  // static variable will be created one time and then will be
                   // used through running of the program
  else
    s.replace(
        pos, previousSizeOfFileName, filename, pos2, previousSizeOfFileName
    );

  bool f = std::filesystem::exists(s);
  LOG(INFO) << "Pathes created.";

  GraphPtr graphPtr = d_graph;
  if (!d_graph->getVerticesByType(VertexTypes::subGraph).empty()) {
    graphPtr = d_graph->unrollGraph();
    LOG(INFO) << "Graph unrolled";
  }
  LOG(INFO) << "Ready to creating DOT file. Starting.";
  return graphPtr->toDOT(d_path, d_circuitName + ".dot").first;
}

bool Circuit::graphToGraphML(
    const std::string& i_path,
    bool               i_makeGraphMLClassic,
    bool               i_makeGraphMLPseudoABCD,
    bool               i_makeGraphMLOpenABCD,
    bool               i_pathExists
) {
  LOG(INFO) << "Start graphToGraphML";
  if (i_makeGraphMLClassic) {
    std::ofstream w(i_path + "/" + d_circuitName + "_Classic.graphml");
    d_graph->toGraphMLClassic(w);
    w.close();
  }
  LOG(INFO) << "GraphMLClassic complete";
  if (i_makeGraphMLPseudoABCD) {
    std::ofstream w(i_path + "/" + d_circuitName + "_PseudoABC-D.graphml");
    d_graph->toGraphMLPseudoABCD(w);
    w.close();
  }
  LOG(INFO) << "GraphMLPseudoABCD complete";
  if (i_makeGraphMLOpenABCD) {
    std::ofstream w(i_path + "/" + d_circuitName + "_OpenABC-D.graphml");
    d_graph->toGraphMLOpenABCD(w);
    w.close();
  }
  LOG(INFO) << "GraphMLOpenABCD complete";
  return true;
}

bool Circuit::saveParameters(
    GraphPtr       i_graph,
    std::ofstream& i_outputFile,
    bool           i_isSubGraph
) {
  LOG(INFO) << "saveParameters started";
  std::string tab = i_isSubGraph ? "\t\t\t" : "\t";
  if (!i_outputFile)
    return false;

  if (i_isSubGraph) {
    i_outputFile << "\t\t" << '"' << i_graph->getName() << '"' << " : ";
  }

  i_outputFile << "{" << std::endl;

  i_outputFile << tab << "\"name\": \"" << d_circuitParameters.d_name << "\","
               << std::endl;
  i_outputFile << tab << "\"numInputs\": \"" << d_circuitParameters.d_numInputs
               << "\"," << std::endl;
  i_outputFile << tab << "\"numConstants\": \""
               << d_circuitParameters.d_numConstants << "\"," << std::endl;
  i_outputFile << tab << "\"numOutputs\": \""
               << d_circuitParameters.d_numOutputs << "\"," << std::endl;
  i_outputFile << tab << "\"maxLevel\": \"" << d_circuitParameters.d_maxLevel
               << "\"," << std::endl;
  i_outputFile << tab << "\"numEdges\": \"" << d_circuitParameters.d_numEdges
               << "\"," << std::endl;
  i_outputFile << tab << "\"numGates\": \"" << d_circuitParameters.d_numGates
               << "\"," << std::endl;
  i_outputFile << tab << "\"hash_code\": \"" << d_circuitParameters.d_hashCode
               << "\"," << std::endl;
  i_outputFile << tab << "\"connected\": " << std::boolalpha
               << i_graph->isConnected() << "," << std::endl;

  i_outputFile << tab << "\"numElementsOfEachType\": {" << std::endl;

  bool first = true;
  for (const auto& [key, value] : d_circuitParameters.d_numElementsOfEachType) {
    if (value != 0) {
      if (first) {
        first = false;
        i_outputFile << tab << "\t\"" << key << "\": " << value;
      } else {
        i_outputFile << "," << std::endl
                     << tab << "\t\"" << key << "\": " << value;
      }
    }
  }
  i_outputFile << std::endl;

  i_outputFile << tab << "}," << std::endl;

  i_outputFile << tab << "\"numEdgesOfEachType\": {" << std::endl;
  first = true;
  for (const auto& [key, value] : d_circuitParameters.d_numEdgesOfEachType) {
    if (value != 0) {
      if (first) {
        first = false;
        i_outputFile << tab << "\t\"" << key.first << "-" << key.second
                     << "\": " << value;
      } else {
        i_outputFile << "," << std::endl
                     << tab << "\t\"" << key.first << "-" << key.second
                     << "\": " << value;
      }
    }
  }

  i_outputFile << std::endl << tab << "}";

  if (!i_graph->getSubGraphs().empty()) {
    i_outputFile << ',';
  }

  i_outputFile << std::endl;

  if (!i_graph->getSubGraphs().empty()) {
    i_outputFile << tab << "\"submodules\" : {" << std::endl;
    std::set<GraphPtr> subSet = d_graph->getSetSubGraphs();
    for (auto sub = subSet.begin(); sub != subSet.end();) {
      LOG(INFO) << "Submodule " << sub->get()->getName();
      updateCircuitParameters(*sub);

      saveParameters(*sub, i_outputFile, true);
      // HERE IS MOVE TO NEXT
      if (++sub != subSet.end()) {
        i_outputFile << ", ";
      }
      i_outputFile << std::endl;
    }

    i_outputFile << tab << "}" << std::endl;
  }

  // file end
  i_outputFile << (i_isSubGraph ? "\t\t" : "") << "}";

  return true;
}

bool Circuit::checkExistingHash()  // TODO: is it really need return true when
                                   // hash wrong?
{
  std::string path = FilesTools::getParentDirOf(d_path);
  if (path == "" || !std::filesystem::exists(path))
    return false;

  std::ifstream r(path);

  std::string   hash = "";

  r >> hash;

  while (r >> hash)
    if (hash != d_circuitParameters.d_hashCode)
      return false;  // TODO: costul

  return false;
}

bool Circuit::generate(
    bool i_makeGraphMLClassic,
    bool i_makeGraphMLPseudoABCD,
    bool i_makeGraphMLOpenABCD,
    bool i_pathExists
) {
  // creating all files in sub directories
  std::string d_path_temp = d_path + d_circuitName;
  d_path                  += d_circuitName + "/";

  std::filesystem::create_directories(d_path);

  // if (!i_pathExists)
  // d_path += d_circuitName;
  LOG(INFO) << "Writing verilog for " << d_circuitName;
  if (!graphToVerilog(d_path, i_pathExists))
    return false;
  LOG(INFO) << "Writing verilog ended for " << d_circuitName;

  LOG(INFO) << "Writing DOT for " << d_circuitName;
  if (!graphToDOT(d_path, i_pathExists))
    return false;
  LOG(INFO) << "Writing DOT ended for " << d_circuitName;

  LOG(INFO) << "Writing GraphML for " << d_circuitName;
  if (graphToGraphML(
          d_path,
          i_makeGraphMLClassic,
          i_makeGraphMLPseudoABCD,
          i_makeGraphMLOpenABCD,
          i_pathExists
      )) {
    LOG(INFO) << "Writing GraphML ended for " << d_circuitName;
  }

  updateCircuitParameters(d_graph);

  std::string   filename = d_path + "/" + d_circuitName + ".json";
  std::ofstream i_outputFile(filename);

  saveParameters(d_graph, i_outputFile);
  LOG(INFO) << "Circuit parameters saved." << d_circuitName;

  // TODO: costul
  // if (checkExistingHash() || d_circuitParameters.d_reliability == 0 ||
  // d_circuitParameters.d_gates == 0)
  //{
  // if (!i_pathExists)
  //     std::filesystem::remove_all(d_path);
  //}
  // else
  //{
  //    std::string path = FilesTools::getParentDirOf(d_path) +
  //    "/hashCodes.txt"; std::ofstream w(path, std::ios_base::out |
  //    std::ios_base::app); w << d_circuitParameters.d_hashCode;
  //}

  return true;
}

void Circuit::setTable(const TruthTable& i_tt) {
  d_tTable = i_tt;
}

void Circuit::setPath(const std::string& i_path) {
  d_path = i_path;
}

void Circuit::setCircuitName(const std::string& i_circName) {
  d_circuitName = i_circName;
  d_graph->setName(i_circName);
}

std::vector<std::shared_ptr<GraphVertexBase>> Circuit::getIndexOfWireName(
    const std::string& i_wireName
) {
  return d_graph->getVerticesByName(i_wireName);
}

Circuit Circuit::fromVerilog(const std::string& i_filepath) {
  // const int MODULE_WORD_SIZE = 7;
  // const int INPUT_WORD_SIZE = 6;
  // const int OUTPUT_WORD_SIZE = 7;
  // const int WIRE_WORD_SIZE = 5;

  GraphPtr graph;
  Circuit  circuit(graph, {});
  // circuit.setPath(i_filepath);

  // std::string verilog_module = readAllFile(i_filepath);

  // int start = verilog_module.find("module ");
  // // TODO would it work with "module NAME("
  // std::string left_brace = " (";
  // size_t io_names_start = verilog_module.find_first_of(left_brace, start +
  // MODULE_WORD_SIZE);

  // // Protection against missing left brace
  // assert(io_names_start != std::string::npos);

  // circuit.setCircuitName(
  //     removeSpaces(
  //         verilog_module.substr(start + MODULE_WORD_SIZE, io_names_start -
  //         start - MODULE_WORD_SIZE)));

  // start = skipSpaces(verilog_module, io_names_start + 1);

  // std::vector<std::string> inputs;
  // std::string inps = "";
  // std::string outs = "";

  // if (verilog_module.find("input", start) == start)
  // {
  //     int i_names_start = verilog_module.find("input ", start) +
  //     INPUT_WORD_SIZE; int o_names_start = verilog_module.find("output ",
  //     i_names_start + 1) + OUTPUT_WORD_SIZE;

  //     inps = removeSpaces(verilog_module.substr(i_names_start, o_names_start
  //     - i_names_start - OUTPUT_WORD_SIZE)); inps = inps.substr(0, inps.size()
  //     - 1);

  //     outs = removeSpaces(verilog_module.substr(
  //         o_names_start, verilog_module.find(");", o_names_start + 1) -
  //         o_names_start));

  //     start = verilog_module.find(");", o_names_start + 1);
  // }
  // else
  // {
  //     start = verilog_module.find(");", start);

  //     int i_names_start = verilog_module.find("input ", start) +
  //     INPUT_WORD_SIZE; int i_names_end = verilog_module.find(";",
  //     i_names_start);

  //     int o_names_start = verilog_module.find("output ", start) +
  //     OUTPUT_WORD_SIZE; int o_names_end = verilog_module.find(";",
  //     o_names_start);

  //     inps = removeSpaces(verilog_module.substr(i_names_start, i_names_end -
  //     i_names_start)); outs =
  //     removeSpaces(verilog_module.substr(o_names_start, o_names_end -
  //     o_names_start));

  //     start = std::max(i_names_end, o_names_end);
  // }

  // for (const auto &input : splitString(inps, ','))
  //     circuit.addVertex(input, "input");

  // for (const auto &output : splitString(outs, ','))
  //     circuit.addVertex(output, "output");

  // {
  //     int wire_start = verilog_module.find("wire ", start) + WIRE_WORD_SIZE;
  //     int wire_end = verilog_module.find(";", wire_start);
  //     // TODO: we really need this? std::string wires =
  //     removeSpaces(s.substr(wire_start, wire_end - wire_start)); start =
  //     wire_start + 1;
  // }

  // {
  //     verilog_module = verilog_module.substr(start);
  //     verilog_module = verilog_module.substr(0,
  //     verilog_module.find("endmodule")); verilog_module =
  //     verilog_module.substr(skipSpaces(verilog_module));

  //     int n = 0;

  //     while (verilog_module.size() != 0)
  //     {
  //         if (verilog_module.rfind("assign", 0) != 0)
  //         {
  //             int end = verilog_module.find(";");

  //             std::string type = verilog_module.substr(0,
  //             verilog_module.find_first_of(left_brace)); std::string wireList
  //             = removeSpaces(
  //                 verilog_module.substr(
  //                     verilog_module.find('(') + 1, end - 2 -
  //                     verilog_module.find('(')));
  //             std::vector<std::string> wires = splitString(wireList, ',');

  //             std::vector<GraphVertexBase*> tt =
  //             circuit.getIndexOfWireName(wires[0]); if (tt.size() != 0 &&
  //             circuit.getVertice(tt).getOperation() == "output")
  //             {
  //                 std::string w = "ewr_" + std::to_string(n++);
  //                 circuit.addVertex(w, "none", w);
  //                 circuit.addEdge(w, wires[0]);
  //                 wires[0] = w;
  //             }

  //             for (const std::string &wire : wires)
  //                 if (circuit.getIndexOfWireName(wire) == -1)
  //                     circuit.addVertex(wire, "none", wire);

  //             circuit.setVerticeOperation(circuit.getIndexOfWireName(wires[0]),
  //             type); if (wires.size() > 3) // TODO: what the magic number?
  //             {
  //                 std::string prev = wires[1];

  //                 for (int i = 2; i + 1 < wires.size(); ++i)
  //                 {
  //                     std::string wire = "ewr_" + std::to_string(n++);
  //                     circuit.addVertex(wire, type, wire);
  //                     circuit.addDoubleEdge(wires[i], prev, wire);
  //                     prev = wire;
  //                 }
  //                 circuit.addDoubleEdge(wires.back(), prev, wires[0]);
  //             }
  //             else
  //                 for (int i = 1; i < wires.size(); ++i)
  //                     circuit.addEdge(wires[i], wires[0]);

  //             verilog_module.erase(0, end + 1);
  //         }
  //         else
  //         {
  //             int end = verilog_module.find(";");

  //             std::string left = removeSpaces(verilog_module.substr(6,
  //             verilog_module.find('=') - 6)); std::string right =
  //             removeSpaces(
  //                 verilog_module.substr(verilog_module.find('=') + 1, end -
  //                 verilog_module.find('=') - 1));

  //             bool f = circuit.addEdge(right, left, false);

  //             verilog_module.erase(0, end + 1);
  //         }

  //         verilog_module = verilog_module.erase(0,
  //         skipSpaces(verilog_module));
  //     }
  // }
  return circuit;
}