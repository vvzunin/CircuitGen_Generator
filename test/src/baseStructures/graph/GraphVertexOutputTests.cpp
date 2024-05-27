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
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr graphPtr2 = std::make_shared<OrientedGraph>();
  graphPtr2->addGate(Gates::GateAnd, "and");

  EXPECT_EQ(graphPtr1->isConnected(), 1);
  EXPECT_EQ(graphPtr2->isConnected(), 1);
}

TEST(TestIsConnected, SizeTwoWithoutEdgesIsNotConnected) {
  GraphPtr graphPtr = std::make_shared<OrientedGraph>();
  graphPtr->addInput("input");
  graphPtr->addOutput("output");

  EXPECT_EQ(graphPtr->isConnected(), 0);
}

TEST(TestIsConnected, SizeTwoWithEdgeIsConnected) {
  GraphPtr  graphPtr = std::make_shared<OrientedGraph>();
  VertexPtr input    = graphPtr->addInput("input");
  VertexPtr output   = graphPtr->addOutput("output");
  graphPtr->addEdge(input, output);

  EXPECT_EQ(graphPtr->isConnected(), 1);
}

TEST(TestIsConnectedWithSubGraphs, ConnectedSubGraphIsConnected) {
  GraphPtr  subGraphPtr(new OrientedGraph());
  VertexPtr subGraphInput  = subGraphPtr->addInput("subGraphInput");
  VertexPtr subGraphOutput = subGraphPtr->addOutput("subGraphOutput");
  subGraphPtr->addEdge(subGraphInput, subGraphOutput);

  GraphPtr               graphPtr(new OrientedGraph());

  std::vector<VertexPtr> inputs;
  VertexPtr              input  = graphPtr->addInput("input");
  VertexPtr              output = graphPtr->addOutput("output");
  inputs.push_back(input);

  graphPtr->addSubGraph(subGraphPtr, inputs);

  EXPECT_EQ(graphPtr->isConnected(), 1);
}

TEST(TestIsConnectedWithSubGraphs, NotConnectedSubGraphIsNotConnected) {
  GraphPtr  subGraphPtr    = std::make_shared<OrientedGraph>();
  VertexPtr subGraphInput  = subGraphPtr->addInput("subGraphInput");
  VertexPtr subGraphOutput = subGraphPtr->addOutput("subGraphOutput");

  GraphPtr  graphPtr       = std::make_shared<OrientedGraph>();
  VertexPtr input          = graphPtr->addInput("input");
  graphPtr->addSubGraph(
      subGraphPtr, graphPtr->getVerticesByType(VertexTypes::input)
  );

  EXPECT_EQ(graphPtr->isConnected(), 0);
}