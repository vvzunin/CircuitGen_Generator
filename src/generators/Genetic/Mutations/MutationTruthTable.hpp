#pragma once

#include <vector>

#include <baseStructures/truthTable/TruthTable.hpp>

#include "../ChromosomeType.hpp"

namespace MutationTruthTable {
std::vector<std::vector<bool>>
    MutationTable(std::vector<std::vector<bool>> i_table, double i_probability);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationBinary(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationDensity(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
    MutationAccessionDel(
        MutationParameters i_mutationParameters,
        std::vector<ChromosomeType<TruthTable, TruthTableParameters>>
            i_population
    );

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationInsertDel(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationExchange(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationDelete(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);

std::vector<ChromosomeType<TruthTable, TruthTableParameters>> MutationDelete(
    MutationParameters i_mutationParameters,
    std::vector<ChromosomeType<TruthTable, TruthTableParameters>> i_population
);
// namespace end
}  // namespace MutationTruthTable