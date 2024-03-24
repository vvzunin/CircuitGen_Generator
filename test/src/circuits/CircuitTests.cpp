#include <gtest/gtest.h>
#include <filesystem>

#include "../optimization_utils/AbcUtils.h"
#include "circuits/Circuit.h"

// Test empty graph
TEST(CircuitTest, EmptyGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph emptyGraph;
    Circuit emptyCircuit(&emptyGraph);
    emptyCircuit.setPath(currentPath);
    emptyCircuit.setCircuitName("EmptyCircuit4");

    EXPECT_FALSE(emptyCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/EmptyCircuit4.v";

    EXPECT_FALSE(std::filesystem::exists(filename));
}



TEST(CircuitTest, InputsOutputsOnlyTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph ioGraph;
    ioGraph.addVertex("1", "input", "Anything");
    ioGraph.addVertex("2", "output", "Anything");
    ioGraph.addVertex("3", "or", "Anything");
    Circuit ioCircuit(&ioGraph);
    ioCircuit.setPath(currentPath);
    ioCircuit.setCircuitName("IOOnlyCircuit4");

    EXPECT_TRUE(ioCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/IOOnlyCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));
    std::cout << "\n" << filename << "\n";;
    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}

TEST(CircuitTest, GraphWithConstantsTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph constGraph;
    constGraph.addVertex("1", "const", "1");
    constGraph.addVertex("2", "output", "");
    constGraph.addEdge("3", "output", false);
    Circuit constCircuit(&constGraph);
    constCircuit.setPath(currentPath);
    constCircuit.setCircuitName("ConstCircuit4");

    EXPECT_TRUE(constCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/ConstCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));
    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}

TEST(CircuitTest, AndOperationGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph andGraph;
    andGraph.addVertex("1", "input", "");
    andGraph.addVertex("2", "input", "");
    andGraph.addVertex("3", "and", "");
    andGraph.addVertex("4", "output", "");
    andGraph.addEdge("1", "and", false);
    andGraph.addEdge("2", "and", false);
    andGraph.addEdge("3", "output", false);
    Circuit andCircuit(&andGraph);
    andCircuit.setPath(currentPath);
    andCircuit.setCircuitName("AndCircuit4");

    EXPECT_TRUE(andCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/AndCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}


TEST(CircuitTest, OrOperationGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph orGraph;
    orGraph.addVertex("1", "input", "");
    orGraph.addVertex("2", "input", "");
    orGraph.addVertex("3", "or", "");
    orGraph.addVertex("4", "output", "");
    orGraph.addEdge("1", "or", false);
    orGraph.addEdge("2", "or", false);
    orGraph.addEdge("3", "output", false);
    Circuit orCircuit(&orGraph);
    orCircuit.setPath(currentPath);
    orCircuit.setCircuitName("OrCircuit4");

    EXPECT_TRUE(orCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/OrCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}

TEST(CircuitTest, XorOperationGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph xorGraph;
    xorGraph.addVertex("1", "input", "");
    xorGraph.addVertex("2", "input", "");
    xorGraph.addVertex("3", "xor", "");
    xorGraph.addVertex("4", "output", "");
    xorGraph.addEdge("1", "xor", false);
    xorGraph.addEdge("2", "xor", false);
    xorGraph.addEdge("3", "output", false);
    Circuit xorCircuit(&xorGraph);
    xorCircuit.setPath(currentPath);
    xorCircuit.setCircuitName("XorCircuit4");

    EXPECT_TRUE(xorCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/XorCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}

TEST(CircuitTest, NandOperationGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph nandGraph;
    nandGraph.addVertex("1", "input", "");
    nandGraph.addVertex("2", "input", "");
    nandGraph.addVertex("3", "nand", "");
    nandGraph.addVertex("4", "output", "");
    nandGraph.addEdge("1", "nand", false);
    nandGraph.addEdge("2", "nand", false);
    nandGraph.addEdge("3", "output", false);
    Circuit nandCircuit(&nandGraph);
    nandCircuit.setPath(currentPath);
    nandCircuit.setCircuitName("NandCircuit4");

    EXPECT_TRUE(nandCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/NandCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}


TEST(CircuitTest, NorOperationGraphTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph norGraph;
    norGraph.addVertex("1", "input", "");
    norGraph.addVertex("2", "input", "");
    norGraph.addVertex("3", "nor", "");
    norGraph.addVertex("4", "output", "");
    norGraph.addEdge("1", "nor", false);
    norGraph.addEdge("2", "nor", false);
    norGraph.addEdge("3", "output", false);
    Circuit norCircuit(&norGraph);
    norCircuit.setPath(currentPath);
    norCircuit.setCircuitName("NorCircuit4");

    EXPECT_TRUE(norCircuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/NorCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    std::filesystem::remove(filename);

    EXPECT_FALSE(std::filesystem::exists(filename));
}


TEST(CircuitTest, GraphToVerilogTest) {
    std::string currentPath = std::filesystem::current_path();
    OrientedGraph example;
    example.addVertex("nor", "Anything", "Anything");
    example.addVertex("xor", "Anything", "Anything");
    example.addVertex("and", "Anything", "Anything");
    example.addVertex("nand", "Anything", "Anything");
    example.addVertex("or", "Anything", "Anything");
    example.addVertex("xnor", "Anything", "Anything");
    example.addVertex("buf", "Anything", "Anything");
    example.addVertex("not", "Anything", "Anything");
    example.addVertex("input", "Anything", "Anything");
    example.addVertex("output", "Anything", "Anything");
    example.addVertex("const", "Anything", "Anything");
    Circuit circuit(&example);
    circuit.setPath(currentPath);
    circuit.setCircuitName("TestCircuit4");

    EXPECT_TRUE(circuit.graphToVerilog(currentPath, true));

    std::string filename = currentPath + "/TestCircuit4.v";

    EXPECT_TRUE(std::filesystem::exists(filename));

    // Удаляем созданный Verilog файл после проверки
    std::filesystem::remove(filename);

    // Убеждаемся, что файл был удалён
    EXPECT_FALSE(std::filesystem::exists(filename));
}