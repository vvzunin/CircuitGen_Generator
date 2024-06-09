#include <filesystem>

#include "baseStructures/graph/GraphVertex.hpp"

#include <gtest/gtest.h>

#include "additional/filesTools/FilesTools.hpp"

TEST(TestConstructorWithoutIName, WithoutDefaulParametrs) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);
  std::string         graphNum = std::to_string(0);
  EXPECT_EQ(subGraph1.getType(), VertexTypes::subGraph);
  EXPECT_EQ(subGraph1.getTypeName(), "subGraph");
  EXPECT_EQ(subGraph1.getName(), "subGraph_" + graphNum);
  EXPECT_EQ(subGraph1.getLevel(), 0);
  EXPECT_EQ(subGraph1.getValue(), 'x');
  EXPECT_EQ(subGraph1.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(subGraph1.getOutConnections().size(), 0);
}

TEST(TestConstructorWithoutIName, WithDefaultInputParametrs) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, graphPtr2);
  std::string         graphNum = std::to_string(1);
  EXPECT_EQ(subGraph1.getType(), VertexTypes::subGraph);
  EXPECT_EQ(subGraph1.getTypeName(), "subGraph");
  EXPECT_EQ(subGraph1.getName(), "subGraph_" + graphNum);
  EXPECT_EQ(subGraph1.getLevel(), 0);
  EXPECT_EQ(subGraph1.getValue(), 'x');
  EXPECT_EQ(subGraph1.getBaseGraph().lock(), graphPtr2);
  EXPECT_EQ(subGraph1.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithoutDefaultInputParametrs) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything");
  EXPECT_EQ(subGraph1.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(subGraph1.getType(), VertexTypes::subGraph);
  EXPECT_EQ(subGraph1.getTypeName(), "subGraph");
  EXPECT_EQ(subGraph1.getName(), "Anything");
  EXPECT_EQ(subGraph1.getLevel(), 0);
  EXPECT_EQ(subGraph1.getValue(), 'x');
  EXPECT_EQ(subGraph1.getBaseGraph().lock(), nullptr);
  EXPECT_EQ(subGraph1.getOutConnections().size(), 0);
}

TEST(TestConstructorWithIName, WithDefaultInputParametrs) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);
  EXPECT_EQ(subGraph1.getType(), VertexTypes::subGraph);
  EXPECT_EQ(subGraph1.getTypeName(), "subGraph");
  EXPECT_EQ(subGraph1.getName(), "Anything");
  EXPECT_EQ(subGraph1.getLevel(), 0);
  EXPECT_EQ(subGraph1.getValue(), 'x');
  EXPECT_EQ(subGraph1.getBaseGraph().lock(), graphPtr2);
  EXPECT_EQ(subGraph1.getOutConnections().size(), 0);
}
// ------------------------OverrideMethodsTests
TEST(TestUpdateValue, Test) {
  VertexPtr subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  EXPECT_EQ(subGraphPtr1->updateValue(), 'x');
}
// return "DO NOT CALL IT" TEST(TestToVerilog, TestReturnString) {}
TEST(TestToVerilog, TestReturnPairThereIsNoBaseGraph) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything");
  EXPECT_THROW(subGraph1.toVerilog("path"), std::invalid_argument);
}

TEST(TestToVerilog, TestReturnPairWrongPath) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);

  std::stringstream   capturedOutput;
  std::streambuf*     originalStderr = std::cerr.rdbuf(capturedOutput.rdbuf());
  subGraph1.toVerilog("wrong_path");

  std::cerr.rdbuf(originalStderr);
  std::string output = capturedOutput.str();
  EXPECT_EQ(output, "cannot write file to wrong_path\n");
}

TEST(TestToVerilog, TestReturnPairCreateCorrectFile) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("testGraph");
  graphPtr1->addConst('x', "testConst");
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);
  std::string         curPath  = std::filesystem::current_path();
  std::string         fileName = "testGraph.v";
  EXPECT_EQ(subGraph1.toVerilog(curPath, fileName).first, true);
  EXPECT_EQ(subGraph1.toVerilog(std::filesystem::current_path()).second, "");
  EXPECT_EQ(
      FilesTools::loadStringFile(curPath + '/' + fileName),
      "module testGraph(\n"
      "  \n"
      "  );\n"
      "          \n"
      "  wire testConst;\n"
      "  assign testConst = 1'bx;"
      "\n\n"
      "endmodule\n"
  );
  std::filesystem::remove(curPath + '/' + fileName);
}

TEST(Test, Test) {}
TEST(TestToGraphML, Test) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("testGraph");
  graphPtr1->addConst('x', "testConst");
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);

  EXPECT_EQ(
      subGraph1.toGraphML(),
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
      "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
      "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
      "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n"
      "  <key id=\"t\" for=\"node\" attr.name=\"type\" "
      "attr.type=\"string\"/>\n  <graph id=\"testGraph\" "
      "edgedefault=\"directed\">\n"
      "    <node id=\"testConst\">\n"
      "      <data key=\"t\">x</data>\n"
      "    </node>\n"
      "  </graph>\n"
      "</graphml>\n"
  );
}
// TEST(TestgGetInstance, Test) {}
TEST(TestCalculateHash, Test) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("testGraph");
  graphPtr1->addConst('x', "testConst");
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);

  GraphPtr            graphPtr3 = std::make_shared<OrientedGraph>("testGraph");
  graphPtr1->addConst('x', "testConst");
  GraphPtr            graphPtr4 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph2(graphPtr1, "Anything", graphPtr2);

  EXPECT_EQ(subGraph1.calculateHash(), subGraph2.calculateHash());
}
TEST(TestSetSubGrahGetSubgraph, Test) {
  GraphPtr graphPtr1 = std::make_shared<OrientedGraph>("testGraph");
  graphPtr1->addConst('x', "testConst");
  GraphPtr            graphPtr2 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1, "Anything", graphPtr2);

  EXPECT_EQ(subGraph1.getSubGraph(), graphPtr1);
  subGraph1.setSubGraph(graphPtr2);
  EXPECT_EQ(subGraph1.getSubGraph(), graphPtr2);
}
// -------------------------------------

TEST(TestSetName, InputCorrectName) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);
  subGraph1.setName("Anything");
  EXPECT_EQ(subGraph1.getName(), "Anything");
}

TEST(TestAddInConnections, AddConnections) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);
  EXPECT_EQ(subGraph1.getInConnections().size(), 0);

  VertexPtr subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  EXPECT_EQ(subGraph1.addVertexToInConnections(subGraphPtr1), 1);
  EXPECT_EQ(subGraph1.addVertexToInConnections(subGraphPtr1), 2);
  EXPECT_EQ(subGraph1.getInConnections()[0].lock(), subGraphPtr1);
  EXPECT_EQ(subGraph1.getInConnections()[1].lock(), subGraphPtr1);

  VertexPtr subGraphPtr2 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraph1.addVertexToInConnections(subGraphPtr2);
  EXPECT_EQ(subGraph1.getInConnections()[2].lock(), subGraphPtr2);
}

TEST(TestAddOutConnections, AddConnections) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);
  EXPECT_EQ(subGraph1.getOutConnections().size(), 0);

  VertexPtr subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  EXPECT_EQ(subGraph1.addVertexToOutConnections(subGraphPtr1), true);
  EXPECT_EQ(subGraph1.addVertexToOutConnections(subGraphPtr1), false);
  EXPECT_EQ(subGraph1.getOutConnections()[0], subGraphPtr1);

  VertexPtr subGraphPtr2 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraph1.addVertexToOutConnections(subGraphPtr2);
  EXPECT_EQ(subGraph1.getOutConnections()[1], subGraphPtr2);
}

TEST(TestRemoveVertexToInConnections, RemoveConnections) {
  VertexPtr subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  EXPECT_EQ(subGraphPtr1->removeVertexToInConnections(nullptr), false);

  subGraphPtr1->addVertexToInConnections(
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>())
  );
  subGraphPtr1->addVertexToInConnections(
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>())
  );
  EXPECT_EQ(subGraphPtr1->getInConnections().size(), 2);
  EXPECT_EQ(subGraphPtr1->removeVertexToInConnections(nullptr), true);
  EXPECT_EQ(subGraphPtr1->getInConnections().size(), 1);
}

TEST(TestUpdateLevel, UpdateLevelCorrect) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);
  VertexPtr           subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraphPtr1->setLevel(1);
  subGraph1.addVertexToInConnections(subGraphPtr1);
  subGraph1.updateLevel();
  EXPECT_EQ(subGraph1.getLevel(), 2);

  VertexPtr subGraphPtr2 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  VertexPtr subGraphPtr3 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraphPtr2->setLevel(3);
  subGraphPtr3->setLevel(2);
  subGraph1.addVertexToInConnections(subGraphPtr2);
  subGraph1.addVertexToInConnections(subGraphPtr3);
  subGraph1.updateLevel();
  EXPECT_EQ(subGraph1.getLevel(), 4);

  VertexPtr subGraphPtr4 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraph1.addVertexToInConnections(subGraphPtr4);
  subGraph1.updateLevel();
  EXPECT_EQ(subGraph1.getLevel(), 4);
}

TEST(TestUpdateLevel, ThrowInvalidArgumentIfDInconnectionsNIsNullptr) {
  GraphPtr            graphPtr1 = std::make_shared<OrientedGraph>();
  GraphVertexSubGraph subGraph1(graphPtr1);

  VertexPtr           subGraphPtr1 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  VertexPtr subGraphPtr2 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraph1.addVertexToInConnections(subGraphPtr1);
  subGraph1.addVertexToInConnections(subGraphPtr2);
  EXPECT_NO_THROW(subGraph1.updateLevel());

  subGraph1.addVertexToInConnections(nullptr);
  EXPECT_THROW(subGraph1.updateLevel(), std::invalid_argument);

  VertexPtr subGraphPtr3 =
      std::make_shared<GraphVertexSubGraph>(std::make_shared<OrientedGraph>());
  subGraph1.addVertexToInConnections(subGraphPtr3);
  EXPECT_THROW(subGraph1.updateLevel(), std::invalid_argument);
}
