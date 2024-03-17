#include <vector>
#include <ctime>
#include <memory>

#include "TruthTable.h"
#include <additional/AuxiliaryMethods.h>

TruthTable::TruthTable()
{
    d_randGenerator.setSeed(AuxMethods::getRandSeed());
    d_settings = Settings::getInstance("TruthTable");
}

TruthTable::TruthTable(int i_seed)
{
    d_randGenerator.setSeed(i_seed);
    d_settings = Settings::getInstance("TruthTable");
}

void TruthTable::setSeed(int i_seed) {
    d_randGenerator.setSeed(i_seed);
}

TruthTable::TruthTable(int i_input, int i_output, const std::vector<std::vector<bool>> &i_array) : d_input(i_input),
                                                                                                   d_output(i_output)
{
    d_size = 1u << d_input;
    if (i_array.size() == 0 || i_array.size() != d_size || i_array[0].size() != d_output)
        generateTable(0);
    else
        d_array = i_array;
}

TruthTable::TruthTable(const TruthTable &i_tt, std::vector<std::vector<bool>> i_array) : d_input(i_tt.d_input),
                                                                                         d_output(i_tt.d_output)
{
    d_size = 1u << d_input; // what?
}

TruthTable::TruthTable(int i_input, int i_output, double i_p) : d_input(i_input),
                                                                d_output(i_output)
{
    d_size = (1u << i_input);
    generateTable(i_p);
}

std::vector<std::vector<bool>> TruthTable::convToBinary() const
{
    std::vector<std::vector<bool>> bin(d_size, std::vector<bool>(d_input));
    for (int i = 0; i < d_size; ++i)
    {
        for (int j = d_input - 1, tmp = i; j >= 0; --j)
        {
            bin[i][j] = (tmp % 2) == 1;
            tmp /= 2;
        }
    }
    return bin;
}

int TruthTable::getInput() const
{
    return d_input;
}

int TruthTable::getOutput() const
{
    return d_output;
}

int TruthTable::size() const
{
    return d_size;
}

std::vector<std::vector<bool>> TruthTable::getOutTable() const
{
    return d_array;
}

bool TruthTable::getOutTable(int i, int j) const
{
    return d_array.at(i).at(j);
}

void TruthTable::generateTable(double i_p)
{

    if (i_p == 0)
    {
        d_array.clear();
        d_array.resize(d_size);
        for (int i = 0; i < d_size; ++i)
        {
            d_array[i].resize(d_output);
            for (int j = 0; j < d_output; ++j)
                d_array[i][j] = d_randGenerator.getRandInt(0, 1, true) == 1;
        }
    }
    if (i_p > 0 && i_p <= 1)
    {
        d_array.clear();
        d_array.resize(d_size);
        for (int i = 0; i < d_size; ++i)
        {
            d_array[i].resize(d_output);
            for (int j = 0; j < d_output; ++j)
                d_array[i][j] = AuxMethods::getRandDouble(0, 1) < i_p;
        }
    }
}

bool TruthTable::operator==(const TruthTable &r) const
{
    return std::tie(d_input, d_output, d_size, d_array) ==
           std::tie(r.d_input, r.d_output, r.d_size, r.d_array);
}
