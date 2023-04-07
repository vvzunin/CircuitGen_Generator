#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../graph/OrientedGraph.h"

TEST(TestGetIndexOfExpression, ExpressionExists)
{
    OrientedGraph example;
    example.addVertex("nor", "input",  "1");
    example.addVertex("xor", "input" ,  "2");
    EXPECT_TRUE(example.getIndexOfExpression("nor") != -1);
}
TEST(TestGetIndexOfExpression, ExpressionDoesNotExist)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("xor", "input",  "2");
    EXPECT_TRUE(example.getIndexOfExpression("or") == -1);
}
TEST(TestGetIndexOfWireName, NameExists)
{
    OrientedGraph example;
    example.addVertex("1", "input", "1");
    example.addVertex("2", "input",  "2");
    EXPECT_TRUE(example.getIndexOfWireName("2") != -1);
}
TEST(TestGetIndexOfWireName, NameDoesNotExist)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("xor", "input",  "2");
    EXPECT_TRUE(example.getIndexOfWireName("0") == -1);
}
TEST(TestAddVertex, ReturnAtFirstLine)
{
    OrientedGraph example;
    example.addVertex("nor", "input",  "1");
    example.addVertex("xor", "input",   "2");
    EXPECT_TRUE(example.addVertex("nor", "Anything",  "Anything") == false);
}
TEST(TestAddVertex, EmptyName)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("xor", "input",  "2");
    EXPECT_TRUE(example.addVertex("", "Anything", "Anything") == true);
}
TEST(TestAddVertex, NonEmptyName)
{
    OrientedGraph example;
    example.addVertex("nor", "const", "1");
    example.addVertex("xor", "const",  "2");
    EXPECT_TRUE(example.addVertex("NonEmptyString", "Anything",  "Anything") == true);
}
TEST(TestAddEdge, ExpressionFalse)
{
    OrientedGraph example;
    example.addVertex("1", "const",  "Anything");// The construction of GraphVertex made so that it do not care about i_wirename. d_wirename gonna be 
                                                 // The same thing as logicExpresion gonna be when d_operation == const or d_operation == input or d_operation == output
    example.addVertex("5", "const",  "Anything");
    example.addVertex("3", "output",  "Anything");
    example.addVertex("2", "output",  "Anything");
    EXPECT_TRUE(example.addEdge("1", "5", false) == true);
    EXPECT_TRUE(example.addEdge("2", "3", false) == true);
}
TEST(TestAddEdge, ExpressionTrue)
{
    OrientedGraph example;
    example.addVertex("nor", "nor",  "1");
    example.addVertex("nor", "nor", "5");
    example.addVertex("nand", "nand", "3");
    example.addVertex("xor", "xor", "2");
    EXPECT_TRUE(example.addEdge("nor", "xor", true) == true);
}
TEST(TestAddEdge, OneOfTheVerticiesDoesNotExists)
{
    OrientedGraph example;
    example.addVertex("1", "or", "1");
    example.addVertex("5", "and", "5");
    example.addVertex("3", "nand", "3");
    example.addVertex("2", "nor", "2");
    EXPECT_TRUE(example.addEdge("nor", "xor", true) == false);
}
TEST(TestAddDoubleEdge, ExpressionTrue)
{
    OrientedGraph example;
    example.addVertex("1", "const", "1");
    example.addVertex("2", "const", "2");
    example.addVertex("3", "const", "3");
    EXPECT_TRUE(example.addDoubleEdge("1", "2", "3", false) == true);
}
TEST(TestAddDoubleEdge, ExpressionFalse)
{
    OrientedGraph example;
    example.addVertex("1", "const", "1");
    example.addVertex("2", "const", "2");
    example.addVertex("3", "const", "3");
    example.addVertex("6", "const", "6");
    example.addVertex("5", "input", "5");
    example.addVertex("4", "input", "4");
    example.addVertex("7", "input", "7");
    EXPECT_TRUE(example.addDoubleEdge("1", "2", "3", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("1", "3", "2", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("2", "1", "3", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("1", "2", "3", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("6", "5", "3", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("2", "5", "4", false) == true);
    EXPECT_TRUE(example.addDoubleEdge("4", "3", "2", false) == true);

}
TEST(TestAddDoubleEdge, OneOfTheVerticiesDoesNotExists)
{
    OrientedGraph example;
    example.addVertex("1", "or", "1");
    example.addVertex("2", "nor", "2");
    example.addVertex("3", "nor", "3");
    EXPECT_TRUE(example.addDoubleEdge("nor", "or", "and", true) == false);
    EXPECT_TRUE(example.addDoubleEdge("nor", "or", "nand", true) == false);
    EXPECT_TRUE(example.addDoubleEdge("nor", "nand", "or", true) == false);
    EXPECT_TRUE(example.addDoubleEdge("nand", "or", "xor", true) == false);
    EXPECT_TRUE(example.addDoubleEdge("not", "or", "nand", true) == false);
}
TEST(TestGetVerticeByType, NamesWasNotFound)
{
    OrientedGraph example;
    example.addVertex("1", "or", "1");
    example.addVertex("2"  "nand", "2");
    example.addVertex("3", "and", "3");
    EXPECT_TRUE(example.getVerticesByType("xor").empty());
    EXPECT_TRUE(example.getVerticesByType("not").empty());
    EXPECT_TRUE(example.getVerticesByType("buf").empty());
    EXPECT_TRUE(example.getVerticesByType("xnor").empty());
}