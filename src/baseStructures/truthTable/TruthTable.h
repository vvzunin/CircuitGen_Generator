#pragma once

#include <vector>
#include <memory>

#include <settings/Settings.h>

class TruthTable 
{
public:
    TruthTable();
    void generateTable(double i_p = 0);
    TruthTable(int i_input, int i_output, const std::vector<std::vector<bool>> &i_array = {});
    TruthTable(const TruthTable &i_tt, std::vector<std::vector<bool>> i_array = {});
    TruthTable(int i_input, int i_output, double i_p = 0.5);
    int getInput() const;
    int getOutput() const;
    int size() const;
    std::vector<std::vector<bool>> getOutTable() const;
    bool getOutTable(int i, int j) const;
    std::vector<std::vector<bool>> convToBinary() const;
    void printTable() const;
    bool operator==(const TruthTable &r) const;

private:
    int d_input;
    int d_output;
    int d_size;
    std::vector<std::vector<bool>> d_array;
    std::shared_ptr<Settings> d_settings = Settings::getInstance("TruthTable");
};
