#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

/*
  Need to add calculateHashTest, another UpdateLevelTest
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
  EXPECT_EQ(output.getBaseGraph(), nullptr);
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
  EXPECT_EQ(output.getBaseGraph(), graphPtr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultInputParametrs) {
  GraphVertexOutput output("Anything");
  EXPECT_EQ(output.getBaseGraph(), nullptr);
  EXPECT_EQ(output.getType(), VertexTypes::output);
  EXPECT_EQ(output.getTypeName(), "output");
  EXPECT_EQ(output.getName(), "Anything");
  EXPECT_EQ(output.getLevel(), 0);
  EXPECT_EQ(output.getValue(), 'x');
  EXPECT_EQ(output.getBaseGraph(), nullptr);
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
  EXPECT_EQ(output.getBaseGraph(), graphPtr);
  EXPECT_EQ(output.getOutConnections().size(), 0);
}
// -----OverrideMethodsTests

TEST(TestUpdateValue, ReturnDValueIfDInConnectionsSizeZero) {
  GraphVertexInput input;
  EXPECT_EQ(input.updateValue(), input.getValue());
}

// TEST(TestUpdateValue, CorrectUpdate){}

TEST(TestUpdateValue, CerrErrorIfThereIsBaseGraph) {
  OrientedGraph    graph;
  GraphVertexInput input1(std::make_shared<OrientedGraph>(graph));
  GraphVertexInput input2;

  input1.addVertexToInConnections(std::make_shared<GraphVertexInput>(input2));

  std::stringstream capturedOutput;
  std::streambuf*   originalStderr = std::cerr.rdbuf(capturedOutput.rdbuf());

  input1.updateValue();

  std::cerr.rdbuf(originalStderr);
  std::string output = capturedOutput.str();
  EXPECT_EQ(output, "Error\n");
}

TEST(TestUpdateLevel, CorrectUpdate) {
  OrientedGraph     graph;
  GraphVertexOutput output1(std::make_shared<OrientedGraph>(graph));
  GraphVertexOutput output2;
  output2.setLevel(1);
  output1.addVertexToInConnections(std::make_shared<GraphVertexOutput>(output2)
  );
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 1);

  GraphVertexOutput output3;
  GraphVertexOutput output4;
  output3.setLevel(2);
  output4.setLevel(3);
  output1.addVertexToInConnections(std::make_shared<GraphVertexOutput>(output3)
  );
  output1.addVertexToInConnections(std::make_shared<GraphVertexOutput>(output4)
  );
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 3);

  GraphVertexOutput output5;
  output1.addVertexToInConnections(std::make_shared<GraphVertexOutput>(output5)
  );
  output1.updateLevel();
  EXPECT_EQ(output1.getLevel(), 3);
}

// -----

TEST(TestSetName, InputCorrectName) {
  GraphVertexOutput output;
  output.setName("Anything");
  EXPECT_EQ(output.getName(), "Anything");
}

TEST(TestAddInConnections, AddConnections) {
  GraphVertexOutput output1;
  EXPECT_EQ(output1.getInConnections().size(), 0);

  GraphVertexOutput output2;
  std::shared_ptr   ptr1 = std::make_shared<GraphVertexOutput>(output2);
  EXPECT_EQ(output1.addVertexToInConnections(ptr1), 1);
  EXPECT_EQ(output1.addVertexToInConnections(ptr1), 2);
  EXPECT_EQ(output1.getInConnections()[0], ptr1);
  EXPECT_EQ(output1.getInConnections()[1], ptr1);

  GraphVertexOutput output3;
  std::shared_ptr   ptr2 = std::make_shared<GraphVertexOutput>(output3);
  output1.addVertexToInConnections(ptr2);
  EXPECT_EQ(output1.getInConnections()[2], ptr2);
}

TEST(TestAddOutConnections, AddConnections) {
  GraphVertexOutput output1;
  EXPECT_EQ(output1.getOutConnections().size(), 0);

  GraphVertexOutput output2;
  std::shared_ptr   ptr1 = std::make_shared<GraphVertexOutput>(output2);
  EXPECT_EQ(output1.addVertexToOutConnections(ptr1), true);
  EXPECT_EQ(output1.addVertexToOutConnections(ptr1), false);
  EXPECT_EQ(output1.getOutConnections()[0], ptr1);

  GraphVertexOutput output3;
  std::shared_ptr   ptr2 = std::make_shared<GraphVertexOutput>(output3);
  output1.addVertexToOutConnections(ptr2);
  EXPECT_EQ(output1.getOutConnections()[1], ptr2);
}

// need to remake realisition of method
// TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}

// TEST(TestCalculateHash, SameHashWhenEqualInputs) {}