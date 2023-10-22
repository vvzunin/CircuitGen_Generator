#include <gtest/gtest.h>
#include "../graph/GraphVertex.h"

TEST(test_graph_vertex, test_init)
{
  GraphVertex v = GraphVertex("testexpr", "testoper", false, "testwirename");
  EXPECT_EQ(true, true);
}

class GraphVertexTest: public testing::Test
{
protected:
	void SetUp()
	{
		vertex = std::make_unique<GraphVertex>("or", "or");
	}
	void TearDown()
	{
		vertex = std::make_unique<GraphVertex>("or", "or");
	}
	std::unique_ptr<GraphVertex> vertex;
};

TEST_F(GraphVertexTest, setValueAndGetValueWorksCorrectly)
{
	vertex->setValue(false);
	EXPECT_EQ(vertex->getValue(), false);
	
	vertex->setValue(true);
	EXPECT_EQ(vertex->getValue(), true);
}

TEST_F(GraphVertexTest, setLevelAndGetLevelWorksCorrectly)
{
	for (int i = 0; i < 50; i++)
	{
		vertex->setLevel(i);
		ASSERT_EQ(vertex->getLevel(), i);
	}
}



TEST_F(GraphVertexTest, setLogicExpressionAndGetLogicExpressionWorksCorrectly)
{
	for (int i = 0; i < 50; i++)
	{
		vertex->setLogicExpression(std::to_string(i));
		ASSERT_EQ(vertex->getLogicExpression(), std::to_string(i));
	}
}

