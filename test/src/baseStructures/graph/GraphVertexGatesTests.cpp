#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

/*
  Need to add calculateHashTest, another UpdateLevelTest, getVerilogStringTest,
    getGateTest, toVerilogTest
  Need to remake RemoveVertexToOutConnections
*/

TEST(TestConstructorWithoutIName, WithoutDefaultGatesParametrs) {
  GraphVertexGates gate(Gates::GateAnd);
  std::string      graphNum = std::to_string(0);
  EXPECT_EQ(gate.getType(), VertexTypes::gate);
  EXPECT_EQ(gate.getTypeName(), "g");
  EXPECT_EQ(gate.getName(), "g_" + graphNum);
  EXPECT_EQ(gate.getLevel(), 0);
  EXPECT_EQ(gate.getValue(), 'x');
  EXPECT_EQ(gate.getBaseGraph(), nullptr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

TEST(TestConstructorWithoutIName, WithDefaultGatesParametrs) {
  GraphPtr         graphPtr = std::make_shared<OrientedGraph>();
  std::string      graphNum = std::to_string(1);
  GraphVertexGates gate(Gates::GateAnd, graphPtr);
  EXPECT_EQ(gate.getType(), VertexTypes::gate);
  EXPECT_EQ(gate.getTypeName(), "g");
  EXPECT_EQ(gate.getName(), "g_" + graphNum);
  EXPECT_EQ(gate.getLevel(), 0);
  EXPECT_EQ(gate.getValue(), 'x');
  EXPECT_EQ(gate.getBaseGraph(), graphPtr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultGatesParametrs) {
  GraphVertexGates gate(Gates::GateAnd, "Anything");
  EXPECT_EQ(gate.getBaseGraph(), nullptr);
  EXPECT_EQ(gate.getType(), VertexTypes::gate);
  EXPECT_EQ(gate.getTypeName(), "g");
  EXPECT_EQ(gate.getName(), "Anything");
  EXPECT_EQ(gate.getLevel(), 0);
  EXPECT_EQ(gate.getValue(), 'x');
  EXPECT_EQ(gate.getBaseGraph(), nullptr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithDefaultGatesParametrs) {
  GraphPtr         graphPtr = std::make_shared<OrientedGraph>();
  std::string      graphNum = std::to_string(1);
  GraphVertexGates gate(Gates::GateAnd, "Anything", graphPtr);
  EXPECT_EQ(gate.getType(), VertexTypes::gate);
  EXPECT_EQ(gate.getTypeName(), "g");
  EXPECT_EQ(gate.getName(), "Anything");
  EXPECT_EQ(gate.getLevel(), 0);
  EXPECT_EQ(gate.getValue(), 'x');
  EXPECT_EQ(gate.getBaseGraph(), graphPtr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

// -----OverrideMethodsTests

// -----

TEST(TestSetName, GatesCorrectName) {
  GraphVertexGates gate(Gates::GateAnd);
  gate.setName("Anything");
  EXPECT_EQ(gate.getName(), "Anything");
}

TEST(TestAddInConnections, AddConnections) {
  GraphVertexGates gate1(Gates::GateAnd);
  EXPECT_EQ(gate1.getInConnections().size(), 0);

  GraphVertexGates gate2(Gates::GateAnd);
  std::shared_ptr  ptr1 = std::make_shared<GraphVertexGates>(gate2);
  EXPECT_EQ(gate1.addVertexToInConnections(ptr1), 1);
  EXPECT_EQ(gate1.addVertexToInConnections(ptr1), 2);
  EXPECT_EQ(gate1.getInConnections()[0], ptr1);
  EXPECT_EQ(gate1.getInConnections()[1], ptr1);

  GraphVertexGates gate3(Gates::GateAnd);
  std::shared_ptr  ptr2 = std::make_shared<GraphVertexGates>(gate3);
  gate1.addVertexToInConnections(ptr2);
  EXPECT_EQ(gate1.getInConnections()[2], ptr2);
}

TEST(TestAddOutConnections, AddConnections) {
  GraphVertexGates gate1(Gates::GateAnd);
  EXPECT_EQ(gate1.getOutConnections().size(), 0);

  GraphVertexGates gate2(Gates::GateAnd);
  std::shared_ptr  ptr1 = std::make_shared<GraphVertexGates>(gate2);
  EXPECT_EQ(gate1.addVertexToOutConnections(ptr1), true);
  EXPECT_EQ(gate1.addVertexToOutConnections(ptr1), false);
  EXPECT_EQ(gate1.getOutConnections()[0], ptr1);

  GraphVertexGates gate3(Gates::GateAnd);
  std::shared_ptr  ptr2 = std::make_shared<GraphVertexGates>(gate3);
  gate1.addVertexToOutConnections(ptr2);
  EXPECT_EQ(gate1.getOutConnections()[1], ptr2);
}

// // need to remake realisition of method
// // TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}

// // TEST(TestCalculateHash, SameHashWhenEqualGatess) {}