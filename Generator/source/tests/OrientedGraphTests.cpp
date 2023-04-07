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
TEST(TestGetVerticeByType, EmptyGraph)
{
    OrientedGraph example;
    EXPECT_TRUE(example.getVerticesByType("and").empty());
}
TEST(TestGetVerticeByType, NormalTest)
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
