#include <algorithm>
#include "CascadeGenerator.hpp"
#include <CircuitGenGraph/GraphVertex.hpp>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <random>
#include <unordered_map>

namespace CG_Gen {

CascadeGenerator::CascadeGenerator() : SimpleGenerator() {}

CascadeGenerator::CascadeGenerator(uint_fast32_t i_seed) 
    : SimpleGenerator(i_seed) {}

CascadeGenerator::CascadeGenerator(const GenerationParameters &i_param) 
    : SimpleGenerator(i_param) {
    auto cascadeParams = i_param.getCascade();
    m_minStates = cascadeParams.getMinNumStates();
    m_maxStates = cascadeParams.getMaxNumStates();
    m_numautomatons = cascadeParams.getNumAutomatons();
}

GraphPtr CascadeGenerator::generatorCascade() {

    if (m_minStates > m_maxStates) {
        throw std::invalid_argument("min_num_states cannot be greater than max_num_states");
    }

    auto graph = std::make_shared<OrientedGraph>("AutomataCascade");
    VertexPtr clock = graph->addInput("clock");
    VertexPtr reset = graph->addInput("reset");

    uint32_t numGlobalInputs = getParameters().getInputs();
    uint32_t numOutputs = getParameters().getOutputs();

    if (numOutputs < numGlobalInputs) {
        throw std::invalid_argument("Number of outputs must be >= number of inputs for cascade connection.");
    }

    std::vector<VertexPtr> global_inputs;
    for (uint32_t i = 0; i < numGlobalInputs; ++i) {
        global_inputs.push_back(graph->addInput("x" + std::to_string(i)));
    }

    std::vector<VertexPtr> previous_outputs;

    uint32_t q = getParameters().getSeed();
    for (uint32_t automaton_idx = 0; automaton_idx < m_numautomatons; ++automaton_idx) {
        d_randGenerator.setSeed(q);
        q += q;
        bool isMoore = d_randGenerator.getRandInt(0, 1, true);
        uint32_t numStates = d_randGenerator.getRandInt(m_minStates, m_maxStates, true);

        std::vector<VertexPtr> automaton_inputs;
        if (automaton_idx == 0) {
            for (uint32_t i = 0; i < global_inputs.size(); ++i) {
                VertexPtr buf = graph->addGate(Gates::GateBuf, "a" + std::to_string(automaton_idx) + "_x" + std::to_string(i));
                graph->addEdge(global_inputs[i], buf);
                automaton_inputs.push_back(buf);
            }
        } else {
            if (previous_outputs.size() < numGlobalInputs) {
                throw std::runtime_error("Not enough outputs from previous automaton to connect as inputs");
            }
            for (uint32_t i = 0; i < numGlobalInputs; ++i) {
                VertexPtr buf = graph->addGate(Gates::GateBuf, "a" + std::to_string(automaton_idx) + "_x" + std::to_string(i));
                graph->addEdge(previous_outputs[i], buf);
                automaton_inputs.push_back(buf);
            }
        }

        std::vector<VertexPtr> automaton_outputs;
        std::vector<VertexPtr> output_or_gates;
        for (uint32_t i = 0; i < numOutputs; ++i) {
            VertexPtr output = graph->addOutput("a" + std::to_string(automaton_idx) + "_f" + std::to_string(i));
            VertexPtr or_gate = graph->addGate(Gates::GateOr, "a" + std::to_string(automaton_idx) + "_or_f" + std::to_string(i));
            graph->addEdge(or_gate, output);
            output_or_gates.push_back(or_gate);
            automaton_outputs.push_back(output);
        }

        std::unordered_map<std::string, VertexPtr> state_bufs, state_ors, state_dffs;
        for (uint32_t i = 0; i < numStates; ++i) {
            std::string name = "a" + std::to_string(automaton_idx) + "_s" + std::to_string(i);
            VertexPtr curr = graph->addGate(Gates::GateBuf, "curr_" + name);
            VertexPtr or_gate = graph->addGate(Gates::GateOr, "or_" + name);
            VertexPtr dff = graph->addSequential(static_cast<SequentialTypes>(ff | RST), clock, or_gate, reset, "dff_" + name);
            graph->addEdge(dff, curr);
            state_bufs[name] = curr;
            state_ors[name] = or_gate;
            state_dffs[name] = dff;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> stateDist(0, numStates - 1);
        std::uniform_int_distribution<uint32_t> outputDist(0, numOutputs - 1);

        std::unordered_set<std::string> reachable_states = {
            "a" + std::to_string(automaton_idx) + "_s0"
        };
        std::unordered_set<uint32_t> reachable_outputs;

        for (const auto& [fromName, fromBuf] : state_bufs) {
            for (uint32_t i = 0; i < automaton_inputs.size(); ++i) {
                std::string toName = "a" + std::to_string(automaton_idx) + "_s" + std::to_string(stateDist(gen));
                if (reachable_states.size() < numStates) {
                    for (uint32_t idx = 0; idx < numStates; ++idx) {
                        std::string candidate = "a" + std::to_string(automaton_idx) + "_s" + std::to_string(idx);
                        if (reachable_states.count(candidate) == 0) {
                            toName = candidate;
                            break;
                        }
                    }
                }

                VertexPtr and_gate = graph->addGate(Gates::GateAnd, fromName + "_to_" + toName + "_x" + std::to_string(i));
                graph->addEdge(automaton_inputs[i], and_gate);
                graph->addEdge(fromBuf, and_gate);
                graph->addEdge(and_gate, state_ors[toName]);
                reachable_states.insert(toName);
            }
        }

        for (const auto& [stateName, _] : state_bufs) {
            if (reachable_states.count(stateName) == 0) {
                std::string fromName = *reachable_states.begin();
                VertexPtr fromBuf = state_bufs[fromName];
                VertexPtr toOr = state_ors[stateName];
                VertexPtr input = automaton_inputs[0];

                VertexPtr and_gate = graph->addGate(Gates::GateAnd, fromName + "_to_" + stateName + "_fix");
                graph->addEdge(fromBuf, and_gate);
                graph->addEdge(input, and_gate);
                graph->addEdge(and_gate, toOr);
                reachable_states.insert(stateName);
            }
        }

        if (isMoore) {

            std::unordered_map<uint32_t, std::string> output_to_state;
            std::unordered_set<std::string> used_states;

            for (uint32_t out_idx = 0; out_idx < numOutputs; ++out_idx) {
                uint32_t state_idx;
                std::string state_name;
                
                do {
                    state_idx = d_randGenerator.getRandInt(0, numStates - 1, true);
                    state_name = "a" + std::to_string(automaton_idx) + "_s" + std::to_string(state_idx);
                } while (used_states.count(state_name) > 0);
                graph->addEdge(state_bufs[state_name], output_or_gates[out_idx]);
                output_to_state[out_idx] = state_name;
                used_states.insert(state_name);
            }

            for (const auto& [state_name, state_buf] : state_bufs) {
                if (used_states.count(state_name) == 0) {
                    uint32_t out_idx = d_randGenerator.getRandInt(0, numOutputs - 1, true);
                    graph->addEdge(state_bufs[state_name], output_or_gates[out_idx]);
                }
            }
        } else {
            std::vector<VertexPtr> all_transitions;
            for (const auto& [state_name, state_buf] : state_bufs) {
                for (VertexPtr out_conn : state_buf->getOutConnections()) {
                    if (out_conn->getType() == VertexTypes::gate && 
                        static_cast<GraphVertexGates*>(out_conn)->getGate() == Gates::GateAnd) {
                        all_transitions.push_back(out_conn);
                    }
                }
            }

            std::unordered_map<uint32_t, VertexPtr> output_to_transition;
            std::unordered_set<VertexPtr> used_transitions;

            for (uint32_t out_idx = 0; out_idx < numOutputs; ++out_idx) {
                VertexPtr transition;
                do {
                    uint32_t trans_idx = d_randGenerator.getRandInt(0, all_transitions.size() - 1, true);
                    transition = all_transitions[trans_idx];
                } while (used_transitions.count(transition) > 0);
                graph->addEdge(transition, output_or_gates[out_idx]);
                output_to_transition[out_idx] = transition;
                used_transitions.insert(transition);
            }

            for (VertexPtr transition : all_transitions) {
                if (used_transitions.count(transition) == 0) {
                    uint32_t out_idx = d_randGenerator.getRandInt(0, numOutputs - 1, true);
                    graph->addEdge(transition, output_or_gates[out_idx]);
                }
            }
        }
        std::string initState = "a" + std::to_string(automaton_idx) + "_s0";
        VertexPtr const1 = graph->addConst('1', "a" + std::to_string(automaton_idx) + "_init");
        VertexPtr initAnd = graph->addGate(Gates::GateAnd, "a" + std::to_string(automaton_idx) + "_init_and");
        VertexPtr initOr = graph->addGate(Gates::GateOr, "a" + std::to_string(automaton_idx) + "_init_or");

        graph->addEdge(reset, initAnd);
        graph->addEdge(const1, initAnd);
        graph->addEdge(initAnd, initOr);


        if (state_ors.count(initState)) {
            graph->addEdge(state_ors[initState], initOr);
        }

        VertexPtr init_dff = graph->addSequential(static_cast<SequentialTypes>(ASYNC | ff | RST), clock, initOr, reset, "init_dff_" + std::to_string(automaton_idx));

        if (state_bufs.count(initState)) {
            graph->addEdge(init_dff, state_bufs[initState]);
        }

        previous_outputs = output_or_gates;
    }

    return graph;
}


} // namespace CG_Gen