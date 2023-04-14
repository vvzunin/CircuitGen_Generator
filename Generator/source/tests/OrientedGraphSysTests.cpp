#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../graph/OrientedGraph.h"

TEST(GeneralTest, AllFunctionsInGraphWorksCorrectlyWithEachOther)
{
    OrientedGraph example;
    EXPECT_EQ(example.size(), 0);
    example.addVertex("nor", "nor", "1");
    example.addVertex("or", "or", "2");
    example.addVertex("and", "and", "3");

    EXPECT_EQ(example.getLogicVerticesToWireName(), std::vector<std::string>({ "1", "2", "3" }));
    EXPECT_EQ(example.getMaxLevel(), 0);
    example.updateLevels();
    EXPECT_EQ(example.getMaxLevel(), 0);
    EXPECT_EQ(example.size(), 3);
    for (int i = 0; i < example.getAdjacencyMatrix().size(); i++)
    {
        for (int j = 0; j < example.getAdjacencyMatrix().size(); j++)
        {
            EXPECT_TRUE(example.getAdjacencyMatrix(i, j) == false);
        }
    }

    example.addEdge("nor", "or");
    EXPECT_EQ(example.size(), 3);
    EXPECT_EQ(example.getMaxLevel(), 0);
    EXPECT_TRUE(example.getAdjacencyMatrix(0, 1));

    example.addEdge("nor", "and");
    EXPECT_EQ(example.size(), 3);
    EXPECT_EQ(example.getMaxLevel(), 0);
    EXPECT_TRUE(example.getAdjacencyMatrix(0, 2));

    example.addEdge("or", "and");
    EXPECT_EQ(example.getMaxLevel(), 0);
    EXPECT_TRUE(example.getAdjacencyMatrix(1, 2));
    EXPECT_EQ(example.size(), 3);

    EXPECT_EQ(example.getLogicVerticesToWireName(), std::vector<std::string>({ "1", "2", "3" }));



    EXPECT_EQ(example.getIndexOfWireName("1"), 0);
    EXPECT_EQ(example.getIndexOfWireName("2"), 1);
    EXPECT_EQ(example.getIndexOfWireName("3"), 2);

    EXPECT_EQ(example.addDoubleEdge("xnor", "nor", "nor"), false);
    EXPECT_EQ(example.addDoubleEdge("or", "buf", "xor"), 0);
    EXPECT_EQ(example.addDoubleEdge("nor", "const", "const"), 0);
    EXPECT_EQ(example.addDoubleEdge("output", "buf", "input"), 0);
    EXPECT_EQ(example.addDoubleEdge("or", "buf", "output"), 0);
    EXPECT_EQ(example.addDoubleEdge("const", "input", "buf"), 0);
    EXPECT_EQ(example.addDoubleEdge("xnor", "nand", "nand"), 0);

    EXPECT_EQ(example.addEdge("xnor", "nor"), 0);
    EXPECT_EQ(example.addEdge("or", "buf"), 0);
    EXPECT_EQ(example.addEdge("nor", "const"), 0);
    EXPECT_EQ(example.addEdge("output", "buf"), 0);
    EXPECT_EQ(example.addEdge("or", "buf"), 0);
    EXPECT_EQ(example.addEdge("const", "input"), 0);
    EXPECT_EQ(example.addEdge("xnor", "nand"), 0);


    example.addVertex("output", "output", "4");
    example.addEdge("or", "output");
    example.addEdge("nor", "or");
    example.addEdge("and", "nor");
    example.updateLevels();
    EXPECT_EQ(example.getMaxLevel(), 2);

    EXPECT_EQ(example.getAdjacencyMatrix().size(), 4);

    EXPECT_EQ(example.getLogicVerticesToWireName(), std::vector<std::string>({ "1", "2", "3"}));
    
    EXPECT_EQ(example.empty(), false);

    example.setVerticeOperation(0, "xor");
    example.setVerticeOperation(1, "xnor");
    example.setVerticeOperation(2, "nand");

    EXPECT_EQ(example.getVerticesByLevel(2), std::vector<std::string>({ "and", "output"}));
    EXPECT_EQ(example.getVerticesByLevel(1), std::vector<std::string>({ "or"}));
    EXPECT_EQ(example.getVerticesByLevel(0), std::vector<std::string>({  }));
}
