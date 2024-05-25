#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "baseStructures/graph/OrientedGraph.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"
/*
  Need to add toVerilogTest, setCurrentParentTest,
    resetCountersTest, getGraphInstanceTest
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
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr2 = std::make_shared<OrientedGraph>();

  EXPECT_EQ(graphPtr1->getName(), "graph_0");
  EXPECT_EQ(graphPtr2->getName(), "graph_1");

  GraphPtr graphPtr3 = std::make_shared<OrientedGraph>(*graphPtr1);
  EXPECT_EQ(graphPtr3->getName(), "graph_0");

  GraphPtr graphPtr4 = std::make_shared<OrientedGraph>();
  graphPtr4          = graphPtr1;
  EXPECT_EQ(graphPtr4->getName(), "graph_0");

  graphPtr1->setName("Changed");
  EXPECT_EQ(graphPtr1->getName(), "Changed");
}

TEST(TestBaseSizeAndFullSizeAndSumFullSize, ReturnCorrectSize) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  EXPECT_EQ(graphPtr->baseSize(), 0);
  EXPECT_EQ(graphPtr->fullSize(), 0);
  EXPECT_EQ(graphPtr->sumFullSize(), 0);

  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addGate(Gates::GateXnor, "Anything");
  graphPtr->addGate(Gates::GateNot, "Anything");
  graphPtr->addGate(Gates::GateBuf, "Anything");
  graphPtr->addGate(Gates::GateDefault, "Anything");
  graphPtr->addInput("Anything");
  graphPtr->addOutput("Anything");
  graphPtr->addConst('x', "Anything");
  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addGate(Gates::GateXnor, "Anything");
  graphPtr->addGate(Gates::GateNot, "Anything");
  graphPtr->addGate(Gates::GateBuf, "Anything");
  graphPtr->addGate(Gates::GateDefault, "Anything");
  graphPtr->addInput("Anything");
  graphPtr->addOutput("Anything");
  graphPtr->addConst('x', "Anything");

  EXPECT_EQ(graphPtr->baseSize(), 18);
  EXPECT_EQ(graphPtr->fullSize(), 18);
  EXPECT_EQ(graphPtr->sumFullSize(), 24);

  GraphPtr subGraphPtr1 = std::make_shared<OrientedGraph>();
  subGraphPtr1->addGate(Gates::GateAnd, "Anything");
  subGraphPtr1->addInput("Anything");
  subGraphPtr1->addOutput("Anything");
  subGraphPtr1->addConst('x', "Anything");
  graphPtr->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );

  EXPECT_EQ(graphPtr->baseSize(), 18);
  EXPECT_EQ(graphPtr->fullSize(), 19);
  // Does sumFullSize() return sum from subGraphs too
  // EXPECT_EQ(graphPtr->sumFullSize(), 28);

  GraphPtr subGraphPtr2 = std::make_shared<OrientedGraph>("");
  subGraphPtr2->addGate(Gates::GateAnd, "Anything");
  subGraphPtr2->addInput("Anything");
  subGraphPtr2->addOutput("Anything");
  subGraphPtr2->addConst('x', "Anything");
  graphPtr->addSubGraph(
      subGraphPtr2, subGraphPtr2->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(graphPtr->baseSize(), 18);
  EXPECT_EQ(graphPtr->fullSize(), 20);
  // Does sumFullSize() return sum from subGraphs too
  // EXPECT_EQ(graph.sumFullSize(), 32);
}

TEST(TestIsEmptyAndIsEmptyFull, ReturnCorrectSize) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr2 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr3 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr4 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr5 = std::make_shared<OrientedGraph>();

  EXPECT_EQ(graphPtr1->isEmpty(), true);
  EXPECT_EQ(graphPtr1->isEmptyFull(), true);
  EXPECT_EQ(graphPtr2->isEmpty(), true);
  EXPECT_EQ(graphPtr2->isEmptyFull(), true);

  graphPtr1->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr1->isEmpty(), false);
  EXPECT_EQ(graphPtr1->isEmptyFull(), false);

  graphPtr2->addInput("Anything");
  EXPECT_EQ(graphPtr2->isEmpty(), true);
  EXPECT_EQ(graphPtr2->isEmptyFull(), false);
  graphPtr2->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr2->isEmpty(), false);

  graphPtr3->addOutput("Anything");
  EXPECT_EQ(graphPtr3->isEmpty(), true);
  EXPECT_EQ(graphPtr3->isEmptyFull(), false);
  graphPtr3->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr3->isEmpty(), false);

  graphPtr4->addConst('x', "Anything");
  EXPECT_EQ(graphPtr4->isEmpty(), true);
  EXPECT_EQ(graphPtr4->isEmptyFull(), false);
  graphPtr4->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr4->isEmpty(), false);

  GraphPtr subGraphPtr = std::make_shared<OrientedGraph>();
  graphPtr5->addSubGraph(
      subGraphPtr, subGraphPtr->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(graphPtr5->isEmpty(), true);
  // Does graph with empty subGraph isEmptyFull?
  // EXPECT_EQ(graph5.isEmptyFull(), false);
  subGraphPtr->addInput("Anything");
  EXPECT_EQ(graphPtr5->isEmpty(), true);
  EXPECT_EQ(graphPtr5->isEmptyFull(), false);
  subGraphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr5->isEmpty(), false);
  EXPECT_EQ(graphPtr5->isEmptyFull(), false);
}

// needToUpdateLevel isn't realized
/*TEST(TestNeedToUpdateLevel, ReturnCorrectValue) {

}*/

// updateLevels is commented
/*TEST(TestUpdateLevelsAndGetMaxLevel, ReturnCorrectMaxLevel) {

}*/

TEST(TestAddParentGraphAndGetParentGraph, CorrectWork) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  EXPECT_EQ(*(graphPtr1->getParentGraphs().begin()), nullptr);

  GraphPtr subGraphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr subGraphPtr2 = std::make_shared<OrientedGraph>();
  graphPtr1->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );
  graphPtr1->addSubGraph(
      subGraphPtr2, subGraphPtr2->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(*(graphPtr1->getParentGraphs().begin()), nullptr);
  EXPECT_EQ(*(subGraphPtr1->getParentGraphs().begin()), graphPtr1);
  EXPECT_EQ(*(subGraphPtr2->getParentGraphs().begin()), graphPtr1);
}

TEST(TestGetEdgesCount, ReturnCorrectCount) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  auto     input1    = graphPtr1->addInput("Input1");
  auto     input2    = graphPtr1->addInput("Input2");
  auto     gate1     = graphPtr1->addGate(Gates::GateAnd, "And");
  auto     output1   = graphPtr1->addOutput("Output");
  EXPECT_EQ(graphPtr1->getEdgesCount(), 0);

  graphPtr1->addEdge(gate1, output1);
  EXPECT_EQ(graphPtr1->getEdgesCount(), 1);

  graphPtr1->addEdges({input1, input2}, gate1);
  EXPECT_EQ(graphPtr1->getEdgesCount(), 3);

  // there is no check for edge being already exist
  // graph1.addEdge(gate, output);
  // EXPECT_EQ(graph1.getEdgesCount(), 3);
  // EXPECT_THROW()

  // there is no check for edges being already exist
  // graph1.addEdges({input1, input2}, gate);
  // EXPECT_EQ(graph1.getEdgesCount(), 3);
  // EXPECT_THROW()

  GraphPtr graphPtr2 = std::make_shared<OrientedGraph>();
  auto     gate2     = graphPtr2->addGate(Gates::GateAnd, "And");
  auto     gate3     = graphPtr2->addGate(Gates::GateAnd, "And");

  // There is no check to the same objects in Edge
  // graph2.addEdge(gate2, gate2);
  // EXPECT_EQ(graph2.getEdgesCount(), 0);
  // EXPECT_TRHOW();
  // graph2.addEdges({gate2, gate2, gate3, gate3}, gate2);
  // EXPECT_EQ(graph2.getEdgesCount(), 1);
  // EXPECT_TRHOW();
}

TEST(TestGetSubGraphs, ReturnCorrectSubGraphs) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  EXPECT_EQ(graphPtr->getSubGraphs().size(), 0);

  GraphPtr subGraphPtr1 = std::make_shared<OrientedGraph>();
  graphPtr->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(graphPtr->getSubGraphs()[0], subGraphPtr1);

  GraphPtr subGraphPtr2 = std::make_shared<OrientedGraph>();
  GraphPtr subGraphPtr3 = std::make_shared<OrientedGraph>();
  graphPtr->addSubGraph(
      subGraphPtr2, subGraphPtr2->getVerticesByType(VertexTypes::input)
  );
  subGraphPtr3->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(graphPtr->getSubGraphs().size(), 2);
  EXPECT_EQ(graphPtr->getSubGraphs()[0], subGraphPtr1);
  EXPECT_EQ(graphPtr->getSubGraphs()[1], subGraphPtr2);
}

TEST(TestGetBaseVertexes, ReturnCorrectVertexes) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::input].size(), 0);

  // without subGraph
  auto gate1 = graphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::gate].size(), 1);
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::gate][0], gate1);

  auto input1 = graphPtr->addInput("Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::input].size(), 1);
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::input][0], input1);

  auto output1 = graphPtr->addOutput("Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::output].size(), 1);
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::output][0], output1);

  auto const1 = graphPtr->addConst('x', "Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::constant].size(), 1);
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::constant][0], const1);

  // with subGraph
  GraphPtr subGraphPtr = std::make_shared<OrientedGraph>();
  graphPtr->addSubGraph(
      subGraphPtr, subGraphPtr->getVerticesByType(VertexTypes::input)
  );
  subGraphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::gate].size(), 1);

  subGraphPtr->addInput("Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::input].size(), 1);

  subGraphPtr->addOutput("Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::output].size(), 1);

  subGraphPtr->addConst('x', "Anything");
  EXPECT_EQ(graphPtr->getBaseVertexes()[VertexTypes::constant].size(), 1);
}

TEST(TestGetVerticeByIndex, ReturnCorrectType) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addGate(Gates::GateXnor, "Anything");
  graphPtr->addGate(Gates::GateNot, "Anything");
  graphPtr->addGate(Gates::GateBuf, "Anything");
  graphPtr->addGate(Gates::GateDefault, "Anything");
  graphPtr->addInput("Anything");
  graphPtr->addOutput("Anything");
  graphPtr->addConst('x', "Anything");

  EXPECT_EQ(graphPtr->getVerticeByIndex(0)->getType(), VertexTypes::input);
  EXPECT_EQ(graphPtr->getVerticeByIndex(1)->getType(), VertexTypes::constant);
  EXPECT_EQ(graphPtr->getVerticeByIndex(2)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(3)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(4)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(5)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(6)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(7)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(8)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(9)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(10)->getType(), VertexTypes::gate);
  EXPECT_EQ(graphPtr->getVerticeByIndex(11)->getType(), VertexTypes::output);
}

TEST(TestGetVerticeByIndex, ReturnCorrectGate) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addGate(Gates::GateXnor, "Anything");
  graphPtr->addGate(Gates::GateNot, "Anything");
  graphPtr->addGate(Gates::GateBuf, "Anything");
  graphPtr->addGate(Gates::GateDefault, "Anything");

  EXPECT_EQ(graphPtr->getVerticeByIndex(0)->getGate(), Gates::GateAnd);
  EXPECT_EQ(graphPtr->getVerticeByIndex(1)->getGate(), Gates::GateNand);
  EXPECT_EQ(graphPtr->getVerticeByIndex(2)->getGate(), Gates::GateOr);
  EXPECT_EQ(graphPtr->getVerticeByIndex(3)->getGate(), Gates::GateNor);
  EXPECT_EQ(graphPtr->getVerticeByIndex(4)->getGate(), Gates::GateXor);
  EXPECT_EQ(graphPtr->getVerticeByIndex(5)->getGate(), Gates::GateXnor);
  EXPECT_EQ(graphPtr->getVerticeByIndex(6)->getGate(), Gates::GateNot);
  EXPECT_EQ(graphPtr->getVerticeByIndex(7)->getGate(), Gates::GateBuf);
  EXPECT_EQ(graphPtr->getVerticeByIndex(8)->getGate(), Gates::GateDefault);
}

TEST(TestGetVerticeByIndex, ThrowExceptionWhenWrongIndex) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();

  EXPECT_THROW(graphPtr->getVerticeByIndex(0), std::invalid_argument);
  graphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_THROW(graphPtr->getVerticeByIndex(1), std::invalid_argument);
}
// TEST(TestGetVerticesByLevel, ReturnCorrectVertices) {
//   // OrientedGraph graph;
//   // EXPECT_EQ(graph.getVerticesByLevel(0).size(), 0);

//   // Do not work
//   // auto          gate = graph.addGate(Gates::GateAnd, "Anything");
//   // EXPECT_EQ(gate->getLevel(), 0);
//   // EXPECT_EQ(graph.getVerticesByLevel(0)[0]->getType(), VertexTypes::gate);
// }

TEST(TestGetVerticesByName, ReturnCorrectVertices) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();

  // Without subGraph
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 0);

  graphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 1);
  EXPECT_EQ(
      graphPtr->getVerticesByName("Anything")[0]->getGate(), Gates::GateAnd
  );

  graphPtr->addInput("Anything");
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 2);
  EXPECT_EQ(
      graphPtr->getVerticesByName("Anything")[0]->getType(), VertexTypes::input
  );
  EXPECT_EQ(
      graphPtr->getVerticesByName("Anything")[1]->getGate(), Gates::GateAnd
  );

  graphPtr->addOutput("Anything");
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 3);
  // Should VertexTypes::output be in the end or be after VertexTypes::input?
  // EXPECT_EQ(graphPtr->getVerticesByName("Anything")[2]->getType(),
  // VertexTypes::output);

  graphPtr->addConst('x', "Anything");
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 4);
  // What should return at first VertexTypes::constant or VertexTypes::output?
  // EXPECT_EQ(graphPtr->getVerticesByName("Anything")[1]->getType(),
  // VertexTypes::constant);

  // With subGraph
  GraphPtr subGraphPtr = std::make_shared<OrientedGraph>();

  graphPtr->addSubGraph(
      subGraphPtr, subGraphPtr->getVerticesByType(VertexTypes::input)
  );
  subGraphPtr->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr->getVerticesByName("Anything").size(), 4);
  EXPECT_EQ(graphPtr->getVerticesByName("Anything", true).size(), 5);
  EXPECT_EQ(
      graphPtr->getVerticesByName("Anything", true)[4]->getGate(),
      Gates::GateAnd
  );
}

TEST(TestToGraphMLStringReturn, ReturnCorrectStringWhenGraphIsEmpty) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>("Graph1");
  EXPECT_EQ(graphPtr->isEmptyFull(), true);
  EXPECT_EQ(
      graphPtr->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n  "
      "<graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "  </graph>\n</graphml>\n"
  );
}

TEST(TestToGraphMLStringReturn, ReturnCorrectStringWhenThereAreNodes) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("Graph1");
  graphPtr1->addGate(Gates::GateAnd, "gate1");
  EXPECT_EQ(
      graphPtr1->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n  "
      "<graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "    <node id=\"gate1\">\n"
      "      <data key=\"d0\">and</data>\n"
      "    </node>\n  "
      "</graph>\n"
      "</graphml>\n"
  );

  graphPtr1->addGate(Gates::GateNot, "gate2");
  EXPECT_EQ(
      graphPtr1->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n"
      "  <graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "    <node id=\"gate1\">\n"
      "      <data key=\"d0\">and</data>\n"
      "    </node>\n"
      "    <node id=\"gate2\">\n"
      "      <data key=\"d0\">not</data>\n"
      "    </node>\n"
      "  </graph>\n"
      "</graphml>\n"
  );
}

TEST(TestToGraphMLStringReturn, ReturnCorrectStringWhenThereAreSubGraphs) {
  GraphPtr graphPtr1    = std::make_shared<OrientedGraph>("Graph1");
  GraphPtr subGraphPtr1 = std::make_shared<OrientedGraph>("SubGraph1");
  graphPtr1->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );
  EXPECT_EQ(
      graphPtr1->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n"
      "  <graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "    <node id=\"SubGraph1_subgraph\">\n"
      "      <data key=\"d0\">graph</data>      <graph id=\"SubGraph1\" "
      "edgedefault=\"directed\">\n"
      "      </graph>\n"
      "    </node>\n"
      "  </graph>\n"
      "</graphml>\n"
  );

  subGraphPtr1->addGate(Gates::GateAnd, "gate1");
  EXPECT_EQ(
      graphPtr1->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n"
      "  <graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "    <node id=\"SubGraph1_subgraph\">\n"
      "      <data key=\"d0\">graph</data>      <graph id=\"SubGraph1\" "
      "edgedefault=\"directed\">\n"
      "            <node id=\"gate1\">\n"
      "          <data key=\"d0\">and</data>\n"
      "        </node>\n"
      "  </graph>\n"
      "    </node>\n"
      "  </graph>\n"
      "</graphml>\n"
  );
}

TEST(TestToGraphMLStringReturn, ReturnCorrectStringWhenThereAreSubEdges) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("Graph1");
  auto     gate1     = graphPtr1->addGate(Gates::GateAnd, "gate1");
  auto     input1    = graphPtr1->addInput("input1");
  auto     input2    = graphPtr1->addInput("input2");

  graphPtr1->addEdges({input1, input2}, gate1);
  EXPECT_EQ(
      graphPtr1->toGraphML(0),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"d0\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n"
      "  <graph id=\"Graph1\" edgedefault=\"directed\">\n"
      "    <node id=\"input1\">\n"
      "      <data key=\"d0\">input</data>\n"
      "    </node>\n"
      "    <node id=\"input2\">\n"
      "      <data key=\"d0\">input</data>\n"
      "    </node>\n"
      "    <node id=\"gate1\">\n"
      "      <data key=\"d0\">and</data>\n"
      "    </node>\n"
      "    <source=\"input1\" target=\"gate1\"/>\n"
      "    <source=\"input2\" target=\"gate1\"/>\n"
      "  </graph>\n"
      "</graphml>\n"
  );
}

TEST(TestToGraphMLBoolReturn, CorrectWriteToFile) {
  std::string   filename = "ToGraphMLTest.txt";
  std::ofstream outF(filename);
  GraphPtr      graphPtr1    = std::make_shared<OrientedGraph>("Graph1");
  auto          gate1        = graphPtr1->addGate(Gates::GateAnd, "gate1");
  auto          input1       = graphPtr1->addInput("input1");
  auto          input2       = graphPtr1->addInput("input2");
  GraphPtr      subGraphPtr1 = std::make_shared<OrientedGraph>("SubGraph1");
  graphPtr1->addSubGraph(
      subGraphPtr1, subGraphPtr1->getVerticesByType(VertexTypes::input)
  );
  graphPtr1->addEdges({input1, input2}, gate1);
  subGraphPtr1->addGate(Gates::GateAnd, "gate1");
  EXPECT_EQ(graphPtr1->toGraphML(outF), true);

  std::ifstream inF(filename);
  outF.close();
  std::ostringstream contentStream;
  contentStream << inF.rdbuf();
  std::string stringF = contentStream.str();
  inF.close();
  EXPECT_EQ(stringF, graphPtr1->toGraphML(0));
}

TEST(TestCalculateHash, GraphsWithTheSameStructureHaveEqualHash) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr2 = std::make_shared<OrientedGraph>();

  EXPECT_EQ(graphPtr1->calculateHash(), graphPtr1->calculateHash(true));
  EXPECT_EQ(graphPtr1->calculateHash(), graphPtr2->calculateHash());

  graphPtr1->addGate(Gates::GateAnd, "Anything");
  graphPtr2->addGate(Gates::GateAnd, "Anything");
  EXPECT_EQ(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));

  graphPtr1->addGate(Gates::GateNand, "Anything");
  // Should hash be not the same if there are differences in Gates
  // EXPECT_NE(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));

  graphPtr1->addInput("Anything");
  EXPECT_NE(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));
  graphPtr2->addInput("Anything");
  EXPECT_EQ(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));

  graphPtr1->addOutput("Anything");
  // Should hash be not the same if there are differences in Outputs
  // EXPECT_NE(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));
  graphPtr2->addOutput("Anything");
  EXPECT_EQ(graphPtr1->calculateHash(true), graphPtr2->calculateHash(true));
}

TEST(TestGetGatesCount, ReturnCorrectGates) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  EXPECT_EQ(graphPtr->getGatesCount().size(), 8);

  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addGate(Gates::GateXnor, "Anything");
  graphPtr->addGate(Gates::GateNot, "Anything");
  graphPtr->addGate(Gates::GateBuf, "Anything");
  graphPtr->addGate(Gates::GateDefault, "Anything");
  graphPtr->addInput("Anything");
  graphPtr->addOutput("Anything");
  graphPtr->addConst('x', "Anything");
  EXPECT_EQ(graphPtr->getGatesCount().size(), 9);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateAnd], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNand], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateOr], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNor], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateXor], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateXnor], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNot], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateBuf], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateDefault], 1);

  graphPtr->addGate(Gates::GateAnd, "Anything");
  graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addGate(Gates::GateNor, "Anything");
  graphPtr->addGate(Gates::GateXor, "Anything");
  graphPtr->addInput("Anything");
  graphPtr->addOutput("Anything");
  graphPtr->addConst('x', "Anything");
  EXPECT_EQ(graphPtr->getGatesCount().size(), 9);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateAnd], 2);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNand], 2);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateOr], 2);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNor], 2);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateXor], 2);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateXnor], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateNot], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateBuf], 1);
  EXPECT_EQ(graphPtr->getGatesCount()[Gates::GateDefault], 1);
}

TEST(TestGetEdgesGatesCount, ReturnCorrectGates) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();

  EXPECT_EQ(graphPtr->getEdgesGatesCount().size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateNand].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateOr].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateNor].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateXor].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateXnor].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateNot].size(), 8);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateBuf].size(), 8);

  auto gate1 = graphPtr->addGate(Gates::GateAnd, "Anything");
  auto gate2 = graphPtr->addGate(Gates::GateNand, "Anything");
  graphPtr->addEdge(gate1, gate2);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateNand], 1);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateOr], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateAnd], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateNor], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateXor], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateXnor], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateNot], 0);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateBuf], 0);

  auto gate3 = graphPtr->addGate(Gates::GateNand, "Anything");
  auto gate4 = graphPtr->addGate(Gates::GateOr, "Anything");
  graphPtr->addEdges({gate3, gate4}, gate1);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateNand][Gates::GateAnd], 1);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateOr][Gates::GateAnd], 1);
  EXPECT_EQ(graphPtr->getEdgesGatesCount()[Gates::GateAnd][Gates::GateNand], 1);
}
