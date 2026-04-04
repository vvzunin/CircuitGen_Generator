#include "DotGenerator.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

namespace CG_Gen {

DotGenerator::DotGenerator() : SimpleGenerator() {
}
DotGenerator::DotGenerator(uint_fast32_t i_seed) : SimpleGenerator(i_seed) {
}
DotGenerator::DotGenerator(const GenerationParameters &i_param) :
    SimpleGenerator(i_param) {
}

namespace {

std::string readDotFile(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open DOT file: " + path);
  }

  auto size = file.tellg();
  if (size > 10 * 1024 * 1024) {
    throw std::runtime_error("DOT file too large: " + path);
  }

  file.seekg(0);
  std::string content(size, '\0');
  file.read(&content[0], size);
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
} // anonymous namespace

GraphPtr DotGenerator::generatorDotToGraphMealy(std::string i_DotPath) {
  std::string content = std::filesystem::is_directory(i_DotPath)
                            ? readDotFile(i_DotPath)
                            : readDotFile(i_DotPath);
  auto graph = std::make_shared<OrientedGraph>("MealyAutomaton");
  parseDotContent(graph, content, false);
  return graph;
}

GraphPtr DotGenerator::generatorDotToGraphMoore(std::string i_DotPath) {
  std::string content = std::filesystem::is_directory(i_DotPath)
                            ? readDotFile(i_DotPath)
                            : readDotFile(i_DotPath);
  auto graph = std::make_shared<OrientedGraph>("MooreAutomaton");
  parseDotContent(graph, content, true);
  return graph;
}

GraphPtr
DotGenerator::generatorDotToGraph(const GenerationParameters &i_param) {
  bool GenTypeDot = i_param.getDotToGraph().getGenTypeDot();
  std::string DotPath = i_param.getDotToGraph().getDotPath();
  return GenTypeDot ? generatorDotToGraphMoore(DotPath)
                    : generatorDotToGraphMealy(DotPath);
}

GraphPtr DotGenerator::generatorDotToGraph() {
  return generatorDotToGraph(getParameters());
}
} // namespace CG_Gen
