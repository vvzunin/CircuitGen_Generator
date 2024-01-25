#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../generators/SimpleGenerators.h"

TEST(EqualGenerateParity, EqualToEachOver)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorParity(2);
    OrientedGraph graph_2 = S_gen_2.generatorParity(2);
    EXPECT_TRUE(graph_1 == graph_2);
    OrientedGraph graph_1 = S_gen_1.generatorParity(10);
    OrientedGraph graph_2 = S_gen_2.generatorParity(10);
    EXPECT_TRUE(graph_1 == graph_2);
}
TEST(EqualGenerateParity, DifferentFromEachOthe)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorParity(4);
    OrientedGraph graph_2 = S_gen_2.generatorParity(5);
    EXPECT_FALSE(graph_1 == graph_2);
    OrientedGraph graph_1 = S_gen_1.generatorParity(10);
    OrientedGraph graph_2 = S_gen_2.generatorParity(2);
    EXPECT_FALSE(graph_1 == graph_2);
}