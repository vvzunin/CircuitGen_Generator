#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

TEST(TestConstructorWithoutIName, WithoutDefaultInputParametrs) {
  GraphVertexConstant constant('z');
  std::string         graphNum = std::to_string(0);
  EXPECT_EQ(constant.getType(), VertexTypes::constant);
  EXPECT_EQ(constant.getTypeName(), "const");
  EXPECT_EQ(constant.getName(), "const_" + graphNum);
  EXPECT_EQ(constant.getLevel(), 0);
  EXPECT_EQ(constant.getValue(), 'z');
  EXPECT_EQ(constant.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(constant.getOutConnections().size(), 0);
}

TEST(TestConstructorWithoutIName, WithDefaultInputParametrs) {
  GraphPtr            graphPtr = std::make_shared<OrientedGraph>();

  std::string         graphNum = std::to_string(1);
  GraphVertexConstant constant('z', graphPtr);
  EXPECT_EQ(constant.getType(), VertexTypes::constant);
  EXPECT_EQ(constant.getTypeName(), "const");
  EXPECT_EQ(constant.getName(), "const_" + graphNum);
  EXPECT_EQ(constant.getLevel(), 0);
  EXPECT_EQ(constant.getValue(), 'z');
  EXPECT_EQ(constant.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(constant.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultInputParametrs) {
  GraphVertexConstant constant('z', "Anything");
  EXPECT_EQ(constant.getType(), VertexTypes::constant);
  EXPECT_EQ(constant.getTypeName(), "const");
  EXPECT_EQ(constant.getName(), "Anything");
  EXPECT_EQ(constant.getLevel(), 0);
  EXPECT_EQ(constant.getValue(), 'z');
  EXPECT_EQ(constant.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(constant.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithDefaultInputParametrs) {
  GraphPtr            graphPtr = std::make_shared<OrientedGraph>();

  GraphVertexConstant constant('z', "Anything", graphPtr);
  EXPECT_EQ(constant.getType(), VertexTypes::constant);
  EXPECT_EQ(constant.getTypeName(), "const");
  EXPECT_EQ(constant.getName(), "Anything");
  EXPECT_EQ(constant.getLevel(), 0);
  EXPECT_EQ(constant.getValue(), 'z');
  EXPECT_EQ(constant.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(constant.getOutConnections().size(), 0);
}

// ------------------OverrideMethodsTests

// it returns 0 does it correct?
TEST(TestUpdateLevel, CorrectUpdate) {
  GraphVertexConstant constant1('z');
  constant1.updateLevel();
  EXPECT_EQ(constant1.getLevel(), 0);
}

TEST(TestGetInstance, ReturnCorrectInstance) {
  GraphVertexConstant constant1('z', "Anything");
  EXPECT_EQ(constant1.getInstance(), "wire Anything;");
}

// -------------------------------------

TEST(TestSetName, InputCorrectName) {
  GraphVertexConstant constant('z');
  constant.setName("Anything");
  EXPECT_EQ(constant.getName(), "Anything");
}

TEST(TestAddVertexToInConnections, AddConnections) {
  GraphVertexConstant constant1('z');
  EXPECT_EQ(constant1.getInConnections().size(), 0);

  GraphVertexConstant constant2('z');
  std::shared_ptr     ptr1 = std::make_shared<GraphVertexConstant>(constant2);
  EXPECT_EQ(constant1.addVertexToInConnections(ptr1), 1);
  EXPECT_EQ(constant1.addVertexToInConnections(ptr1), 2);
  EXPECT_EQ(constant1.getInConnections()[0].lock(), ptr1);
  EXPECT_EQ(constant1.getInConnections()[1].lock(), ptr1);

  GraphVertexConstant constant3('z');
  std::shared_ptr     ptr2 = std::make_shared<GraphVertexConstant>(constant3);
  constant1.addVertexToInConnections(ptr2);
  EXPECT_EQ(constant1.getInConnections()[2].lock(), ptr2);
}

TEST(TestAddVertexToOutConnections, AddConnections) {
  GraphVertexConstant constant1('z');
  EXPECT_EQ(constant1.getOutConnections().size(), 0);

  GraphVertexConstant constant2('z');
  std::shared_ptr     ptr1 = std::make_shared<GraphVertexConstant>(constant2);
  EXPECT_EQ(constant1.addVertexToOutConnections(ptr1), true);
  EXPECT_EQ(constant1.addVertexToOutConnections(ptr1), false);
  EXPECT_EQ(constant1.getOutConnections()[0], ptr1);

  GraphVertexConstant constant3('z');
  std::shared_ptr     ptr2 = std::make_shared<GraphVertexConstant>(constant3);
  constant1.addVertexToOutConnections(ptr2);
  EXPECT_EQ(constant1.getOutConnections()[1], ptr2);
}

TEST(TestCalculateHash, SameHashWhenEqualInputs) {
  GraphVertexConstant constant1('z');
  GraphVertexConstant constant2('z');
  EXPECT_EQ(constant1.calculateHash(), constant2.calculateHash());

  constant1.addVertexToOutConnections(std::make_shared<GraphVertexConstant>('z')
  );
  EXPECT_NE(constant1.calculateHash(true), constant2.calculateHash(true));
  constant2.addVertexToOutConnections(std::make_shared<GraphVertexConstant>('z')
  );
  EXPECT_EQ(constant1.calculateHash(true), constant2.calculateHash(true));
}

TEST(TestRemoveVertexToInConnections, RemoveConnections) {
  VertexPtr vertexPtr1 = std::make_shared<GraphVertexConstant>('z');
  EXPECT_EQ(vertexPtr1->removeVertexToInConnections(vertexPtr1), false);
  vertexPtr1->addVertexToInConnections(std::make_shared<GraphVertexConstant>('z'
  ));
  vertexPtr1->addVertexToInConnections(std::make_shared<GraphVertexConstant>('z'
  ));
  EXPECT_EQ(vertexPtr1->getInConnections().size(), 2);
  EXPECT_EQ(vertexPtr1->removeVertexToInConnections(nullptr), true);
  EXPECT_EQ(vertexPtr1->getInConnections().size(), 1);
}

// need to remake realisition of method
// TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}
