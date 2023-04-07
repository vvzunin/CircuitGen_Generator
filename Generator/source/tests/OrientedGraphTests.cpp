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