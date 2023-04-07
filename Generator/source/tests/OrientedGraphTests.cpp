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

