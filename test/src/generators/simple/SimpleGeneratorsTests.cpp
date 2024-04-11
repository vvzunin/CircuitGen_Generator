#include "src/generators/simple/SimpleGenerators.hpp"

#include <gtest/gtest.h>

//CNF RandLevel NumOperations was made in branch tests

TEST(GeneratorParityTest, EqualToEachOther) {
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    std::shared_ptr<OrientedGraph> graph_1 = S_gen_1.generatorParity(2);
    std::shared_ptr<OrientedGraph> graph_2 = S_gen_2.generatorParity(2);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorParity(10);
    graph_2 = S_gen_2.generatorParity(10);
    EXPECT_TRUE(graph_1 == graph_2);
}

TEST(GeneratorComparisonTest, EqualToEachOver)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    std::shared_ptr<OrientedGraph> graph_1 = S_gen_1.generatorComparison(2, true, false, true, false);
    std::shared_ptr<OrientedGraph> graph_2 = S_gen_2.generatorComparison(2, true, false, true, false);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorComparison(10, false, false, true, true);
    graph_2 = S_gen_2.generatorComparison(10, false, false, true, true);
    EXPECT_TRUE(graph_1 == graph_2);
}
TEST(GeneratorComparisonTest, DifferentFromEachOthe)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    std::shared_ptr<OrientedGraph> graph_1 = S_gen_1.generatorComparison(4, true, false, true, false);
    std::shared_ptr<OrientedGraph> graph_2 = S_gen_2.generatorComparison(5, true, false, true, false);
    EXPECT_FALSE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorComparison(4, true, false, true, true);
    graph_2 = S_gen_2.generatorComparison(4, true, false, true, false);
    EXPECT_FALSE(graph_1 == graph_2);
}
TEST(GeneratorDecoderTest, EqualToEachOver)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    std::shared_ptr<OrientedGraph> graph_1 = S_gen_1.generatorDecoder(2);
    std::shared_ptr<OrientedGraph> graph_2 = S_gen_2.generatorDecoder(2);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorDecoder(10);
    graph_2 = S_gen_2.generatorDecoder(10);
    EXPECT_TRUE(graph_1 == graph_2);
}
TEST(lGeneratorDecoderTest, DifferentFromEachOther)
{
    SimpleGenerators S_gen_1;
    SimpleGenerators S_gen_2;
    std::shared_ptr<OrientedGraph> graph_1 = S_gen_1.generatorDecoder(4);
    std::shared_ptr<OrientedGraph> graph_2 = S_gen_2.generatorDecoder(5);
    EXPECT_FALSE(graph_1 == graph_2);
    graph_1 = S_gen_1.generatorDecoder(10);
    graph_2 = S_gen_2.generatorDecoder(2);
    EXPECT_FALSE(graph_1 == graph_2);  
}
