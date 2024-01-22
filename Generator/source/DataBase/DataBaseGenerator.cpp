#include <thread>
#include <vector>
#include <iostream>
#include <filesystem>

#include <FilesTools.h>
#include <circuits/Circuit.h>
#include <generators/Parser.h>
#include <generators/TruthTable.h>
#include <thread_pool/ThreadPool.h>
#include <circuits/CircuitsParameters.h>
#include <generators/SimpleGenerators.h>
#include <generators/Genetic/GenGenerator.h>
#include <generators/Genetic/GeneticParameters.h>

#include "DataBaseGenerator.h"

using namespace Threading;

void DataBaseGenerator::generateType(
    const DataBaseGeneratorParameters &i_dbgp,
    bool parallel, bool createIdDirectories)
{

    std::string s = i_dbgp.getGenerationTypeString();
    std::function<void(const GenerationParameters &)> generator = getGenerateMethod(s);
    // TODO: make normal code
    std::string dir = d_settings->getDatasetPath();

    if (createIdDirectories)
        dir += "/" + i_dbgp.getGenerationParameters().getName() + "/" + i_dbgp.getGenerationParameters().getRequestId();
    // Creating nested directories
    std::filesystem::create_directories(dir);

    d_mainPath = dir + "/";
    d_dirCount = 0;
    // std::cout << "Inside of generateType: " << std::endl;
    // std::cout << "dir = " << dir << std::endl;
    // std::cout << "i_dbgp.getGenerationParameters().getRequestId() returned: " << i_dbgp.getGenerationParameters().getRequestId() << std::endl;
    // std::cout << "i_dbgp.getMaxInputs() returned: " << i_dbgp.getMaxInputs() << std::endl;
    // std::cout << "i_dbgp.getMinInputs() returned: " << i_dbgp.getMinInputs() << std::endl;
    // std::cout << "i_dbgp.getMaxOutputs() returned: " << i_dbgp.getMaxOutputs() << std::endl;
    // std::cout << "i_dbgp.getMinOutsputs() returned: " << i_dbgp.getMinOutputs() << std::endl;
    if (std::filesystem::is_directory(dir))
    {
        for (const auto item : FilesTools::getDirectories(dir))
        {
            std::string s0 = item;
            auto pos = s0.find(d_settings->getGenerationMethodPrefix(s));

            if (pos == std::string::npos)
                continue;

            s0.replace(pos, d_settings->getGenerationMethodPrefix(s).size(), "");

            auto jk = std::min(s0.find("_"), s0.find("."));
            if (jk == std::string::npos)
            {
                jk = s0.size();
            }

            s0 = s0.substr(0, jk);

            d_dirCount = std::max(d_dirCount, std::stoi(s0) + 1); // TODO: in general code n is int32, is it really need?
        }
    }

    for (int i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i)
    {
        for (int j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j)
        {
            d_parameters.setInputs(i);
            d_parameters.setOutputs(j);

            if (parallel)
            {

                // exit(1); //TODO: write to threadpool
                ThreadPool pool(4);

                // vector of threads with generators
                std::vector<std::thread> allGenerators(i_dbgp.getEachIteration());

                for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt)
                {
                    d_parameters.setIteration(tt);
                    d_parameters.setName(d_settings->getGenerationMethodPrefix(s) + std::to_string(d_dirCount));

                    auto runGenerator = [generator, param=d_parameters.getGenerationParameters()] () {
                        generator(param);
                    };

                    // allGenerators.emplace_back(
                    //     generator,
                    //     d_parameters.getGenerationParameters());
                    pool.submit(runGenerator);
                    d_dirCount++;
                }

                pool.wait();
                // for (std::thread &gen : allGenerators)
                // {
                //     if (gen.joinable())
                //         gen.join();
                // }
            }
            else
            {
                for (int tt = 0; tt < i_dbgp.getEachIteration(); ++tt)
                {
                    // TODO: it is that Rustam told about iteration?
                    d_parameters.setIteration(tt);
                    d_parameters.setName(d_settings->getGenerationMethodPrefix(s) + std::to_string(d_dirCount));

                    generator(d_parameters.getGenerationParameters());
                    d_dirCount++;
                }
            }
        }
    }
}

void DataBaseGenerator::generateDataBaseFromRandomTruthTable(const GenerationParameters &i_param)
{
    TruthTable tt(i_param.getInputs(), i_param.getOutputs(), {});
    tt.generateRandom({i_param.getInputs(), i_param.getOutputs()});

    SimpleGenerators tftt;
    tftt.setGatesInputsInfo(i_param.getGatesInputsInfo());

    std::vector<std::pair<std::string, std::vector<std::string>>> circs;

    if (i_param.getCNF().getCNFT())
        circs.push_back({"CNFT", tftt.cnfFromTruthTable(tt, true)});

    if (i_param.getCNF().getCNFF())
        circs.push_back({"CNFF", tftt.cnfFromTruthTable(tt, false)});

    for (const auto &[name, expr] : circs)
    {
        Parser pCNFT(expr);
        pCNFT.parseAll();

        OrientedGraph graph = pCNFT.getGraph();
        Circuit c(graph, expr);
        c.setTable(tt);
        c.setPath(d_mainPath);
        c.setCircuitName(i_param.getName() + "_" + name);
        c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
    }
}

void DataBaseGenerator::generateDataBaseRandLevel(const GenerationParameters &i_param)
{
    SimpleGenerators generator;
    generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

    std::vector<std::pair<std::string, OrientedGraph>> circs;
    circs.push_back({"RandLevel",
                     generator.generatorRandLevel(i_param.getRandLevel().getMaxLevel(),
                                                  i_param.getRandLevel().getMaxElements(),
                                                  i_param.getInputs(),
                                                  i_param.getOutputs())});

    for (const auto &[name, graph] : circs)
    {
        Circuit c(graph);
        c.setPath(d_mainPath);
        c.setCircuitName(i_param.getName());
        c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
    }
}

void DataBaseGenerator::generateDataBaseNumOperations(const GenerationParameters &i_param)
{
    SimpleGenerators generator;
    generator.setGatesInputsInfo(i_param.getGatesInputsInfo());

    std::vector<std::pair<std::string, OrientedGraph>> circs;
    circs.push_back({"RandLevel",
                     generator.generatorNumOperation(
                         i_param.getInputs(),
                         i_param.getOutputs(),
                         i_param.getNumOperations().getLogicOpers(),
                         i_param.getNumOperations().getLeaveEmptyOut())});

    for (const auto &[name, graph] : circs)
    {
        Circuit c(graph);
        c.setPath(d_mainPath);
        c.setCircuitName(i_param.getName());
        c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
    }
    // TODO: remake all generates to return value and call graphToVerilog
}

void DataBaseGenerator::generateDataBaseGenetic(const GenerationParameters &i_param)
{
    i_param.getGenetic().setInputs(i_param.getInputs());
    i_param.getGenetic().setOutputs(i_param.getOutputs());

    GeneticGenerator<TruthTable, TruthTableParameters> gg(GeneticParameters(i_param.getGenetic()),
                                                          {i_param.getInputs(), i_param.getOutputs()},
                                                          d_mainPath);
    // gg.generate();
}

void DataBaseGenerator::GenerateDataBaseSummator(GenerationParameters &i_param)
{
    SimpleGenerators sg;
    sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

    int bits = i_param.getInputs();
    bool overflowIn = i_param.getSummator().OverFlowIn;
    bool overflowOut = i_param.getSummator().OverFlowOut;
    bool minus = i_param.getSummator().minus;
    OrientedGraph graph = sg.generatorSummator(bits, overflowIn, overflowOut, minus);
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
}

void DataBaseGenerator::GenerateDataBaseComparison(const GenerationParameters &i_param)
{
    SimpleGenerators sg;
    sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

    int bits = i_param.getInputs();
    bool compare0 = i_param.getComparison().compare0;
    bool compare1 = i_param.getComparison().compare1;
    bool compare2 = i_param.getComparison().compare2;
    OrientedGraph graph = sg.generatorСomparison(bits, compare0, compare1, compare2);
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
}

void DataBaseGenerator::GenerateDataBaseEncoder(const GenerationParameters &i_param)
{
    SimpleGenerators sg;
    sg.setGatesInputsInfo(i_param.getGatesInputsInfo());

    int bits = i_param.getInputs();
    OrientedGraph graph = sg.generatorEncoder(bits);
    Circuit c(graph);
    c.setPath(d_mainPath);
    c.setCircuitName(i_param.getName());
    c.generate(i_param.getCalculateStatsAbc(), i_param.getLibraryName(), i_param.getMakeOptimizedFiles());
}

std::function<void(const GenerationParameters &)> DataBaseGenerator::getGenerateMethod(const std::string &i_methodName)
{
    if (i_methodName == "FromRandomTruthTable")
        return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable, this, std::placeholders::_1);
    if (i_methodName == "RandLevel")
        return std::bind(&DataBaseGenerator::generateDataBaseRandLevel, this, std::placeholders::_1);
    if (i_methodName == "NumOperation")
        return std::bind(&DataBaseGenerator::generateDataBaseNumOperations, this, std::placeholders::_1);
    if (i_methodName == "Genetic")
        return std::bind(&DataBaseGenerator::generateDataBaseGenetic, this, std::placeholders::_1);

    std::cout << "UNDEFINED FUNC << " << i_methodName << std::endl;
    return std::bind(&DataBaseGenerator::generateDataBaseFromRandomTruthTable, this, std::placeholders::_1);
}
