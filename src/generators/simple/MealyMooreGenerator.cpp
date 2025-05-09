#include <algorithm>
#include <fstream>
#include <memory>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

#include "MealyMooreGenerator.hpp"

namespace CG_Gen {

MealyMooreGenerator::MealyMooreGenerator() : SimpleGenerator() {
}

MealyMooreGenerator::MealyMooreGenerator(uint_fast32_t i_seed) :
    SimpleGenerator(i_seed) {
}

MealyMooreGenerator::MealyMooreGenerator(const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

DotReturn MealyMooreGenerator::generatorMoore(uint32_t i_Inputs,
                                              uint32_t i_Outputs,
                                              uint32_t i_numStates,
                                              uint32_t i_seed,
                                              bool i_saveDOT_mmg) {
  DotReturn dotData;
  if (i_numStates < 1 || i_Inputs < 1 || i_Outputs < 1)
    return dotData;

  d_randGenerator.setSeed(i_seed);

  dotData.push_back({DotTypes::DotGate,
                     {{"name", "__start0"}, {"label", ""}, {"shape", "none"}}});

  std::vector<uint32_t> outputs(i_numStates);
  for (uint32_t i = 0; i < i_numStates; ++i) {
    outputs[i] = d_randGenerator.getRandInt(1, i_Outputs, true);
  }

  for (uint32_t i = 0; i < i_numStates; ++i) {
    dotData.push_back({DotTypes::DotGate,
                       {{"name", "s" + std::to_string(i)},
                        {"label", "s" + std::to_string(i) + "\\nout=f" +
                                      std::to_string(outputs[i])},
                        {"shape", "circle"}}});
  }

  dotData.push_back(
      {DotTypes::DotEdge, {{"from", "__start0"}, {"to", "s0"}, {"label", ""}}});

  for (uint32_t i = 0; i < i_numStates; ++i) {
    for (uint32_t input = 0; input < i_Inputs; ++input) {
      uint32_t target;
      if (i_numStates == 1) {
        target = 0;
      } else {
        target = d_randGenerator.getRandInt(0, i_numStates - 1, true);
      }

      dotData.push_back({DotTypes::DotEdge,
                         {{"from", "s" + std::to_string(i)},
                          {"to", "s" + std::to_string(target)},
                          {"label", "x" + std::to_string(input)}}});
    }
  }

  return dotData;
}

DotReturn MealyMooreGenerator::generatorMealy(uint32_t i_Inputs,
                                              uint32_t i_Outputs,
                                              uint32_t i_numStates,
                                              uint32_t i_seed,
                                              bool i_saveDOT_mmg) {
  DotReturn dotData;
  if (i_numStates < 1 || i_Inputs < 1 || i_Outputs < 1)
    return dotData;

  d_randGenerator.setSeed(i_seed);

  dotData.push_back({DotTypes::DotGate,
                     {{"name", "__start0"}, {"label", ""}, {"shape", "none"}}});

  for (uint32_t i = 0; i < i_numStates; ++i) {
    dotData.push_back({DotTypes::DotGate,
                       {{"name", "s" + std::to_string(i)},
                        {"label", "s" + std::to_string(i)},
                        {"shape", "circle"}}});
  }

  dotData.push_back(
      {DotTypes::DotEdge, {{"from", "__start0"}, {"to", "s0"}, {"label", ""}}});

  std::unordered_map<std::string, bool> transitions;
  for (uint32_t i = 0; i < i_numStates; ++i) {
    for (uint32_t input = 0; input < i_Inputs; ++input) {
      std::string key = std::to_string(i) + "_x" + std::to_string(input);

      if (!transitions.count(key)) {
        uint32_t target;
        if (i_numStates == 1) {
          target = 0;
        } else {
          target = d_randGenerator.getRandInt(0, i_numStates - 1, true);
        }

        uint32_t output = d_randGenerator.getRandInt(1, i_Outputs, true);
        dotData.push_back({DotTypes::DotEdge,
                           {{"from", "s" + std::to_string(i)},
                            {"to", "s" + std::to_string(target)},
                            {"label", "x" + std::to_string(input) + " / f" +
                                          std::to_string(output)}}});
        transitions[key] = true;
      }
    }
  }

  return dotData;
}

std::string GenerateContent(DotReturn d_dot) {
  std::string content;

  if (d_dot.empty()) {
    std::cerr << "d_dot is empty or save_dot_mmg is set as false" << std::endl;
    return "";
  }

  content += "digraph CCGMM {\n";
  content += "    rankdir=LR;\n";
  content += "    node [shape=circle];\n\n";

  for (const auto &element: d_dot) {
    switch (element.first) {
      case DotTypes::DotGate: {
        auto name_it = element.second.find("name");
        auto label_it = element.second.find("label");
        auto shape_it = element.second.find("shape");

        if (name_it != element.second.end()) {
          content += "    " + name_it->second;

          if (label_it != element.second.end() ||
              shape_it != element.second.end()) {
            content += " [";

            if (label_it != element.second.end()) {
              content += "label=\"" + label_it->second + "\"";
            }

            if (shape_it != element.second.end()) {
              if (label_it != element.second.end())
                content += ", ";
              content += "shape=" + shape_it->second;
            }

            content += "]";
          }
          content += ";\n";
        }
        break;
      }
      case DotTypes::DotEdge: {
        auto from_it = element.second.find("from");
        auto to_it = element.second.find("to");
        auto label_it = element.second.find("label");

        if (from_it != element.second.end() && to_it != element.second.end()) {
          content += "    " + from_it->second + " -> " + to_it->second;

          if (label_it != element.second.end() && !label_it->second.empty()) {
            content += " [label=\"" + label_it->second + "\"]";
          }
          content += ";\n";
        }
        break;
      }
      default:
        break;
    }
  }

  content += "}\n";

  return content;
}

std::string sanitizeName(std::string name) {
  name.erase(std::remove_if(name.begin(), name.end(),
                            [](char c) { return c == '/' || c == ' '; }),
             name.end());
  return name.empty() ? "unnamed" : name;
}

void parseDotContent(GraphPtr graph, const std::string &content, bool isMoore) {
  if (!graph || content.empty()) {
    throw std::invalid_argument("Invalid graph or empty content");
  }

  static const std::regex moore_state_regex(
      R"(^\s*(\w+)\s*\[label\s*=\s*\"([^\n\\]+)(?:\\nout=([^\"]+))?\")");
  static const std::regex moore_transition_regex(
      R"(^\s*(\w+)\s*->\s*(\w+)\s*\[label\s*=\s*\"([^\"]+)\"\])");
  static const std::regex mealy_state_regex(
      R"(^\s*(\w+)\s*\[label\s*=\s*\"([^\n\\]+)(?:\\n([^\"]+))?\")");
  static const std::regex mealy_transition_regex(
      R"(^\s*(\w+)\s*->\s*(\w+)\s*\[label\s*=\s*\"([^/]+)/([^\"]+)\"\])");

  const auto &state_regex = isMoore ? moore_state_regex : mealy_state_regex;
  const auto &transition_regex =
      isMoore ? moore_transition_regex : mealy_transition_regex;

  struct StateInfo {
    std::string name;
    std::string output;
    std::vector<std::tuple<std::string, std::string, std::string>> transitions;
  };

  std::unordered_map<std::string, StateInfo> states;
  std::unordered_set<std::string> inputs, outputs;

  std::istringstream iss(content);
  std::string line;
  while (std::getline(iss, line)) {
    std::smatch match;
    if (std::regex_search(line, match, state_regex) &&
        match[1].str() != "__start0") {
      std::string name = sanitizeName(match[1].str());
      StateInfo s;
      s.name = name;
      if (isMoore && match.size() >= 4) {
        s.output = sanitizeName(match[3].str());
        if (!s.output.empty())
          outputs.insert(s.output);
      }
      if (!states.emplace(name, std::move(s)).second) {
        throw std::runtime_error("Duplicate state: " + name);
      }
    } else if (std::regex_search(line, match, transition_regex) &&
               match[1].str() != "__start0") {
      std::string from = sanitizeName(match[1].str());
      std::string to = sanitizeName(match[2].str());
      if (isMoore) {
        std::string input = sanitizeName(match[3].str());
        if (!input.empty())
          inputs.insert(input);
        states[from].transitions.emplace_back(from, input, to);
      } else {
        std::string input = sanitizeName(match[3].str());
        std::string output = sanitizeName(match[4].str());
        if (!input.empty() && !output.empty()) {
          inputs.insert(input);
          outputs.insert(output);
          states[from].transitions.emplace_back(from, input + "/" + output, to);
        }
      }
    }
  }

  if (states.empty()) {
    throw std::runtime_error("No valid states found in DOT file");
  }

  VertexPtr clock = graph->addInput("clock");
  VertexPtr reset = graph->addInput("reset");
  if (!clock || !reset) {
    throw std::runtime_error("Failed to create clock/reset");
  }

  std::unordered_map<std::string, VertexPtr> state_bufs;
  for (const auto &[name, info]: states) {
    VertexPtr curr = graph->addGate(Gates::GateBuf, "curr_" + name);
    state_bufs[name] = curr;
  }

  std::unordered_map<std::string, VertexPtr> inputs_map, outputs_map;
  for (const auto &in: inputs) {
    VertexPtr v = graph->addInput(in);
    if (!v)
      throw std::runtime_error("Failed to create input: " + in);
    inputs_map[in] = v;
  }

  std::unordered_map<std::string, VertexPtr> output_ors;
  for (const auto &out: outputs) {
    VertexPtr o = graph->addOutput(out);
    VertexPtr g = graph->addGate(Gates::GateOr, "or_" + out);
    if (!o || !g)
      throw std::runtime_error("Failed output: " + out);
    graph->addEdge(g, o);
    outputs_map[out] = o;
    output_ors[out] = g;
  }

  std::unordered_map<std::string, VertexPtr> state_ors;
  for (const auto &[name, info]: states) {
    for (const auto &[from, label, to]: info.transitions) {
      std::string in = label;
      std::string out;
      if (!isMoore) {
        size_t slash = label.find('/');
        in = label.substr(0, slash);
        out = label.substr(slash + 1);
      }
      auto in_v = inputs_map.find(in);
      if (in_v == inputs_map.end())
        continue;

      VertexPtr and_gate =
          graph->addGate(Gates::GateAnd, from + "_to_" + to + "_" + in);
      if (!and_gate)
        continue;
      graph->addEdge(state_bufs[from], and_gate);
      graph->addEdge(in_v->second, and_gate);

      if (!isMoore && !out.empty() && output_ors.count(out)) {
        graph->addEdge(and_gate, output_ors[out]);
      }

      if (!state_ors.count(to)) {
        VertexPtr or_gate = graph->addGate(Gates::GateOr, "or_" + to);
        VertexPtr dff =
            graph->addSequential(static_cast<SequentialTypes>(ff | RST), clock,
                                 or_gate, reset, "dff_" + to);
        graph->addEdge(dff, state_bufs[to]);
        state_ors[to] = or_gate;
      }

      graph->addEdge(and_gate, state_ors[to]);
    }

    if (isMoore && !info.output.empty() && output_ors.count(info.output)) {
      graph->addEdge(state_bufs[name], output_ors[info.output]);
    }
  }

  auto init = states.count("s0") ? "s0" : states.begin()->first;
  VertexPtr const1 = graph->addConst('1', "init");
  VertexPtr and_gate = graph->addGate(Gates::GateAnd, "init_and");
  VertexPtr or_gate = graph->addGate(Gates::GateOr, "init_or");
  graph->addEdge(reset, and_gate);
  graph->addEdge(const1, and_gate);
  if (state_ors.count(init)) {
    graph->addEdge(state_ors[init], or_gate);
  }
  graph->addEdge(and_gate, or_gate);
  VertexPtr dff =
      graph->addSequential(static_cast<SequentialTypes>(ASYNC | ff | RST),
                           clock, or_gate, reset, "init_dff");
  graph->addEdge(dff, state_bufs[init]);
}

DotReturn
MealyMooreGenerator::generatorMealyMoore(const GenerationParameters &i_param) {
  uint32_t Inputs = i_param.getInputs();
  uint32_t Outputs = i_param.getOutputs();
  uint32_t numStates = i_param.getMealyMoore().getNumStates();
  bool genType = i_param.getMealyMoore().getGenType();
  uint32_t seed = i_param.getSeed();
  bool saveDOT_mmg = i_param.getMealyMoore().getsaveDOT_mmg();

  if (genType) {
    return generatorMoore(Inputs, Outputs, numStates, seed, saveDOT_mmg);
  }
  return generatorMealy(Inputs, Outputs, numStates, seed, saveDOT_mmg);
}

DotReturn MealyMooreGenerator::generatorMealyMoore() {
  return generatorMealyMoore(getParameters());
}

GraphPtr MealyMooreGenerator::generatorDotReturnToGraphMealy(
    uint32_t i_Inputs, uint32_t i_Outputs, uint32_t i_numStates,
    uint32_t i_seed, bool i_saveDOT_mmg) {
  std::string content = GenerateContent(
      generatorMealy(i_Inputs, i_Outputs, i_numStates, i_seed, i_saveDOT_mmg));
  auto graph = std::make_shared<OrientedGraph>("MealyAutomaton");
  parseDotContent(graph, content, false);
  return graph;
}

GraphPtr MealyMooreGenerator::generatorDotReturnToGraphMoore(
    uint32_t i_Inputs, uint32_t i_Outputs, uint32_t i_numStates,
    uint32_t i_seed, bool i_saveDOT_mmg) {
  std::string content = GenerateContent(
      generatorMoore(i_Inputs, i_Outputs, i_numStates, i_seed, i_saveDOT_mmg));
  auto graph = std::make_shared<OrientedGraph>("MooreAutomaton");
  parseDotContent(graph, content, true);
  return graph;
}

GraphPtr MealyMooreGenerator::generatorDotReturnToGraph(
    const GenerationParameters &i_param) {
  uint32_t Inputs = i_param.getInputs();
  uint32_t Outputs = i_param.getOutputs();
  uint32_t numStates = i_param.getMealyMoore().getNumStates();
  bool genType = i_param.getMealyMoore().getGenType();
  uint32_t seed = i_param.getSeed();
  bool saveDOT_mmg = i_param.getMealyMoore().getsaveDOT_mmg();

  return genType ? generatorDotReturnToGraphMoore(Inputs, Outputs, numStates,
                                                  seed, saveDOT_mmg)
                 : generatorDotReturnToGraphMealy(Inputs, Outputs, numStates,
                                                  seed, saveDOT_mmg);
}

GraphPtr MealyMooreGenerator::generatorDotReturnToGraph() {
  return generatorDotReturnToGraph(getParameters());
}

} // namespace CG_Gen