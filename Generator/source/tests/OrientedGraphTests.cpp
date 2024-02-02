#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../graph/OrientedGraph.h"
#include "../generators/SimpleGenerators.h"

TEST(TestGetIndexOfExpressionWhichReturnMinusOneIfThereIsNoSuchExpressionInGraphOtherWiseReturnTheIndexOfVertix, ReturnRightIndexOfExpressionInGraphWhenWeCalledGetIndexOfExpression)
{
    OrientedGraph example;
    example.addVertex("nor", "Anything",  "Anything");// addVertex(i_expression , i_operation, i_wireName)
    example.addVertex("xor", "Anything" ,  "Anything");//When I write down Anything it means that if we replace the content it does not change anything
    example.addVertex("and", "Anything", "Anything");
    example.addVertex("nand", "Anything", "Anything");
    example.addVertex("or", "Anything", "Anything");
    example.addVertex("xnor", "Anything", "Anything");
    example.addVertex("buf", "Anything", "Anything");
    example.addVertex("not", "Anything", "Anything");
    example.addVertex("input", "Anything", "Anything");
    example.addVertex("output", "Anything", "Anything");
    example.addVertex("const", "Anything", "Anything");
    EXPECT_TRUE(example.getIndexOfExpression("nor") == 0);
    EXPECT_TRUE(example.getIndexOfExpression("xor") == 1);
    EXPECT_TRUE(example.getIndexOfExpression("and") == 2);
    EXPECT_TRUE(example.getIndexOfExpression("nand") == 3);
    EXPECT_TRUE(example.getIndexOfExpression("or") == 4);
    EXPECT_TRUE(example.getIndexOfExpression("xnor") == 5);
    EXPECT_TRUE(example.getIndexOfExpression("buf") == 6);
    EXPECT_TRUE(example.getIndexOfExpression("not") == 7);
    EXPECT_TRUE(example.getIndexOfExpression("input") == 8);
    EXPECT_TRUE(example.getIndexOfExpression("output") == 9);
    EXPECT_TRUE(example.getIndexOfExpression("const") == 10);
}

TEST(TestGetIndexOfExpressionWhichReturnMinusOneIfThereIsNoSuchExpressionInGraphOtherWiseReturnTheIndexOfVertix, ReturnMinusOneWhenWePassedExpressionThatDoesNotExistInGetIndexOfExpression)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("xor", "input",  "2");
    EXPECT_TRUE(example.getIndexOfExpression("or") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("and") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("nand") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("const") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("xnor") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("buf") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("input") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("output") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("not") == -1);
    EXPECT_TRUE(example.getIndexOfExpression("Anything") == -1);
}

TEST(TestGetIndexOfWireNameWhichReturnTheIndexOfPassedWireNameAndMinusOneWhenThereIsNoSuchWireName, getIndexOfWireNameReturnRigthIndexWhenSuchWireNameExists)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("nand", "input",  "2");
    EXPECT_TRUE(example.getIndexOfWireName("nor") == 0);
    EXPECT_TRUE(example.getIndexOfWireName("nand") == 1);
}

TEST(TestGetIndexOfWireNameWhichReturnTheIndexOfPassedWireNameAndMinusOneWhenThereIsNoSuchWireName, GetIndexOfWireNameReturnMinusOneWhenThereIsNoSuchWireName)
{
    OrientedGraph example;
    example.addVertex("nor", "input", "1");
    example.addVertex("xor", "input",  "2");
    EXPECT_TRUE(example.getIndexOfWireName("not") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("and") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("nand") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("xnor") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("or") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("Something") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("123") == -1);
    EXPECT_TRUE(example.getIndexOfWireName("") == -1);
}

TEST(TestAddVertexWhichReturnFalseIfThereAlreadyExistSuchVertexOtherwiseAddVertexToGraphAndReturnTrue, AddVertexDoesNotAddVertexWhichAlreadyExistsInGraph)
{
    OrientedGraph example;
    example.addVertex("nor", "",  "1");//Reminder: addVertex(const std::string i_vertexName, const std::string& i_operation, const std::string& i_wireName)
    example.addVertex("nor", "", "0");//Check with all operation(second parameter) and the same expresion(first parameter)
    example.addVertex("nor", "=", "1");
    example.addVertex("nor", "1'b", "2");
    example.addVertex("nor", "and", "3");
    example.addVertex("nor", "nand", "4");
    example.addVertex("nor", "or", "5");
    example.addVertex("nor", "nor", "6");
    example.addVertex("nor", "not", "7");
    example.addVertex("nor", "buf", "8");
    example.addVertex("nor", "xor", "9");
    example.addVertex("nor", "xnor", "10");
    EXPECT_EQ(example.size(), 1);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("nor"), 0);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("or", "=", "1");
    example.addVertex("or", "=", "1");
    EXPECT_EQ(example.size(), 2);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("or"), 1);// Check if the expression "or" was not replaced by anything else
    example.addVertex("xor", "=", "1");
    example.addVertex("xor", "=", "1");
    EXPECT_EQ(example.size(), 3);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("xor"), 2);// Check if the expression "xor" was not replaced by anything else
    example.addVertex("xnor", "xnor", "1");
    example.addVertex("xnor", "xnor", "1");
    EXPECT_EQ(example.size(), 4);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("xnor"), 3);// Check if the expression "xnor" was not replaced by anything else
    example.addVertex("and", "and", "1");
    example.addVertex("and", "", "1");
    EXPECT_EQ(example.size(), 5);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("and"), 4);// Check if the expression "and" was not replaced by anything else
    example.addVertex("nand", "=", "1");
    example.addVertex("nand", "=", "1");
    EXPECT_EQ(example.size(), 6);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("nand"), 5);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("not", "=", "1");
    example.addVertex("not", "=", "1");
    EXPECT_EQ(example.size(), 7);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("not"), 6);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("buf", "=", "1");
    example.addVertex("buf", "=", "1");
    EXPECT_EQ(example.size(), 8);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("buf"), 7);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("input", "=", "1");
    example.addVertex("input", "=", "1");
    EXPECT_EQ(example.size(), 9);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("input"), 8);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("output", "=", "1");
    example.addVertex("output", "=", "1");
    EXPECT_EQ(example.size(), 10);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("output"), 9);// Check if the expression "nor" was not replaced by anything else
    example.addVertex("const", "=", "1");
    example.addVertex("const", "=", "1");
    EXPECT_EQ(example.size(), 11);// The size of graph must be the same as before second addVertex
    EXPECT_EQ(example.getIndexOfExpression("const"), 10);// Check if the expression "nor" was not replaced by anything else
}

TEST(TestAddVertexWhichReturnFalseIfThereAlreadyExistSuchVertexOtherwiseAddVertexToGraphAndReturnTrue, EmptyName)
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

TEST(TestAddEdgeWhichCreatedOrientedEdgeFromFirstPassedExistingVertexEdgeToSecondPassedExistingVertexAndReturnTrueButIfOneOfThePassedVerticesDoesNotExistsWillDoNothingAndReturnFalse, AddEdgeActuallyAddEdgeBetweenTwoPassedExistingVertices)
{
    OrientedGraph example;
    example.addVertex("nor", "and",  "1");// The construction of GraphVertex made so that it do not care about i_wirename. d_wirename gonna be 
    example.addVertex("xor", "nand",  "2");// The same thing as logicExpresion gonna be when d_operation == const or d_operation == input or d_operation == output
    example.addVertex("and", "and",  "3");
    example.addVertex("nand", "and",  "5");
    example.addEdge("nor", "xor");
    EXPECT_TRUE(example.getAdjacencyMatrix(0, 1));
}

TEST(TestAddEdgeWhichCreatedOrientedEdgeFromFirstPassedVertexEdgeToSecondPassedVertexAndReturnTrueIfOneOfThePassedVerticesDoesNotExistsWillDoNothingAndReturnFalse, AddEdgeDoesNotAddRedundantEdgesToOtherVertices)
{
    OrientedGraph example;
    example.addVertex("nor", "nor",  "1");
    example.addVertex("xor", "or", "2");
    example.addVertex("nand", "nand", "3");
    example.addEdge("nor", "xor");
    EXPECT_TRUE(example.getAdjacencyMatrix(0,2) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(2, 0) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(0, 0) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(1, 2) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(2, 1) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(1, 1) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(0, 2) == false);
    EXPECT_TRUE(example.getAdjacencyMatrix(2, 2) == false);
}

TEST(TestAddEdgeWhichCreatedOrientedEdgeFromFirstPassedVertexEdgeToSecondPassedVertexAndReturnTrueIfOneOfThePassedVerticesDoesNotExistsWillDoNothingAndReturnFalse, AddEdgeDoesNothingWhenOneOfTheVerticiesDoesNotExists)
{
    OrientedGraph example;

    example.addVertex("buf", "or", "1");
    example.addVertex("or", "and", "5");
    example.addVertex("and", "nand", "3");
    example.addVertex("nand", "nor", "2");

    example.addEdge("xnor", "buf");// one non-existing vertex

    for (int i = 0; i < example.getAdjacencyMatrix().size(); i++)
    {
        for (int j = 0; j < example.getAdjacencyMatrix().size(); j++)
        {
            EXPECT_TRUE(example.getAdjacencyMatrix(i, j) == false);
        }
    }

    EXPECT_TRUE(example.size() == 4);

    EXPECT_TRUE(example.getIndexOfExpression("buf") == 0);// Check that the content of the Graph was not changed
    EXPECT_TRUE(example.getIndexOfExpression("or") == 1);
    EXPECT_TRUE(example.getIndexOfExpression("and") == 2);
    EXPECT_TRUE(example.getIndexOfExpression("nand") == 3);

    example.addEdge("xor", "xnor");// two non-existing verticies

    for (int i = 0; i < example.getAdjacencyMatrix().size(); i++)
    {
        for (int j = 0; j < example.getAdjacencyMatrix().size(); j++)
        {
            EXPECT_TRUE(example.getAdjacencyMatrix(i, j) == false);
        }
    }

    EXPECT_TRUE(example.size() == 4);

    EXPECT_TRUE(example.getIndexOfExpression("buf") == 0);// Check that the content of the Graph was not changed
    EXPECT_TRUE(example.getIndexOfExpression("or") == 1);
    EXPECT_TRUE(example.getIndexOfExpression("and") == 2);
    EXPECT_TRUE(example.getIndexOfExpression("nand") == 3);
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

TEST(TestGetVerticeByTypeWhichGetTheOperationAsInputAndAfterThatReturnTheVectorWithVerticiesWhichHaveSuchOperation, getVerticesByTypeReturnEmptyVectorWhenThereAreNoVerticiesInGraphWhichHasSuchOperation)
{
    OrientedGraph example;
    example.addVertex("nand", "nand", "1");
    example.addVertex("nor"  "nor", "2");
    example.addVertex("or", "or", "3");
    EXPECT_TRUE(example.getVerticesByType("xor").empty());
    EXPECT_TRUE(example.getVerticesByType("not").empty());
    EXPECT_TRUE(example.getVerticesByType("buf").empty());
    EXPECT_TRUE(example.getVerticesByType("xnor").empty());
    EXPECT_TRUE(example.getVerticesByType("and").empty());
    EXPECT_TRUE(example.getVerticesByType("").empty());
    EXPECT_TRUE(example.getVerticesByType("=").empty());
    EXPECT_TRUE(example.getVerticesByType("1'b").empty());
}

TEST(TestGetVerticeByTypeWhichGetTheOperationAsInputAndAfterThatReturnTheVectorWithVerticiesWhichHaveSuchOperation, getVerticeByTypeReturnEmptyVectorWhenThereAreNoVerticiesInGraph)
{
    OrientedGraph example;
    EXPECT_TRUE(example.getVerticesByType("and").empty());
    EXPECT_TRUE(example.getVerticesByType("nand").empty());
    EXPECT_TRUE(example.getVerticesByType("xor").empty());
    EXPECT_TRUE(example.getVerticesByType("nor").empty());
    EXPECT_TRUE(example.getVerticesByType("or").empty());
    EXPECT_TRUE(example.getVerticesByType("").empty());
    EXPECT_TRUE(example.getVerticesByType("=").empty());
    EXPECT_TRUE(example.getVerticesByType("xnor").empty());
    EXPECT_TRUE(example.getVerticesByType("1'b").empty());
    EXPECT_TRUE(example.getVerticesByType("and").empty());
    EXPECT_TRUE(example.getVerticesByType("not").empty());
}

TEST(TestGetVerticeByTypeWhichGetTheOperationAsInputAndAfterThatReturnTheVectorWithVerticiesWhichHaveSuchOperation, getVerticeByTypeNormalTest)
{
    OrientedGraph example;
    example.addVertex("1", "nor", "anything");
    example.addVertex("2", "or", "anything");
    example.addVertex("3", "or", "anything");
    example.addVertex("4", "nand", "anything");
    example.addVertex("5", "nand", "anything");
    example.addVertex("6", "buf", "anything");
    example.addVertex("7", "and", "anything");
    example.addVertex("8", "xor", "anything");
    example.addVertex("9", "not", "anything");
    example.addVertex("10", "not", "anything");
    example.addVertex("11", "not", "anything");
    EXPECT_EQ(example.getVerticesByType("or"), std::vector<std::string>({ std::string("2"), std::string("3") }));
    EXPECT_EQ(example.getVerticesByType("buf"), std::vector<std::string>({ std::string("6") }));
    EXPECT_EQ(example.getVerticesByType("nor"), std::vector<std::string>({ std::string("1") }));
    EXPECT_EQ(example.getVerticesByType("nand"), std::vector<std::string>({ std::string("4") , std::string("5") }));
    EXPECT_EQ(example.getVerticesByType(""), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("not"), std::vector<std::string>({ std::string("9"), std::string("10") , std::string("11") }));

}

TEST(TestGetVerticeByTypeToWireName, NamesWasNotFound)
{
    OrientedGraph example;
    example.addVertex("anything", "nor", "1");
    example.addVertex("anything", "xor", "2");
    example.addVertex("anything", "nor", "3");
    example.addVertex("anything", "and", "4");
    example.addVertex("anything", "nand", "5");
    EXPECT_EQ(example.getVerticesByType("not"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("or"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("buf"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("xnor"), std::vector<std::string>({  }));

}

TEST(TestGetVerticeByTypeToWireName, EmptyGraph)
{
    OrientedGraph example;
    EXPECT_EQ(example.getVerticesByType("not"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("or"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("buf"), std::vector<std::string>({  }));
    EXPECT_EQ(example.getVerticesByType("xnor"), std::vector<std::string>({  }));

}

TEST(TestGetVerticeByTypeToWireName, NormalTest)
{
    OrientedGraph example;
    example.addVertex("1", "input", "1");
    example.addVertex("2", "input", "2");
    example.addVertex("3", "input", "3");
    example.addVertex("4", "input", "4");
    example.addVertex("5", "const", "5");
    example.addVertex("6", "const", "6");
    example.addVertex("7", "const", "7");
    example.addVertex("8", "const", "8");
    example.addVertex("9", "const", "9");
    example.addVertex("10", "output", "10");
    example.addVertex("11", "output", "11");
    example.addVertex("12", "output", "12");
    example.addVertex("13", "output", "13");
    EXPECT_EQ(example.getVerticesByTypeToWireName("input"), std::vector<std::string>({ "1" ,"2" ,  "3" , "4"}));
    EXPECT_EQ(example.getVerticesByTypeToWireName("const"), std::vector<std::string>({ "5" , "6" , "7" , "8" , "9"}));
    EXPECT_EQ(example.getVerticesByTypeToWireName("output"), std::vector<std::string>({ "10" , "11" , "12" , "13" }));
}

TEST(TestGetLogicVerticesToWireName, NamesWasNotFound)
{
    OrientedGraph example;
    example.addVertex("11", "const", "11");
    example.addVertex("12", "input", "12");
    example.addVertex("13", "output", "13");
    EXPECT_EQ(example.getLogicVerticesToWireName(), std::vector<std::string>({ }));
}

TEST(TestGetLogicVerticesToWireName, EmptyGraph)
{
    OrientedGraph example;
    EXPECT_EQ(example.getLogicVerticesToWireName(), std::vector<std::string>({ }));
}

TEST(TestGetLogicVerticesToWireName, NormalTest)
{
    OrientedGraph example;
    example.addVertex("1", "nor", "1");
    example.addVertex("2", "or", "2");
    EXPECT_EQ(example.getLogicVerticesToWireName().size(), 2);// When we push nor and or we expect that both will be included in output of getLogicVerticesToWireName
    example.addVertex("3", "const", "3");
    example.addVertex("4", "const", "4");
    EXPECT_EQ(example.getLogicVerticesToWireName().size(), 2);// When we added const there are nothing must be changed in output of getLogicVerticesToWireName
    example.addVertex("5", "nand", "5");
    example.addVertex("6", "input", "6");
    EXPECT_EQ(example.getLogicVerticesToWireName().size(), 3);// The same logic as before with input because input obeys the same rules as const. nand have to be included in output of getLogicVerticesToWireName 
    example.addVertex("7", "output", "7");
    EXPECT_EQ(example.getLogicVerticesToWireName().size(), 3);// output obeys the same rules as const. See definition of getLogicVerticesToWireName
   
    
}

TEST(TestGetVerticesByLevel, WithNonExistingLevel)
{
    OrientedGraph example;
    example.addVertex("1", "nor", "1");
    EXPECT_EQ(example.getVerticesByLevel(6), std::vector<std::string>({  }));
    example.addVertex("2", "or", "2");
    EXPECT_EQ(example.getVerticesByLevel(6), std::vector<std::string>({  }));
    example.addVertex("3", "nor", "3");
    example.addEdge("1" , "2");
    example.addEdge("1", "3");
    example.updateLevels();
    EXPECT_EQ(example.getVerticesByLevel(6), std::vector<std::string>({  }));
    example.addVertex("4", "xor", "4");
    EXPECT_EQ(example.getVerticesByLevel(3), std::vector<std::string>({  }));
    example.addVertex("5", "and", "5");
    EXPECT_EQ(example.getVerticesByLevel(5), std::vector<std::string>({  }));
    example.addVertex("6", "nand", "6");
    EXPECT_EQ(example.getVerticesByLevel(4), std::vector<std::string>({  }));
    example.addVertex("7", "not", "7");
    EXPECT_EQ(example.getVerticesByLevel(3), std::vector<std::string>({  }));
    example.addVertex("8", "nor", "8");
    EXPECT_EQ(example.getVerticesByLevel(111), std::vector<std::string>({  }));
}

TEST(TestGetVerticesByLevel, WithExistingLevel)
{
    OrientedGraph example;
    example.addVertex("1", "input", "1");
    example.addVertex("2", "or", "2");
    example.addEdge("1", "2");
    example.updateLevels();
    EXPECT_EQ(example.getVerticesByLevel(1), std::vector<std::string>({"2"}));
}

TEST(TestGetVerticesByLevel, EmptyGraph)
{
    OrientedGraph example;
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(example.getVerticesByLevel(i), std::vector<std::string>({  }));

}

TEST(TestGetVerticesByLevel, NormalTest)
{
    OrientedGraph example;
    example.addVertex("1", "nor", "1");
    EXPECT_EQ(example.getVerticesByLevel(0), std::vector<std::string>({ "1" }));
    example.addVertex("2", "or", "2");
    example.updateLevels();
    EXPECT_EQ(example.getVerticesByLevel(0), std::vector<std::string>({ "1" , "2" }));
    example.addVertex("3", "nor", "3");// Current vertex
    example.addEdge("1", "3");// Now the level of the current vertex equal to 1
    EXPECT_EQ(example.getVerticesByLevel(1), std::vector<std::string>({ "3" }));
    example.addVertex("4", "xor", "4");// Current vertex
    example.addEdge("2" , "4");// Now the level of the current vertex equal to 1
    EXPECT_EQ(example.getVerticesByLevel(1), std::vector<std::string>({ "3" , "4" }));
    example.addVertex("5", "and", "5");// Current vertex
    example.addEdge("1" , "5"); // Now the level of the current vertex equal to 1
    EXPECT_EQ(example.getVerticesByLevel(1), std::vector<std::string>({ "3" , "4" , "5" }));
    example.addVertex("6", "nand", "6");// Current vertex
    example.addEdge("3" , "6");// Now the level of the current vertex equal to 2
    EXPECT_EQ(example.getVerticesByLevel(2), std::vector<std::string>({ "6" }));
    example.addVertex("7", "not", "7");// Current vertex
    example.addEdge("3" , "7");// Now the level of the current vertex equal to 2
    EXPECT_EQ(example.getVerticesByLevel(2), std::vector<std::string>({ "6" , "7" }));
}

// Because of incapsulation we gonna test ConnectedTo  indirectly.
TEST(TestGetConnectedTo, NormalTest)
{
    OrientedGraph example;
    example.addVertex("1", "nor", "1");
    example.addVertex("2", "or", "2");
    example.addEdge("1" , "2" , true);
    example.addVertex("3", "xor", "3");
    example.addVertex("4", "nor", "4");
    example.addEdge("3", "4", true);
    example.addEdge("3", "2", true);
    example.addEdge("2", "3", true);
    example.addVertex("5", "and", "5");
    example.addVertex("6", "nand", "6");
    EXPECT_EQ(example.getMaxLevel(), 0);
}

TEST(TestUpdateLevels, NormalTest)
{
    OrientedGraph example;
    example.addVertex("0", "and", "0");
    example.addVertex("1", "nor", "1");
    example.addVertex("2", "output", "2");
    example.addVertex("3", "output", "3");
    example.addVertex("4", "nor", "4");
    example.addVertex("5", "and", "5");
    example.addVertex("6", "nand", "6");
    example.updateLevels();
    EXPECT_EQ(example.getMaxLevel(), 0);
    example.addEdge("1", "2");
    example.updateLevels();
    EXPECT_EQ(example.getMaxLevel(), 1);
    example.addEdge("2", "3");
    example.updateLevels();
    EXPECT_EQ(example.getMaxLevel(), 2);

}

TEST(TestExtendFunc, PreviuosTestForExtend)
{
    SimpleGenerators S_gen_1;
    OrientedGraph graph_1 = S_gen_1.generatorDecoder(4);
    OrientedGraph ex_graph;
    ex_graph.Extend(S_gen_1.generatorDecoder(4));
    EXPECT_FALSE(graph_1 == ex_graph);
}

TEST(TestDeleteFunc, PreviuosTestForDelete)
{
    SimpleGenerators S_gen;
    OrientedGraph graph_1 = S_gen.generatorDecoder(2);
    OrientedGraph graph_2 = S_gen.generatorDecoder(2);
    EXPECT_TRUE(graph_1 == graph_2);
    graph_1.Delete("x_a0", false);
    EXPECT_FALSE(graph_1 == graph_2);
}
