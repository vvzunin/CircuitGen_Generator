#include <string>
#include <vector>

#include "baseStructures/graph/OrientedGraph.hpp"

#include <gtest/gtest.h>

// Test is on top because it needs to contain the graph_0
TEST(TestSetNameAndGetName, ReturnCorrectName) {
  OrientedGraph example1;
  OrientedGraph example2;
  EXPECT_EQ(example1.getName(), "graph_0");
  EXPECT_EQ(example2.getName(), "graph_1");

  // OrientedGraph example3(example1);
  // EXPECT_EQ(example3.getName(), "graph_2");

  // OrientedGraph example4 = example1;
  // EXPECT_EQ(example4.getName(), "graph_3");

  example1.setName("Cahnged");
  EXPECT_EQ(example1.getName(), "Cahnged");

  auto subGraph = example1.addSubGraph("SubGraph");
  EXPECT_EQ(subGraph->getName(), "SubGraph");
  subGraph->setName("Changed");
  EXPECT_EQ(subGraph->getName(), "Changed");
}

TEST(TestBaseSizeAndFullSizeAndSumFullSize, ReturnCorrectSize) {
  OrientedGraph example;
  EXPECT_EQ(example.baseSize(), 0);
  EXPECT_EQ(example.fullSize(), 0);
  EXPECT_EQ(example.sumFullSize(), 0);

  example.addGate(Gates::GateAnd, "Anything");
  example.addGate(Gates::GateNand, "Anything");
  example.addGate(Gates::GateOr, "Anything");
  example.addGate(Gates::GateNor, "Anything");
  example.addGate(Gates::GateXor, "Anything");
  example.addGate(Gates::GateXnor, "Anything");
  example.addGate(Gates::GateNot, "Anything");
  example.addGate(Gates::GateBuf, "Anything");
  example.addGate(Gates::GateDefault, "Anything");
  example.addInput("Anything");
  example.addOutput("Anything");
  example.addConst('x', "Anything");
  example.addGate(Gates::GateAnd, "Anything");
  example.addGate(Gates::GateNand, "Anything");
  example.addGate(Gates::GateOr, "Anything");
  example.addGate(Gates::GateNor, "Anything");
  example.addGate(Gates::GateXor, "Anything");
  example.addGate(Gates::GateXnor, "Anything");
  example.addGate(Gates::GateNot, "Anything");
  example.addGate(Gates::GateBuf, "Anything");
  example.addGate(Gates::GateDefault, "Anything");
  example.addInput("Anything");
  example.addOutput("Anything");
  example.addConst('x', "Anything");

  EXPECT_EQ(example.baseSize(), 18);
  EXPECT_EQ(example.fullSize(), 18);
  EXPECT_EQ(example.sumFullSize(), 24);

  auto subGraph1 = example.addSubGraph("SubGraph1");
  subGraph1->addGate(Gates::GateAnd, "Anything");
  subGraph1->addInput("Anything");
  subGraph1->addOutput("Anything");
  subGraph1->addConst('x', "Anything");
  EXPECT_EQ(example.baseSize(), 18);
  EXPECT_EQ(example.fullSize(), 19);
  // EXPECT_EQ(example.sumFullSize(), 28);

  auto subGraph2 = example.addSubGraph("SubGraph2");
  subGraph2->addGate(Gates::GateAnd, "Anything");
  subGraph2->addInput("Anything");
  subGraph2->addOutput("Anything");
  subGraph2->addConst('x', "Anything");
  EXPECT_EQ(example.baseSize(), 18);
  EXPECT_EQ(example.fullSize(), 20);
  // EXPECT_EQ(example.sumFullSize(), 32);
}

TEST(TestIsEmptyAndIsEmptyFull, ReturnCorrectSize) {
  OrientedGraph example1;
  OrientedGraph example2;
  OrientedGraph example3;
  OrientedGraph example4;
  OrientedGraph example5;
  EXPECT_EQ(example1.isEmpty(), true);
  EXPECT_EQ(example1.isEmptyFull(), true);
  EXPECT_EQ(example2.isEmpty(), true);
  EXPECT_EQ(example2.isEmptyFull(), true);

  example1.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example1.isEmpty(), false);
  EXPECT_EQ(example1.isEmptyFull(), false);

  example2.addInput("Anything");
  EXPECT_EQ(example2.isEmpty(), true);
  EXPECT_EQ(example2.isEmptyFull(), false);
  example2.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example2.isEmpty(), false);

  example3.addOutput("Anything");
  EXPECT_EQ(example3.isEmpty(), true);
  EXPECT_EQ(example3.isEmptyFull(), false);
  example3.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example3.isEmpty(), false);

  example4.addConst('x', "Anything");
  EXPECT_EQ(example4.isEmpty(), true);
  EXPECT_EQ(example4.isEmptyFull(), false);
  example4.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example4.isEmpty(), false);

  auto subGraph = example5.addSubGraph("SubGraph");
  EXPECT_EQ(example5.isEmpty(), true);
  // EXPECT_EQ(example5.isEmptyFull(), false);
  subGraph->addInput("Anything");
  EXPECT_EQ(example5.isEmpty(), true);
  EXPECT_EQ(example5.isEmptyFull(), false);
  subGraph->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example5.isEmpty(), false);
  EXPECT_EQ(example5.isEmptyFull(), false);
}

// needToUpdateLevel isn't realized
/*TEST(TestNeedToUpdateLevel, ReturnCorrectValue) {

}*/

// updateLevels is commented
/*TEST(TestUpdateLevelsAndGetMaxLevel, ReturnCorrectMaxLevel) {

}*/

TEST(TestSetBaseGraphAndGetBaseGraph, CorrectWork) {
  OrientedGraph example1;
  EXPECT_EQ(example1.getBaseGraph(), nullptr);

  auto subGraph1 = example1.addSubGraph("SubGraph");
  auto subGraph2 = example1.addSubGraph("SubGraph");
  EXPECT_EQ(example1.getBaseGraph(), nullptr);
  EXPECT_EQ(subGraph1->getBaseGraph(), &example1);
  EXPECT_EQ(subGraph2->getBaseGraph(), &example1);

  OrientedGraph example2;
  OrientedGraph example3;
  example2.setBaseGraph(&example3);
  EXPECT_EQ(example3.getBaseGraph(), nullptr);
  EXPECT_EQ(example2.getBaseGraph(), &example3);

  OrientedGraph example4;
  auto          subGraph3 = example4.addSubGraph("SubGraph");
  example4.setBaseGraph(&(*subGraph3));
  EXPECT_EQ(example4.getBaseGraph(), &(*subGraph3));
  EXPECT_EQ(subGraph3->getBaseGraph(), &example4);
}

TEST(TestGetEdgesCount, ReturnCorrectCount) {
  OrientedGraph example1;
  auto          input1  = example1.addInput("Input1");
  auto          input2  = example1.addInput("Input2");
  auto          gate1   = example1.addGate(Gates::GateAnd, "And");
  auto          output1 = example1.addOutput("Output");
  EXPECT_EQ(example1.getEdgesCount(), 0);

  example1.addEdge(gate1, output1);
  EXPECT_EQ(example1.getEdgesCount(), 1);

  example1.addEdges({input1, input2}, gate1);
  EXPECT_EQ(example1.getEdgesCount(), 3);

  // there is no check for edge being already exist
  // example1.addEdge(gate, output);
  // EXPECT_EQ(example1.getEdgesCount(), 3);
  // EXPECT_THROW()

  // there is no check for edges being already exist
  // example1.addEdges({input1, input2}, gate);
  // EXPECT_EQ(example1.getEdgesCount(), 3);
  // EXPECT_THROW()

  OrientedGraph example2;
  auto          gate2 = example2.addGate(Gates::GateAnd, "And");
  auto          gate3 = example2.addGate(Gates::GateAnd, "And");

  // There is no check to the same objects in Edge
  // example2.addEdge(gate2, gate2);
  // EXPECT_EQ(example2.getEdgesCount(), 0);
  // EXPECT_TRHOW();
  // example2.addEdges({gate2, gate2, gate3, gate3}, gate2);
  // EXPECT_EQ(example2.getEdgesCount(), 1);
  // EXPECT_TRHOW();
}

TEST(TestGetSubGraphs, ReturnCorrectSubGraphs) {
  OrientedGraph example;

  // Is this test case correct?
  // auto          subVector1 = example.getSubGraphs();
  // EXPECT_EQ(subVector1.size(), 0);
  // EXPECT_EQ(subVector1[0], nullptr);
  // EXPECT_THROW();

  auto          subGraph1  = example.addSubGraph("SubGraph1");
  auto          subVector2 = example.getSubGraphs();
  EXPECT_EQ(subVector2[0], subGraph1);

  auto subGraph2  = example.addSubGraph("SubGraph2");
  auto subGraph3  = subGraph1->addSubGraph("SubGraph2");
  auto subVector3 = example.getSubGraphs();
  EXPECT_EQ(subVector3.size(), 2);
  EXPECT_EQ(subVector3[0], subGraph1);
  EXPECT_EQ(subVector3[1], subGraph2);
}

TEST(TestGetVerticeByIndex, ReturnCorrectType) {
  OrientedGraph example;
  example.addGate(Gates::GateAnd, "Anything");
  example.addGate(Gates::GateNand, "Anything");
  example.addGate(Gates::GateOr, "Anything");
  example.addGate(Gates::GateNor, "Anything");
  example.addGate(Gates::GateXor, "Anything");
  example.addGate(Gates::GateXnor, "Anything");
  example.addGate(Gates::GateNot, "Anything");
  example.addGate(Gates::GateBuf, "Anything");
  example.addGate(Gates::GateDefault, "Anything");
  example.addInput("Anything");
  example.addOutput("Anything");
  example.addConst('x', "Anything");

  EXPECT_EQ(example.getVerticeByIndex(0)->getType(), VertexTypes::input);
  EXPECT_EQ(example.getVerticeByIndex(1)->getType(), VertexTypes::constant);
  EXPECT_EQ(example.getVerticeByIndex(2)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(3)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(4)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(5)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(6)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(7)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(8)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(9)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(10)->getType(), VertexTypes::gate);
  EXPECT_EQ(example.getVerticeByIndex(11)->getType(), VertexTypes::output);
}

TEST(TestGetVerticeByIndex, ReturnCorrectGate) {
  OrientedGraph example;
  example.addGate(Gates::GateAnd, "Anything");
  example.addGate(Gates::GateNand, "Anything");
  example.addGate(Gates::GateOr, "Anything");
  example.addGate(Gates::GateNor, "Anything");
  example.addGate(Gates::GateXor, "Anything");
  example.addGate(Gates::GateXnor, "Anything");
  example.addGate(Gates::GateNot, "Anything");
  example.addGate(Gates::GateBuf, "Anything");
  example.addGate(Gates::GateDefault, "Anything");

  EXPECT_EQ(example.getVerticeByIndex(0)->getGate(), Gates::GateAnd);
  EXPECT_EQ(example.getVerticeByIndex(1)->getGate(), Gates::GateNand);
  EXPECT_EQ(example.getVerticeByIndex(2)->getGate(), Gates::GateOr);
  EXPECT_EQ(example.getVerticeByIndex(3)->getGate(), Gates::GateNor);
  EXPECT_EQ(example.getVerticeByIndex(4)->getGate(), Gates::GateXor);
  EXPECT_EQ(example.getVerticeByIndex(5)->getGate(), Gates::GateXnor);
  EXPECT_EQ(example.getVerticeByIndex(6)->getGate(), Gates::GateNot);
  EXPECT_EQ(example.getVerticeByIndex(7)->getGate(), Gates::GateBuf);
  EXPECT_EQ(example.getVerticeByIndex(8)->getGate(), Gates::GateDefault);
}

TEST(TestGetVerticeByIndex, ThrowExceptionWhenWrongIndex) {
  OrientedGraph example;

  EXPECT_THROW(example.getVerticeByIndex(0), std::invalid_argument);
  example.addGate(Gates::GateAnd, "Anything");
  EXPECT_THROW(example.getVerticeByIndex(1), std::invalid_argument);
}
