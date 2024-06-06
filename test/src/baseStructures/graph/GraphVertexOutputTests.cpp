#include "baseStructures/graph/GraphVertex.hpp"

#include <CircuitGenGenerator/OrientedGraph.hpp>
#include <gtest/gtest.h>

/*
  Need to remake RemoveVertexToOutConnections
*/

TEST(TestConstructorWithoutIName, WithoutDefaultInputParametrs) {
  GraphVertexOutput output;
  std::string       graphNum = std::to_string(0);
  EXPECT_EQ(output.getType(), VertexTypes::output);
  EXPECT_EQ(output.getTypeName(), "output");
  EXPECT_EQ(output.getName(), "output_" + graphNum);
  EXPECT_EQ(output.getLevel(), 0);
  EXPECT_EQ(output.getValue(), 'x');
  EXPECT_EQ(output.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}

TEST(TestConstructorWithoutIName, WithDefaultInputParametrs) {
  OrientedGraph     graph;
  GraphPtr          graphPtr = std::make_shared<OrientedGraph>(graph);
  std::string       graphNum = std::to_string(1);
  GraphVertexOutput output(graphPtr);
  EXPECT_EQ(output.getType(), VertexTypes::output);
  EXPECT_EQ(output.getTypeName(), "output");
  EXPECT_EQ(output.getName(), "output_" + graphNum);
  EXPECT_EQ(output.getLevel(), 0);
  EXPECT_EQ(output.getValue(), 'x');
  EXPECT_EQ(output.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultInputParametrs) {
  GraphVertexOutput output("Anything");
  EXPECT_EQ(output.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(output.getType(), VertexTypes::output);
  EXPECT_EQ(output.getTypeName(), "output");
  EXPECT_EQ(output.getName(), "Anything");
  EXPECT_EQ(output.getLevel(), 0);
  EXPECT_EQ(output.getValue(), 'x');
  EXPECT_EQ(output.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithDefaultInputParametrs) {
  OrientedGraph     graph;
  GraphPtr          graphPtr = std::make_shared<OrientedGraph>(graph);
  GraphVertexOutput output("Anything", graphPtr);
  EXPECT_EQ(output.getType(), VertexTypes::output);
  EXPECT_EQ(output.getTypeName(), "output");
  EXPECT_EQ(output.getName(), "Anything");
  EXPECT_EQ(output.getLevel(), 0);
  EXPECT_EQ(output.getValue(), 'x');
  EXPECT_EQ(output.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}
// ------------------------OverrideMethodsTests

TEST(TestUpdateValue, UpdateValueCorrect) {
  GraphVertexOutput output1;
  VertexPtr         constantPtr1 = std::make_shared<GraphVertexConstant>('z');
  output1.addVertexToInConnections(constantPtr1);
  EXPECT_EQ(output1.getValue(), 'x');
  EXPECT_EQ(output1.updateValue(), 'z');
  EXPECT_EQ(output1.getValue(), 'z');

  VertexPtr constantPtr2 = std::make_shared<GraphVertexConstant>('z');
  output1.addVertexToInConnections(constantPtr2);
  EXPECT_EQ(output1.updateValue(), 'z');

  VertexPtr constantPtr3 = std::make_shared<GraphVertexConstant>('1');
  output1.addVertexToInConnections(constantPtr3);
  EXPECT_EQ(output1.updateValue(), 'x');
}

TEST(TestUpdateValue, ReturnDValueIfDInConnectionsSizeZero) {
  GraphVertexOutput output;
  const char        c = output.getValue();
  EXPECT_EQ(output.updateValue(), c);
}

TEST(TestUpdateValue, ThrowInvalidArgumentIfDInConnectionsZeroIsNullptr) {
  GraphVertexOutput output1;
  output1.addVertexToInConnections(nullptr);
  EXPECT_THROW(output1.updateValue(), std::invalid_argument);
}

TEST(TestUpdateValue, ThrowInvalidArgumentIfDInconnectionsNIzNullptr) {
  GraphVertexInput output1;
  VertexPtr        outputPtr1 = std::make_shared<GraphVertexOutput>();
  VertexPtr        outputPtr2 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToInConnections(outputPtr1);
  output1.addVertexToInConnections(outputPtr2);
  EXPECT_NO_THROW(output1.updateValue());

  output1.addVertexToInConnections(nullptr);
  EXPECT_THROW(output1.updateValue(), std::invalid_argument);
}

TEST(TestUpdateLevel, CorrectUpdate) {
  GraphVertexOutput output1;
  VertexPtr         outputPtr1 = std::make_shared<GraphVertexOutput>();
  outputPtr1->setLevel(1);
  output1.addVertexToInConnections(outputPtr1);
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 1);

  VertexPtr outputPtr2 = std::make_shared<GraphVertexOutput>();
  VertexPtr outputPtr3 = std::make_shared<GraphVertexOutput>();
  outputPtr2->setLevel(3);
  outputPtr3->setLevel(2);
  output1.addVertexToInConnections(outputPtr2);
  output1.addVertexToInConnections(outputPtr3);
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 3);

  VertexPtr outputPtr4 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToInConnections(outputPtr4);
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 3);
}

TEST(TestUpdateLevel, ThrowInvalidArgumentIfDInconnectionsNIzNullptr) {
  GraphVertexOutput output1;

  VertexPtr         outputPtr1 = std::make_shared<GraphVertexOutput>();
  VertexPtr         outputPtr2 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToInConnections(outputPtr1);
  output1.addVertexToInConnections(outputPtr2);
  EXPECT_NO_THROW(output1.updateLevel());

  output1.addVertexToInConnections(nullptr);
  EXPECT_THROW(output1.updateLevel(), std::invalid_argument);

  VertexPtr outputPtr3 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToInConnections(outputPtr3);
  EXPECT_THROW(output1.updateLevel(), std::invalid_argument);
}

// -------------------------------------

TEST(TestSetName, InputCorrectName) {
  GraphVertexOutput output;
  output.setName("Anything");
  EXPECT_EQ(output.getName(), "Anything");
}

TEST(TestAddInConnections, AddConnections) {
  GraphVertexOutput output1;
  EXPECT_EQ(output1.getInConnections().size(), 0);

  VertexPtr outputPtr1 = std::make_shared<GraphVertexOutput>();
  EXPECT_EQ(output1.addVertexToInConnections(outputPtr1), 1);
  EXPECT_EQ(output1.addVertexToInConnections(outputPtr1), 2);
  EXPECT_EQ(output1.getInConnections()[0].lock(), outputPtr1);
  EXPECT_EQ(output1.getInConnections()[1].lock(), outputPtr1);

  VertexPtr outputPtr2 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToInConnections(outputPtr2);
  EXPECT_EQ(output1.getInConnections()[2].lock(), outputPtr2);
}

TEST(TestAddOutConnections, AddConnections) {
  GraphVertexOutput output1;
  EXPECT_EQ(output1.getOutConnections().size(), 0);

  VertexPtr outputPtr1 = std::make_shared<GraphVertexOutput>();
  EXPECT_EQ(output1.addVertexToOutConnections(outputPtr1), true);
  EXPECT_EQ(output1.addVertexToOutConnections(outputPtr1), false);
  EXPECT_EQ(output1.getOutConnections()[0], outputPtr1);

  VertexPtr outputPtr2 = std::make_shared<GraphVertexOutput>();
  output1.addVertexToOutConnections(outputPtr2);
  EXPECT_EQ(output1.getOutConnections()[1], outputPtr2);
}

TEST(TestCalculateHash, SameHashWhenEqualInputs) {
  GraphVertexOutput output1;
  EXPECT_EQ(output1.calculateHash(), "");

  output1.addVertexToOutConnections(std::make_shared<GraphVertexOutput>());
  EXPECT_EQ(output1.calculateHash(true), "");

  GraphPtr          graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexOutput output2(graphPtr1);
  GraphVertexInput  output3(graphPtr1);
  output2.addVertexToOutConnections(std::make_shared<GraphVertexInput>());
  EXPECT_NE(output2.calculateHash(true), output3.calculateHash(true));

  output3.addVertexToOutConnections(std::make_shared<GraphVertexInput>());
  EXPECT_EQ(output2.calculateHash(true), output3.calculateHash(true));
}

TEST(TestRemoveVertexToInConnections, RemoveConnections) {
  VertexPtr outputPtr1 = std::make_shared<GraphVertexOutput>();
  EXPECT_EQ(outputPtr1->removeVertexToInConnections(nullptr), false);

  outputPtr1->addVertexToInConnections(std::make_shared<GraphVertexOutput>());
  outputPtr1->addVertexToInConnections(std::make_shared<GraphVertexOutput>());
  EXPECT_EQ(outputPtr1->getInConnections().size(), 2);
  EXPECT_EQ(outputPtr1->removeVertexToInConnections(nullptr), true);
  EXPECT_EQ(outputPtr1->getInConnections().size(), 1);
}

// need to remake realisition of method
// TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}

TEST(TestIsConnected, SizeZeroAndOneIsConnected) {
  GraphPtr graphPtr1(new OrientedGraph());
  GraphPtr graphPtr2(new OrientedGraph());
  graphPtr2->addGate(Gates::GateAnd, "and");

  EXPECT_EQ(graphPtr1->isConnected(), true);
  EXPECT_EQ(graphPtr2->isConnected(), true);
}

TEST(TestIsConnected, SizeTwoWithoutEdgesIsNotConnected) {
  GraphPtr graphPtr(new OrientedGraph());
  graphPtr->addInput("input");
  graphPtr->addOutput("output");

  EXPECT_EQ(graphPtr->isConnected(), false);
}

TEST(TestIsConnected, SizeTwoWithEdgeIsConnected) {
  GraphPtr  graphPtr(new OrientedGraph());
  VertexPtr input  = graphPtr->addInput("input");
  VertexPtr output = graphPtr->addOutput("output");
  graphPtr->addEdge(input, output);

  EXPECT_EQ(graphPtr->isConnected(), true);
}

TEST(TestIsConnectedWithSubGraphsTrivial, ConnectedSubGraphIsConnected) {
  GraphPtr               graphPtr(new OrientedGraph());

  std::vector<VertexPtr> inputs;
  VertexPtr              input  = graphPtr->addInput("input");
  VertexPtr              output = graphPtr->addOutput("output");
  inputs.push_back(input);

  GraphPtr  subGraphPtr(new OrientedGraph());

  VertexPtr subGraphInput  = subGraphPtr->addInput("subGraphInput");
  VertexPtr testBuf        = subGraphPtr->addGate(Gates::GateBuf);
  VertexPtr subGraphOutput = subGraphPtr->addOutput("subGraphOutput");

  subGraphPtr->addEdge(subGraphInput, testBuf);
  subGraphPtr->addEdge(testBuf, subGraphOutput);

  auto subGraphOutput2 = graphPtr->addSubGraph(subGraphPtr, inputs).back();
  auto inv             = graphPtr->addGate(GateNot);

  graphPtr->addEdge(subGraphOutput2, inv);
  graphPtr->addEdge(inv, output);

  EXPECT_EQ(graphPtr->isConnected(), true);
}

TEST(TestIsConnectedWithSubGraphsTrivial, DisconnectedSubGraphIsNotConnected) {
  GraphPtr  graphPtr(new OrientedGraph());
  VertexPtr input = graphPtr->addInput("input");

  GraphPtr  subGraphPtr(new OrientedGraph());
  VertexPtr subGraphInput  = subGraphPtr->addInput("subGraphInput");
  VertexPtr subGraphOutput = subGraphPtr->addOutput("subGraphOutput");

  graphPtr->addSubGraph(
      subGraphPtr, graphPtr->getVerticesByType(VertexTypes::input)
  );

  EXPECT_EQ(graphPtr->isConnected(), false);
}

TEST(
    TestIsConnectedWithSubGraphsNontrivial,
    DisconnectedSubGraphLvl2IsNotConnected
) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Input2  = lvl1->addInput("lvl1Input2");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1Output2);

  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Input2  = lvl0->addInput("lvl0Input2");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), false);
  EXPECT_EQ(lvl1->isConnected(), false);
  EXPECT_EQ(lvl0->isConnected(), false);
}

TEST(TestIsConnectedWithSubGraphsNontrivial, ConnectedSubGraphLvl2IsConnected) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output2);  // <-- different from upper test
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Input2  = lvl1->addInput("lvl1Input2");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1Output2);

  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Input2  = lvl0->addInput("lvl0Input2");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), true);
  EXPECT_EQ(lvl1->isConnected(), true);
  EXPECT_EQ(lvl0->isConnected(), true);
}

TEST(
    TestIsConnectedWithSubGraphsNontrivial,
    ConnectedSubGraphLvl1IsConnectedStraight
) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Input2  = lvl1->addInput("lvl1Input2");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  VertexPtr lvl1And     = lvl1->addGate(Gates::GateAnd, "lvl1And");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1And);
  lvl1->addEdge(lvl1Input2, lvl1And);
  lvl1->addEdge(lvl1And, lvl1Output2);

  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Input2  = lvl0->addInput("lvl0Input2");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), false);
  EXPECT_EQ(lvl1->isConnected(), true);
  EXPECT_EQ(lvl0->isConnected(), true);
}

TEST(
    TestIsConnectedWithSubGraphsNontrivial,
    ConnectedSubGraphLvl1IsConnectedReverse
) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input2 =
      lvl1->addInput("lvl1Input2");  // <-- different from upper test
  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  VertexPtr lvl1And     = lvl1->addGate(Gates::GateAnd, "lvl1And");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1And);
  lvl1->addEdge(lvl1Input1, lvl1And);  // <-- different from upper test
  lvl1->addEdge(lvl1And, lvl1Output2);

  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Input2  = lvl0->addInput("lvl0Input2");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), false);
  EXPECT_EQ(lvl1->isConnected(), true);
  EXPECT_EQ(lvl0->isConnected(), true);
}

TEST(
    TestIsConnectedWithSubGraphsNontrivial,
    ConnectedSubGraphLvl0IsConnectedStraight
) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Input2  = lvl1->addInput("lvl1Input2");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1Output2);

  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Input2  = lvl0->addInput("lvl0Input2");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  VertexPtr lvl0And     = lvl0->addGate(Gates::GateAnd, "lvl0And");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0And);
  lvl0->addEdge(lvl0Input2, lvl0And);
  lvl0->addEdge(lvl0And, lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), false);
  EXPECT_EQ(lvl1->isConnected(), false);
  EXPECT_EQ(lvl0->isConnected(), true);
}

TEST(
    TestIsConnectedWithSubGraphsNontrivial,
    ConnectedSubGraphLvl0IsConnectedReverse
) {
  GraphPtr  lvl0(new OrientedGraph());
  GraphPtr  lvl1(new OrientedGraph());
  GraphPtr  lvl2(new OrientedGraph());

  VertexPtr lvl2Input1  = lvl2->addInput("lvl2Input1");
  VertexPtr lvl2Output1 = lvl2->addOutput("lvl2Output1");
  VertexPtr lvl2Input2  = lvl2->addInput("lvl2Input2");
  VertexPtr lvl2Output2 = lvl2->addOutput("lvl2Output2");
  lvl2->addEdge(lvl2Input1, lvl2Output2);
  lvl2->addEdge(lvl2Input2, lvl2Output1);

  VertexPtr lvl1Input1  = lvl1->addInput("lvl1Input1");
  VertexPtr lvl1Output1 = lvl1->addOutput("lvl1Output1");
  VertexPtr lvl1Input2  = lvl1->addInput("lvl1Input2");
  VertexPtr lvl1Output2 = lvl1->addOutput("lvl1Output2");
  auto      bufsLvl1 =
      lvl1->addSubGraph(lvl2, lvl1->getVerticesByType(VertexTypes::input));
  lvl1->addEdge(bufsLvl1[0], lvl1Output1);
  lvl1->addEdge(bufsLvl1[1], lvl1Output2);

  VertexPtr lvl0Input2 =
      lvl0->addInput("lvl0Input2");  // <-- different from upper test
  VertexPtr lvl0Input1  = lvl0->addInput("lvl0Input1");
  VertexPtr lvl0Output1 = lvl0->addOutput("lvl0Output1");
  VertexPtr lvl0Output2 = lvl0->addOutput("lvl0Output2");
  VertexPtr lvl0And     = lvl0->addGate(Gates::GateAnd, "lvl0And");
  auto      bufsLvl0 =
      lvl0->addSubGraph(lvl1, lvl0->getVerticesByType(VertexTypes::input));
  lvl0->addEdge(bufsLvl0[0], lvl0Output1);
  lvl0->addEdge(bufsLvl0[1], lvl0And);
  lvl0->addEdge(lvl0Input1, lvl0And);  // <-- different from upper test
  lvl0->addEdge(lvl0And, lvl0Output2);

  EXPECT_EQ(lvl2->isConnected(), false);
  EXPECT_EQ(lvl1->isConnected(), false);
  EXPECT_EQ(lvl0->isConnected(), true);
}

TEST(TestIsConnectedRecalculation, SimpleRecalculation) {
  GraphPtr  graphPtr(new OrientedGraph());
  VertexPtr input  = graphPtr->addInput("input");
  VertexPtr output = graphPtr->addOutput("output");
  EXPECT_EQ(graphPtr->isConnected(), false);

  graphPtr->addEdge(input, output);
  EXPECT_EQ(graphPtr->isConnected(), false);
  EXPECT_EQ(graphPtr->isConnected(true), true);

  graphPtr->addGate(Gates::GateAnd, "and");
  EXPECT_EQ(graphPtr->isConnected(), true);
  EXPECT_EQ(graphPtr->isConnected(true), false);
}