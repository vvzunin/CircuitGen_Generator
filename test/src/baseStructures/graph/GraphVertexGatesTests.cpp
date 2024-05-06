#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

/*
  Need to add another UpdateValueTest
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
  EXPECT_EQ(gate.getBaseGraph().lock(), nullptr);
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
  EXPECT_EQ(gate.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultGatesParametrs) {
  GraphVertexGates gate(Gates::GateAnd, "Anything");
  EXPECT_EQ(gate.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(gate.getType(), VertexTypes::gate);
  EXPECT_EQ(gate.getTypeName(), "g");
  EXPECT_EQ(gate.getName(), "Anything");
  EXPECT_EQ(gate.getLevel(), 0);
  EXPECT_EQ(gate.getValue(), 'x');
  EXPECT_EQ(gate.getBaseGraph().lock(), nullptr);
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
  EXPECT_EQ(gate.getBaseGraph().lock(), graphPtr);
  EXPECT_EQ(gate.getOutConnections().size(), 0);
}

// -----OverrideMethodsTests

TEST(TestUpdateValue, ReturnDValueIfDInConnectionsSizeZero) {
  GraphVertexGates gate1(Gates::GateAnd);
  const char       c = gate1.getValue();
  EXPECT_EQ(gate1.updateValue(), c);
}

TEST(TestUpdateValue, ReturnXIfDInConnectionsZeroIsDead) {
  GraphVertexGates gate1(Gates::GateAnd);
  gate1.addVertexToInConnections(nullptr);
  EXPECT_EQ(gate1.updateValue(), 'x');
}

TEST(TestUpdateLevel, CorrectUpdate) {
  GraphVertexGates gate1(Gates::GateAnd);
  VertexPtr gatePtr1 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gatePtr1->setLevel(1);
  gate1.addVertexToInConnections(gatePtr1);
  gate1.updateLevel();
  EXPECT_EQ(gate1.getLevel(), 2);

  VertexPtr gatePtr2 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  VertexPtr gatePtr3 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gatePtr2->setLevel(3);
  gatePtr3->setLevel(2);
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  gate1.updateLevel();
  EXPECT_EQ(gate1.getLevel(), 4);

  VertexPtr gatePtr4 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr4);
  gate1.updateLevel();
  EXPECT_EQ(gate1.getLevel(), 4);
}

TEST(TestUpdateLevel, ThrowInvalidArgumentIfDInconnectionsNIsNullptr) {
  GraphVertexGates gate1(Gates::GateAnd);

  VertexPtr gatePtr1 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  VertexPtr gatePtr2 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr1);
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_NO_THROW(gate1.updateLevel());

  gate1.addVertexToInConnections(nullptr);
  EXPECT_THROW(gate1.updateLevel(), std::invalid_argument);

  VertexPtr gatePtr3 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_THROW(gate1.updateLevel(), std::invalid_argument);
}

TEST(TestGetVerilogString, ReturnEmptyStringIfDInConnectionsSizeIsZero) {
  GraphVertexGates gate1(Gates::GateAnd);
  EXPECT_EQ(gate1.getVerilogString(), "");
}

TEST(TestGetVerilogString, ThrowInvalidArgumentIfDInConnectionsZeroIsDead) {
  GraphVertexGates gate1(Gates::GateAnd);
  gate1.addVertexToInConnections(nullptr);
  EXPECT_THROW(gate1.getVerilogString(), std::invalid_argument);
}

TEST(TestGetVerilogString, ThrowInvalidArgumentIfDInConnectionsNIsDead) {
  GraphVertexGates gate1(Gates::GateAnd);
  VertexPtr gatePtr1 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  VertexPtr gatePtr2 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr1);
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_NO_THROW(gate1.getVerilogString());

  gate1.addVertexToInConnections(nullptr);
  EXPECT_THROW(gate1.getVerilogString(), std::invalid_argument);

  VertexPtr gatePtr3 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_THROW(gate1.getVerilogString(), std::invalid_argument);
}

TEST(TestGetVerilogString, ReturnStringWithAndExpressionWhenUseGateAnd) {
  GraphVertexGates gate1(Gates::GateAnd);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "Var1");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "Var1 & Var2 & Var3");
}

TEST(TestGetVerilogString, CerrErrorStringWhenUseGateDefault) {
  GraphVertexGates gate1(Gates::GateDefault);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  gate1.addVertexToInConnections(gatePtr2);

  std::stringstream capturedOutput;
  std::streambuf*   originalStderr = std::cerr.rdbuf(capturedOutput.rdbuf());

  gate1.getVerilogString();

  std::cerr.rdbuf(originalStderr);
  std::string output = capturedOutput.str();
  EXPECT_EQ(output, "Error\n");
}

TEST(TestGetVerilogString, ReturnCorrectStringExpressionWhenUseGateNand) {
  GraphVertexGates gate1(Gates::GateNand);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1)");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1 & Var2 & Var3)");
}

TEST(TestGetVerilogString, ReturnCorrectStringExpressionWhenUsedGateNor) {
  GraphVertexGates gate1(Gates::GateNor);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1)");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1 | Var2 | Var3)");
}

TEST(TestGetVerilogString, ReturnCorrectStrinExpressionWhenUseGateNot) {
  GraphVertexGates gate1(Gates::GateNot);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "~Var1");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "~Var1 ~ Var2 ~ Var3");
}

TEST(TestGetVerilogString, ReturnCorrectStringExpressionWhenUsedGateOr) {
  GraphVertexGates gate1(Gates::GateOr);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "Var1");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "Var1 | Var2 | Var3");
}

TEST(TestGetVerilogString, ReturnCorrectStringExpressionWhenUseGateXnor) {
  GraphVertexGates gate1(Gates::GateXnor);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1)");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "~(Var1 ^ Var2 ^ Var3)");
}

TEST(TestGetVerilogString, ReturnCorrectStringExpressionWhenUseGateXor) {
  GraphVertexGates gate1(Gates::GateXor);
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var1");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.getVerilogString(), "Var1");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr3 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  gate1.addVertexToInConnections(gatePtr3);
  EXPECT_EQ(gate1.getVerilogString(), "Var1 ^ Var2 ^ Var3");
}

TEST(TestGetGate, ReturnCorrectGate) {
  GraphVertexGates gate1(Gates::GateAnd);
  EXPECT_EQ(gate1.getGate(), Gates::GateAnd);

  GraphVertexGates gate2(Gates::GateBuf);
  EXPECT_EQ(gate2.getGate(), Gates::GateBuf);

  GraphVertexGates gate3(Gates::GateDefault);
  EXPECT_EQ(gate3.getGate(), Gates::GateDefault);

  GraphVertexGates gate4(Gates::GateNand);
  EXPECT_EQ(gate4.getGate(), Gates::GateNand);

  GraphVertexGates gate5(Gates::GateNor);
  EXPECT_EQ(gate5.getGate(), Gates::GateNor);

  GraphVertexGates gate6(Gates::GateNot);
  EXPECT_EQ(gate6.getGate(), Gates::GateNot);

  GraphVertexGates gate7(Gates::GateOr);
  EXPECT_EQ(gate7.getGate(), Gates::GateOr);

  GraphVertexGates gate8(Gates::GateXnor);
  EXPECT_EQ(gate8.getGate(), Gates::GateXnor);

  GraphVertexGates gate9(Gates::GateXor);
  EXPECT_EQ(gate9.getGate(), Gates::GateXor);
}

TEST(TestToVerilog, CerrErrorStringIfDInConnectionsSizeIzZero) {
  GraphVertexGates  gate1(Gates::GateAnd);
  std::stringstream capturedOutput;
  std::streambuf*   originalStderr = std::cerr.rdbuf(capturedOutput.rdbuf());

  gate1.toVerilog();

  std::cerr.rdbuf(originalStderr);
  std::string output = capturedOutput.str();
  EXPECT_EQ(output, "TODO: delete empty vertices\n");
}

TEST(TestToVerilog, ReturnEmptyStringIfDInConnectionsSizeIsZero) {
  GraphVertexGates gate1(Gates::GateAnd);
  EXPECT_EQ(gate1.toVerilog(), "");
}

TEST(TestToVerilog, ThrowInvalidArgumentIfDInConnectionsLastIsDead) {
  GraphVertexGates gate1(Gates::GateAnd);
  gate1.addVertexToInConnections(nullptr);
  EXPECT_THROW(gate1.toVerilog(), std::invalid_argument);

  VertexPtr gatePtr1 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_NO_THROW(gate1.toVerilog());

  gate1.addVertexToInConnections(nullptr);
  EXPECT_THROW(gate1.toVerilog(), std::invalid_argument);
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateAnd) {
  GraphVertexGates gate1(Gates::GateAnd, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2;");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2 & Var3;");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseBuf) {
  GraphVertexGates gate1(Gates::GateBuf, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2;");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseDefault) {
  GraphVertexGates gate1(Gates::GateDefault, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr1);
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2 Error Var3;");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateNand) {
  GraphVertexGates gate1(Gates::GateNand, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 );");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 & Var3 );");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateNor) {
  GraphVertexGates gate1(Gates::GateNor, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 );");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 | Var3 );");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateNot) {
  GraphVertexGates gate1(Gates::GateNot, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~Var2;");

  // Does it correct eq?
  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~Var3;");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateOr) {
  GraphVertexGates gate1(Gates::GateOr, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2;");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2 | Var3;");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateXnor) {
  GraphVertexGates gate1(Gates::GateXnor, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 );");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = ~ ( Var2 ^ Var3 );");
}

TEST(TestToVerilog, ReturnCorrectVerilogStringWhenUseGateXor) {
  GraphVertexGates gate1(Gates::GateXor, "Var1");
  VertexPtr        gatePtr1 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var2");
  gate1.addVertexToInConnections(gatePtr1);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2;");

  VertexPtr gatePtr2 =
      std::make_shared<GraphVertexGates>(Gates::GateAnd, "Var3");
  gate1.addVertexToInConnections(gatePtr2);
  EXPECT_EQ(gate1.toVerilog(), "assign Var1 = Var2 ^ Var3;");
}

// -------------------------------------

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
  EXPECT_EQ(gate1.getInConnections()[0].lock(), ptr1);
  EXPECT_EQ(gate1.getInConnections()[1].lock(), ptr1);

  GraphVertexGates gate3(Gates::GateAnd);
  std::shared_ptr  ptr2 = std::make_shared<GraphVertexGates>(gate3);
  gate1.addVertexToInConnections(ptr2);
  EXPECT_EQ(gate1.getInConnections()[2].lock(), ptr2);
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

TEST(TestCalculateHash, SameHashWhenEqualInputs) {
  GraphVertexGates gate1(Gates::GateAnd);
  GraphVertexGates gate2(Gates::GateAnd);
  EXPECT_EQ(gate1.calculateHash(), gate2.calculateHash());

  gate1.addVertexToOutConnections(
      std::make_shared<GraphVertexGates>(Gates::GateAnd)
  );
  EXPECT_NE(gate1.calculateHash(true), gate2.calculateHash(true));
  gate2.addVertexToOutConnections(
      std::make_shared<GraphVertexGates>(Gates::GateAnd)
  );
  EXPECT_EQ(gate1.calculateHash(true), gate2.calculateHash(true));
}

TEST(TestRemoveVertexToInConnections, RemoveConnections) {
  VertexPtr gatesPtr1 = std::make_shared<GraphVertexGates>(Gates::GateAnd);
  EXPECT_EQ(gatesPtr1->removeVertexToInConnections(nullptr), false);

  gatesPtr1->addVertexToInConnections(
      std::make_shared<GraphVertexGates>(Gates::GateAnd)
  );
  gatesPtr1->addVertexToInConnections(
      std::make_shared<GraphVertexGates>(Gates::GateAnd)
  );
  EXPECT_EQ(gatesPtr1->getInConnections().size(), 2);
  EXPECT_EQ(gatesPtr1->removeVertexToInConnections(nullptr), true);
  EXPECT_EQ(gatesPtr1->getInConnections().size(), 1);
}

// // need to remake realisition of method
// // TEST(TestRemoveVertexToOutConnections, RemoveConnecttions){}
