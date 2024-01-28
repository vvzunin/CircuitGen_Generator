#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../generators/SimpleGenerators.h"

TEST(EqualGenerateDecoder, EqualToEachOver)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorDecoder(2);
    OrientedGraph graph_2 = S_gen_2.generatorDecoder(2);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorDecoder(10);
    graph_2 = S_gen_2.generatorDecoder(10);
    EXPECT_TRUE(graph_1 == graph_2);
}
TEST(EqualGenerateDecoder, DifferentFromEachOthe)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    OrientedGraph graph_1 = S_gen_1.generatorDecoder(4);
    OrientedGraph graph_2 = S_gen_2.generatorDecoder(5);
    EXPECT_FALSE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorDecoder(10);
    graph_2 = S_gen_2.generatorDecoder(2);
    EXPECT_FALSE(graph_1 == graph_2);  
}
