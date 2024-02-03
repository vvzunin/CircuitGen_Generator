#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../generators/SimpleGenerators.h"

TEST(EqualGenerateComparison, EqualToEachOver)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorComparison(2, true, false, true, false);
    OrientedGraph graph_2 = S_gen_2.generatorComparison(2, true, false, true, false);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorComparison(10, false, false, true, true);
    graph_2 = S_gen_2.generatorComparison(10, false, false, true, true);
    EXPECT_TRUE(graph_1 == graph_2);
}
TEST(EqualGenerateComparison, DifferentFromEachOthe)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorComparison(4, true, false, true, false);
    OrientedGraph graph_2 = S_gen_2.generatorComparison(5, true, false, true, false);
    EXPECT_FALSE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorComparison(4, true, false, true, true);
    graph_2 = S_gen_2.generatorComparison(4, true, false, true, false);
    EXPECT_FALSE(graph_1 == graph_2);
}