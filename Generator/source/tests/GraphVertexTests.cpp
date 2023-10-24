#include <gtest/gtest.h>
#include "../graph/GraphVertex.h"
#include <thread>
#include <functional>
#include <memory>

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
		for (auto& el : vertexes)
		{
			el = std::make_shared<GraphVertex>("or", "or");
		}
		vertex = std::make_shared<GraphVertex>("or", "or");
	}
	void TearDown()
	{
		for (auto& el : vertexes)
		{
			el = std::make_shared<GraphVertex>("or", "or");
		}
		vertex = std::make_shared<GraphVertex>("or", "or");
	}
	std::vector<std::shared_ptr<GraphVertex>> vertexes;
	std::shared_ptr<GraphVertex> vertex;
};

TEST_F(GraphVertexTest, setValueAndGetValueWorksCorrectly)
{
	vertex->setValue(false);
	EXPECT_EQ(vertex->getValue(), false);
	
	vertex->setValue(true);
	EXPECT_EQ(vertex->getValue(), true);
}



template<typename T>
struct Loop
{
	static void loop(int i, std::shared_ptr<T> ptr);
};

template<typename T>
void Loop<T>::loop(int i, std::shared_ptr<T> ptr)
{
	for (int j = (i - 1) * 1000; j < i * 1000; j++)
	{
		ptr->setLevel(j);
		EXPECT_EQ(ptr->getLevel(), j);
	}
}

TEST_F(GraphVertexTest, setLevelAndGetLevelWorksCorrectly)
{
	Loop<GraphVertex>::loop(1, vertex);
	std::vector<std::thread> vecOfThreads;
	for (int i = 0; i < 5; i++) vecOfThreads.push_back(std::thread(Loop<GraphVertex>::loop, i, vertexes[i]));
	for (int i = 0; i < 5; i++) vecOfThreads[i].join();
}



TEST_F(GraphVertexTest, setLogicExpressionAndGetLogicExpressionWorksCorrectly)
{
	for (int i = 0; i < 50; i++)
	{
		vertex->setLogicExpression(std::to_string(i));
		ASSERT_EQ(vertex->getLogicExpression(), std::to_string(i));
	}
}

/*
TEST_F(GraphVertexTest, setWireNameAndGetWireNameWorksCorrectly)
{
	std::vector<std::function<void(void)>> lambdas;

	for (int i = 1; i < 5; i++)
	{
		lambdas.push_back([i, this]() {
			for (int j = (i - 1) * 1000; j < i * 1000; j++)
			{
				vertex->setWireName(std::to_string(j));
				ASSERT_EQ(vertex->getWireName(), std::to_string(j));
			}
			}
		);
	}

	std::vector<std::thread> vecOfThreads;
	for (int i = 1; i < 5; i++)
	{
		std::thread th1(lambdas.back());
		lambdas.pop_back();
		vecOfThreads.push_back(std::move(th1));
	}
	for (std::thread& th : vecOfThreads)
	{
		if (th.joinable())
			th.join();
	}
}*/


