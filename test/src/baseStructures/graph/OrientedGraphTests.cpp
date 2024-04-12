#include <string>
#include <vector>

#include "baseStructures/graph/OrientedGraph.hpp"

#include <gtest/gtest.h>
/*
  Need to add toGrapMlTest, toVerilogTest
  Need to realize getVerticesByLevel, needToUpdateLevel, updateLevels,
  getMaxLevel

  Questions in:
    TestSetNameAndGetName
    TestIsEmptyAndIsEmptyFull
    TestGetEdgesCount
    TestGetVerticesByName
    TestCalculateHash
*/

// Test is on top because it needs to contain the graph_0
TEST(TestSetNameAndGetName, ReturnCorrectName) {
  OrientedGraph example1;
  OrientedGraph example2;
  EXPECT_EQ(example1.getName(), "graph_0");
  EXPECT_EQ(example2.getName(), "graph_1");

  // Should be names of copying graph and new grah the same
  // OrientedGraph example3(example1);
  // EXPECT_EQ(example3.getName(), "graph_2");

  // Should be names of copying graph and new grah the same
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
  // Does sumFullSize() return sum from subGraphs too?
  // EXPECT_EQ(example.sumFullSize(), 28);

  auto subGraph2 = example.addSubGraph("SubGraph2");
  subGraph2->addGate(Gates::GateAnd, "Anything");
  subGraph2->addInput("Anything");
  subGraph2->addOutput("Anything");
  subGraph2->addConst('x', "Anything");
  EXPECT_EQ(example.baseSize(), 18);
  EXPECT_EQ(example.fullSize(), 20);
  // Does sumFullSize() return sum from subGraphs too?
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
  // Does graph with empty subGraph isEmptyFull?
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
  auto          subVector1 = example.getSubGraphs();
  EXPECT_EQ(subVector1.size(), 0);

  auto subGraph1  = example.addSubGraph("SubGraph1");
  auto subVector2 = example.getSubGraphs();
  EXPECT_EQ(subVector2[0], subGraph1);

  auto subGraph2  = example.addSubGraph("SubGraph2");
  auto subGraph3  = subGraph1->addSubGraph("SubGraph2");
  auto subVector3 = example.getSubGraphs();
  EXPECT_EQ(subVector3.size(), 2);
  EXPECT_EQ(subVector3[0], subGraph1);
  EXPECT_EQ(subVector3[1], subGraph2);
}

TEST(TestGetBaseVertexes, ReturnCorrectVertexes) {
  OrientedGraph example;
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::input].size(), 0);

  // without subGraph
  auto gate1 = example.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::gate].size(), 1);
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::gate][0], gate1);

  auto input1 = example.addInput("Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::input].size(), 1);
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::input][0], input1);

  auto output1 = example.addOutput("Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::output].size(), 1);
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::output][0], output1);

  auto const1 = example.addConst('x', "Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::constant].size(), 1);
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::constant][0], const1);

  // with subGraph
  auto subGraph = example.addSubGraph("Anyhting");
  subGraph->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::gate].size(), 1);

  subGraph->addInput("Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::input].size(), 1);

  subGraph->addOutput("Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::output].size(), 1);

  subGraph->addConst('x', "Anything");
  EXPECT_EQ(example.getBaseVertexes()[VertexTypes::constant].size(), 1);
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

TEST(TestGetVerticesByLevel, ReturnCorrectVertices) {
  // OrientedGraph example;
  // EXPECT_EQ(example.getVerticesByLevel(0).size(), 0);

  // Do not work
  // auto          gate = example.addGate(Gates::GateAnd, "Anything");
  // EXPECT_EQ(gate->getLevel(), 0);
  // EXPECT_EQ(example.getVerticesByLevel(0)[0]->getType(), VertexTypes::gate);
}

TEST(TestGetVerticesByName, ReturnCorrectVertices) {
  OrientedGraph example;
  // Without subGraph
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 0);

  example.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 1);
  EXPECT_EQ(
      example.getVerticesByName("Anything")[0]->getGate(), Gates::GateAnd
  );

  example.addInput("Anything");
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 2);
  EXPECT_EQ(
      example.getVerticesByName("Anything")[0]->getType(), VertexTypes::input
  );
  EXPECT_EQ(
      example.getVerticesByName("Anything")[1]->getGate(), Gates::GateAnd
  );

  example.addOutput("Anything");
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 3);
  // Should VertexTypes::output be in the end or be after VertexTypes::input?
  // EXPECT_EQ(
  //    example.getVerticesByName("Anything")[2]->getType(), VertexTypes::output
  //);

  example.addConst('x', "Anything");
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 4);
  // What should return at first VertexTypes::constant or VertexTypes::output?
  // EXPECT_EQ(
  //    example.getVerticesByName("Anything")[1]->getType(),
  //    VertexTypes::constant
  //);

  // With subGraph
  auto subGraph = example.addSubGraph("Anything");
  subGraph->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(example.getVerticesByName("Anything").size(), 4);
  EXPECT_EQ(example.getVerticesByName("Anything", true).size(), 5);
  EXPECT_EQ(
      example.getVerticesByName("Anything", true)[4]->getGate(), Gates::GateAnd
  );
}

TEST(TestCalculateHash, GraphsWithTheSameStrutureHaveEqualHash) {
  OrientedGraph graph1;
  OrientedGraph graph2;

  EXPECT_EQ(graph1.calculateHash(), graph1.calculateHash(true));
  EXPECT_EQ(graph1.calculateHash(), graph2.calculateHash());

  graph1.addGate(Gates::GateAnd, "Anything");
  graph2.addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graph1.calculateHash(true), graph2.calculateHash(true));

  graph1.addGate(Gates::GateNand, "Anything");
  // Should hash be not the same if there are differenece in Gates
  // EXPECT_NE(graph1.calculateHash(true), graph2.calculateHash(true));

  graph1.addInput("Anything");
  EXPECT_NE(graph1.calculateHash(true), graph2.calculateHash(true));
  graph2.addInput("Anything");
  EXPECT_EQ(graph1.calculateHash(true), graph2.calculateHash(true));

  graph1.addOutput("Anything");
  // Should hash be not the same if there are differenece in Outputs
  // EXPECT_NE(graph1.calculateHash(true), graph2.calculateHash(true));
  graph2.addOutput("Anything");
  EXPECT_EQ(graph1.calculateHash(true), graph2.calculateHash(true));
}

TEST(TestGetGatesCount, ReturnCorrectGates) {
  OrientedGraph example;
  EXPECT_EQ(example.getGatesCount().size(), 8);

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
  EXPECT_EQ(example.getGatesCount().size(), 9);
  EXPECT_EQ(example.getGatesCount()[Gates::GateAnd], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNand], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateOr], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNor], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateXor], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateXnor], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNot], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateBuf], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateDefault], 1);

  example.addGate(Gates::GateAnd, "Anything");
  example.addGate(Gates::GateNand, "Anything");
  example.addGate(Gates::GateOr, "Anything");
  example.addGate(Gates::GateNor, "Anything");
  example.addGate(Gates::GateXor, "Anything");
  example.addInput("Anything");
  example.addOutput("Anything");
  example.addConst('x', "Anything");
  EXPECT_EQ(example.getGatesCount().size(), 9);
  EXPECT_EQ(example.getGatesCount()[Gates::GateAnd], 2);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNand], 2);
  EXPECT_EQ(example.getGatesCount()[Gates::GateOr], 2);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNor], 2);
  EXPECT_EQ(example.getGatesCount()[Gates::GateXor], 2);
  EXPECT_EQ(example.getGatesCount()[Gates::GateXnor], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateNot], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateBuf], 1);
  EXPECT_EQ(example.getGatesCount()[Gates::GateDefault], 1);
}

TEST(TestGetEdgesGatesCount, ReturnCorrectGates) {
  OrientedGraph example;
  EXPECT_EQ(example.getEdgesGatesCount().size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateNand].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateOr].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateNor].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateXor].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateXnor].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateNot].size(), 8);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateBuf].size(), 8);

  auto gate1 = example.addGate(Gates::GateAnd, "Anything");
  auto gate2 = example.addGate(Gates::GateNand, "Anything");
  example.addEdge(gate1, gate2);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateNand], 1);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateOr], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateAnd], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateNor], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateXor], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateXnor], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateNot], 0);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateBuf], 0);

  auto gate3 = example.addGate(Gates::GateNand, "Anything");
  auto gate4 = example.addGate(Gates::GateOr, "Anything");
  example.addEdges({gate3, gate4}, gate1);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateNand][Gates::GateAnd], 1);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateOr][Gates::GateAnd], 1);
  EXPECT_EQ(example.getEdgesGatesCount()[Gates::GateAnd][Gates::GateNand], 1);
}
