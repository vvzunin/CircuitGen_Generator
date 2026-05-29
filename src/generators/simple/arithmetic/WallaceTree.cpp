#include "ArithmeticGenerator.hpp"
#include <CircuitGenGraph/GraphUtils.hpp>
#include <CircuitGenGraph/GraphVertexBase.hpp>
#include <CircuitGenGraph/GraphVertexBus.hpp>
#include <cstddef>
#include <fmt/format.h>
#include <vector>
namespace CG_Gen {
    std::pair<VertexPtr, VertexPtr> generateCSA(GraphPtr graph, const std::vector<VertexPtr>& inputs, size_t width) {
        if(inputs.size() != 3) {
            throw std::invalid_argument("CSA requires exactly 3 inputs");
        }
        VertexPtr sum, *carry, *and1, *and2, *and3;
        sum = graph->addGateBus(GateXor,"", width);
        graph->addEdges(inputs, sum);
        carry = graph->addGateBus(GateOr, "", width);
        and1 = graph->addGateBus(GateAnd, "", width);
        and2 = graph->addGateBus(GateAnd, "", width);
        and3 = graph->addGateBus(GateAnd, "", width);
        graph->addEdges({and1,and2, and3}, carry);
        graph->addEdges({inputs[0], inputs[1]}, and1);
        graph->addEdges({inputs[1], inputs[2]}, and2);
        graph->addEdges({inputs[0], inputs[2]}, and3);
        return {sum, carry};
    }

    GraphPtr ArithmeticGenerator::generateWallaceTree(size_t i_argsCount, size_t bits, ArithemticOperations::Types summatorType) const {
        GraphPtr graph = std::make_shared<OrientedGraph>();
        graph->setName("WallaceTree");
        VertexPtr shiftCarry;
        VertexPtr zero = graph->addConst('0');
        std::vector<VertexPtr> currentValues;
        std::vector<VertexPtr> nextLevelValues;
        currentValues.reserve(i_argsCount);
        for(int i = 0; i < i_argsCount; ++i) {
           currentValues.push_back(graph->addInputBus(fmt::format("input_{}",i), bits));
        }
        graph->addOutputBus("sum", bits + i_argsCount);
        while(currentValues.size() > 2) {
            for (size_t i = 0; i< currentValues.size()-3;i+=3) {
                auto [sum, carry] = generateCSA(graph, {currentValues[i], currentValues[i+1], currentValues[i+2]}, bits);
                nextLevelValues.push_back(sum);
                shiftCarry = graph->addGateBus(GateConcatenation, "", bits+1);
                graph->addEdges({carry, zero}, shiftCarry);
                nextLevelValues.push_back(shiftCarry);
            }
        currentValues = nextLevelValues;
        nextLevelValues.clear();
        }   
        switch (summatorType) {
        case ArithemticOperations::ADD:
            graph->addSubGraph(generatorBusSummator(bits, 0,0,false), currentValues);
            break;
        }
        return graph;
    }
}