#include <filesystem>

#include "circuit/Circuit.hpp"

#include <gtest/gtest.h>

#include "easylogging++Init.hpp"
#include "fstream"

const std::string testDirectory = std::filesystem::current_path();

TEST(Circuit, TestingVerilogAndParametersForEmptyGraph) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("EmptyGraph");
  Circuit  circuit(graphPtr, {});
  circuit.setCircuitName("empty_graph");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/empty_graph.v";
  std::string paramsFilePath  = testDirectory + "/empty_graph.json";
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

TEST(Circuit, TestingVerilogAndParametersSimpleANDCircuit) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("SimpleAND");
  auto     input1   = graphPtr->addInput("input1");
  auto     input2   = graphPtr->addInput("input2");
  auto     andGate  = graphPtr->addGate(Gates::GateAnd, "andGate");
  auto     output   = graphPtr->addOutput("output");
  graphPtr->addEdge(input1, andGate);
  graphPtr->addEdge(input2, andGate);
  graphPtr->addEdge(andGate, output);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("simple_and");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/simple_and.v";
  std::string paramsFilePath  = testDirectory + "/simple_and.json";
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

TEST(Circuit, TestingVerilogAndParametersSimpleORGate) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("SimpleOR");
  auto     input1   = graphPtr->addInput("input1");
  auto     input2   = graphPtr->addInput("input2");
  auto     orGate   = graphPtr->addGate(Gates::GateOr, "orGate");
  auto     output   = graphPtr->addOutput("output");
  graphPtr->addEdge(input1, orGate);
  graphPtr->addEdge(input2, orGate);
  graphPtr->addEdge(orGate, output);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("simple_or_gate");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/simple_or_gate.v";
  std::string paramsFilePath  = testDirectory + "/simple_or_gate.json";
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

TEST(Circuit, TestingVerilogAndParametersNOTGate) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("NOTGate");
  auto     input    = graphPtr->addInput("input");
  auto     notGate  = graphPtr->addGate(Gates::GateNot, "notGate");
  auto     output   = graphPtr->addOutput("output");
  graphPtr->addEdge(input, notGate);
  graphPtr->addEdge(notGate, output);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("not_gate");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/not_gate.v";
  std::string paramsFilePath  = testDirectory + "/not_gate.json";
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

TEST(Circuit, TestingVerilogAndParametersComplexLogicCircuit) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("ComplexLogic");
  auto     input1   = graphPtr->addInput("input1");
  auto     input2   = graphPtr->addInput("input2");
  auto     input3   = graphPtr->addInput("input3");
  auto     andGate1 = graphPtr->addGate(Gates::GateAnd, "andGate1");
  auto     orGate   = graphPtr->addGate(Gates::GateOr, "orGate");
  auto     notGate  = graphPtr->addGate(Gates::GateNot, "notGate");
  auto     output   = graphPtr->addOutput("output");

  graphPtr->addEdge(input1, andGate1);
  graphPtr->addEdge(input2, andGate1);
  graphPtr->addEdge(andGate1, orGate);
  graphPtr->addEdge(input3, notGate);
  graphPtr->addEdge(notGate, orGate);
  graphPtr->addEdge(orGate, output);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("complex_logic_circuit");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/complex_logic_circuit.v";
  std::string paramsFilePath  = testDirectory + "/complex_logic_circuit.json";
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

TEST(Circuit, TestingVerilogAndParametersMultipleOutputs) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("MultipleOutputs");
  auto     input    = graphPtr->addInput("input");
  auto     notGate  = graphPtr->addGate(Gates::GateNot, "notGate");
  auto     output1  = graphPtr->addOutput("output1");
  auto     output2  = graphPtr->addOutput("output2");

  graphPtr->addEdge(input, notGate);
  graphPtr->addEdge(notGate, output1);
  graphPtr->addEdge(input, output2);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("multiple_outputs");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/multiple_outputs.v";
  std::string paramsFilePath  = testDirectory + "/multiple_outputs.json";
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

TEST(Circuit, TestingVerilogAndParametersFeedbackLoop) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("FeedbackLoop");
  auto     input    = graphPtr->addInput("input");
  auto     andGate  = graphPtr->addGate(Gates::GateAnd, "andGate");
  auto     output   = graphPtr->addOutput("output");
  graphPtr->addEdge(input, andGate);
  graphPtr->addEdge(andGate, output);
  graphPtr->addEdge(output, andGate);

  Circuit circuit(graphPtr, {});
  circuit.setCircuitName("feedback_loop");
  circuit.setPath(testDirectory);

  std::string verilogFilePath = testDirectory + "/feedback_loop.v";
  std::string paramsFilePath  = testDirectory + "/feedback_loop.json";
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
