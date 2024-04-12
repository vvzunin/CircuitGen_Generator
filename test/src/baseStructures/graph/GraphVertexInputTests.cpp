#include <sstream>

#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

/*
  Need to add calculateHashTest, another test UpdateLevelTest
  Need to remake RemoveVertexToOutConnections
*/

TEST(TestConstructorWithoutIName, WithoutDefaultInputParametrs) {
  GraphVertexInput input;
  std::string      graphNum = std::to_string(0);
  EXPECT_EQ(input.getType(), VertexTypes::input);
  EXPECT_EQ(input.getTypeName(), "input");
  EXPECT_EQ(input.getName(), "input_" + graphNum);
  EXPECT_EQ(input.getLevel(), 0);
  EXPECT_EQ(input.getValue(), 'x');
  EXPECT_EQ(input.getBaseGraph(), nullptr);
  EXPECT_EQ(input.getOutConnections().size(), 0);
}

TEST(TestConstructorWithoutIName, WithDefaultInputParametrs) {
  OrientedGraph    example;
  std::string      graphNum = std::to_string(1);
  GraphVertexInput input(&example, VertexTypes::input);
  EXPECT_EQ(input.getType(), VertexTypes::input);
  EXPECT_EQ(input.getTypeName(), "input");
  EXPECT_EQ(input.getName(), "input_" + graphNum);
  EXPECT_EQ(input.getLevel(), 0);
  EXPECT_EQ(input.getValue(), 'x');
  EXPECT_EQ(input.getBaseGraph(), &example);
  EXPECT_EQ(input.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultInputParametrs) {
  GraphVertexInput input("Anything");
  EXPECT_EQ(input.getBaseGraph(), nullptr);
  EXPECT_EQ(input.getType(), VertexTypes::input);
  EXPECT_EQ(input.getTypeName(), "input");
  EXPECT_EQ(input.getName(), "Anything");
  EXPECT_EQ(input.getLevel(), 0);
  EXPECT_EQ(input.getValue(), 'x');
  EXPECT_EQ(input.getBaseGraph(), nullptr);
  EXPECT_EQ(input.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithDefaultInputParametrs) {
  OrientedGraph    example;
  GraphVertexInput input("Anything", &example, VertexTypes::input);
  EXPECT_EQ(input.getType(), VertexTypes::input);
  EXPECT_EQ(input.getTypeName(), "input");
  EXPECT_EQ(input.getName(), "Anything");
  EXPECT_EQ(input.getLevel(), 0);
  EXPECT_EQ(input.getValue(), 'x');
  EXPECT_EQ(input.getBaseGraph(), &example);
  EXPECT_EQ(input.getOutConnections().size(), 0);
}
// -----OverrideMethodsTests

TEST(TestUpdateValue, ReturnDValueIfDInConnectionsSizeZero) {
  GraphVertexInput input;
  EXPECT_EQ(input.updateValue(), input.getValue());
}

// TEST(TestUpdateLevel, CorrectUpdate){}

TEST(TestUpdateValue, CerrErrorIfThereIsBaseGraph) {
  OrientedGraph    graph;
  GraphVertexInput input1(&graph);
  GraphVertexInput input2;

  input1.addVertexToInConnections(std::make_shared<GraphVertexInput>(input2));

  std::stringstream capturedOutput;
  std::streambuf*   originalStderr = std::cerr.rdbuf(capturedOutput.rdbuf());

  input1.updateValue();

  std::cerr.rdbuf(originalStderr);
  std::string output = capturedOutput.str();
  EXPECT_EQ(output, "Error\n");
}

TEST(TestUpdateValue, CorrectUpdate) {
  OrientedGraph    graph;
  GraphVertexInput input1(&graph);
  GraphVertexInput input2;
  input2.setLevel(1);
  input1.addVertexToInConnections(std::make_shared<GraphVertexInput>(input2));
  input1.updateLevel();
  EXPECT_EQ(input1.getLevel(), 1);

  GraphVertexInput input3;
  GraphVertexInput input4;
  input3.setLevel(2);
  input4.setLevel(3);
  input1.addVertexToInConnections(std::make_shared<GraphVertexInput>(input3));
  input1.addVertexToInConnections(std::make_shared<GraphVertexInput>(input4));
  input1.updateLevel();
  EXPECT_EQ(input1.getLevel(), 3);

  GraphVertexInput input5;
  input1.updateLevel();
  EXPECT_EQ(input1.getLevel(), 3);
}

// -----

TEST(TestSetName, InputCorrectName) {
  GraphVertexInput input;
  input.setName("Anything");
  EXPECT_EQ(input.getName(), "Anything");
}

TEST(TestAddInConnections, AddConnections) {
  GraphVertexInput input1;
  EXPECT_EQ(input1.getInConnections().size(), 0);

  GraphVertexInput input2;
  std::shared_ptr  ptr1 = std::make_shared<GraphVertexInput>(input2);
  EXPECT_EQ(input1.addVertexToInConnections(ptr1), 1);
  EXPECT_EQ(input1.addVertexToInConnections(ptr1), 2);
  EXPECT_EQ(input1.getInConnections()[0], ptr1);
  EXPECT_EQ(input1.getInConnections()[1], ptr1);

  GraphVertexInput input3;
  std::shared_ptr  ptr2 = std::make_shared<GraphVertexInput>(input3);
  input1.addVertexToInConnections(ptr2);
  EXPECT_EQ(input1.getInConnections()[2], ptr2);
}

TEST(TestAddOutConnections, AddConnections) {
  GraphVertexInput input1;
  EXPECT_EQ(input1.getOutConnections().size(), 0);

  GraphVertexInput input2;
  std::shared_ptr  ptr1 = std::make_shared<GraphVertexInput>(input2);
  EXPECT_EQ(input1.addVertexToOutConnections(ptr1), true);
  EXPECT_EQ(input1.addVertexToOutConnections(ptr1), false);
  EXPECT_EQ(input1.getOutConnections()[0], ptr1);

  GraphVertexInput input3;
  std::shared_ptr  ptr2 = std::make_shared<GraphVertexInput>(input3);
  input1.addVertexToOutConnections(ptr2);
  EXPECT_EQ(input1.getOutConnections()[1], ptr2);
}

// need to remake realisition of method
// TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}

// TEST(TestCalculateHash, SameHashWhenEqualInputs) {}