#pragma once

#include <vector>
#include <memory>

#include <settings/Settings.hpp>
#include <additional/RandomGeneratorWithSeed.hpp>

class TruthTable 
{
public:
    TruthTable();

    TruthTable(int seed);
    TruthTable(const TruthTable &other) = default;
    TruthTable &operator=(const TruthTable &other) = default;
    TruthTable(TruthTable &&other) = default;
    TruthTable &operator=(TruthTable &&other) = default;
    TruthTable(int i_input, int i_output, const std::vector<std::vector<bool>> &i_array = {});
    TruthTable(const TruthTable &i_tt, std::vector<std::vector<bool>> i_array = {});
    TruthTable(int i_input, int i_output, double i_p = 0.5);

    void setSeed(int i_seed);
    // void generateRandom(TruthTableParameters i_gp) override;
    void generateTable(double i_p = 0);
    int getInput() const;
    int getOutput() const;
    int size() const;
    std::vector<std::vector<bool>> getOutTable() const;
    bool getOutTable(int i, int j) const;
    std::vector<std::vector<bool>> convToBinary() const;
    // TODO: Добавить
    void printTable() const;
    bool operator==(const TruthTable &r) const;

private:
    int d_input;
    int d_output;
    int d_size;
    std::vector<std::vector<bool>> d_array;
    std::shared_ptr<Settings> d_settings = Settings::getInstance("TruthTable");
    RandomGeneratorWithSeed d_randGenerator;
};
