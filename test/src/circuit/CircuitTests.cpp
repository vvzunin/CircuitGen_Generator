#include <gtest/gtest.h>
#include <filesystem>
#include "circuit/Circuit.hpp"
#include "fstream"


const std::string testDirectory = std::filesystem::current_path();

TEST(Circuit, VerilogAndParametersFileCreationForEmptyGraph) {
    auto* graph = new OrientedGraph("EmptyGraph");
    Circuit circuit(graph, {});
    circuit.setCircuitName("empty_graph");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/empty_graph.v";
    std::string paramsFilePath = testDirectory + "/empty_graph.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }
    
    bool saveSuccess = circuit.saveParameters(true); 

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}

TEST(Circuit, SimpleANDCircuit) {
    OrientedGraph* graph = new OrientedGraph("SimpleAND");
    auto input1 = graph->addInput("input1");
    auto input2 = graph->addInput("input2");
    auto andGate = graph->addGate(Gates::GateAnd, "andGate");
    auto output = graph->addOutput("output");
    graph->addEdge(input1, andGate);
    graph->addEdge(input2, andGate);
    graph->addEdge(andGate, output);

    Circuit circuit(graph, {});
    circuit.setCircuitName("simple_and");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/simple_and.v";
    std::string paramsFilePath = testDirectory + "/simple_and.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true);

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}

TEST(Circuit, SimpleORGate) {
    auto* graph = new OrientedGraph("SimpleOR");
    auto input1 = graph->addInput("input1");
    auto input2 = graph->addInput("input2");
    auto orGate = graph->addGate(Gates::GateOr, "orGate");
    auto output = graph->addOutput("output");
    graph->addEdge(input1, orGate);
    graph->addEdge(input2, orGate);
    graph->addEdge(orGate, output);

    Circuit circuit(graph, {});
    circuit.setCircuitName("simple_or_gate");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/simple_or_gate.v";
    std::string paramsFilePath = testDirectory + "/simple_or_gate.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true);

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}


TEST(Circuit, NOTGate) {
    auto* graph = new OrientedGraph("NOTGate");
    auto input = graph->addInput("input");
    auto notGate = graph->addGate(Gates::GateNot, "notGate");
    auto output = graph->addOutput("output");
    graph->addEdge(input, notGate);
    graph->addEdge(notGate, output);

    Circuit circuit(graph, {});
    circuit.setCircuitName("not_gate");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/not_gate.v";
    std::string paramsFilePath = testDirectory + "/not_gate.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true);

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}


TEST(Circuit, ComplexLogicCircuit) {
    auto* graph = new OrientedGraph("ComplexLogic");
    auto input1 = graph->addInput("input1");
    auto input2 = graph->addInput("input2");
    auto input3 = graph->addInput("input3");
    auto andGate1 = graph->addGate(Gates::GateAnd, "andGate1");
    auto orGate = graph->addGate(Gates::GateOr, "orGate");
    auto notGate = graph->addGate(Gates::GateNot, "notGate");
    auto output = graph->addOutput("output");

    graph->addEdge(input1, andGate1);
    graph->addEdge(input2, andGate1);
    graph->addEdge(andGate1, orGate);
    graph->addEdge(input3, notGate);
    graph->addEdge(notGate, orGate);
    graph->addEdge(orGate, output);

    Circuit circuit(graph, {});
    circuit.setCircuitName("complex_logic_circuit");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/complex_logic_circuit.v";
    std::string paramsFilePath = testDirectory + "/complex_logic_circuit.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true);

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}


TEST(Circuit, MultipleOutputs) {
    auto* graph = new OrientedGraph("MultipleOutputs");
    auto input = graph->addInput("input");
    auto notGate = graph->addGate(Gates::GateNot, "notGate");
    auto output1 = graph->addOutput("output1");
    auto output2 = graph->addOutput("output2");

    graph->addEdge(input, notGate);
    graph->addEdge(notGate, output1);
    graph->addEdge(input, output2);

    Circuit circuit(graph, {});
    circuit.setCircuitName("multiple_outputs");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/multiple_outputs.v";
    std::string paramsFilePath = testDirectory + "/multiple_outputs.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true); 

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}


TEST(Circuit, FeedbackLoop) {
    auto* graph = new OrientedGraph("FeedbackLoop");
    auto input = graph->addInput("input");
    auto andGate = graph->addGate(Gates::GateAnd, "andGate");
    auto output = graph->addOutput("output");
    graph->addEdge(input, andGate);
    graph->addEdge(andGate, output);
    graph->addEdge(output, andGate);

    Circuit circuit(graph, {});
    circuit.setCircuitName("feedback_loop");
    circuit.setPath(testDirectory);

    std::string verilogFilePath = testDirectory + "/feedback_loop.v";
    std::string paramsFilePath = testDirectory + "/feedback_loop.json";
    {
        std::ofstream fileStream(verilogFilePath);
        circuit.graphToVerilog(verilogFilePath, true);
        fileStream.close();
    }

    bool saveSuccess = circuit.saveParameters(true);

    EXPECT_TRUE(std::filesystem::exists(verilogFilePath));
    EXPECT_TRUE(std::filesystem::exists(paramsFilePath));
    EXPECT_TRUE(saveSuccess);

    std::filesystem::remove(verilogFilePath);
    std::filesystem::remove(paramsFilePath);
}