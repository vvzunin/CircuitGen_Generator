#pragma once

std::vector<ChronosomeType<TruthTable, TruthTableParameters>> SelectionType(
  SelectionParameters i_selectionParameters,
  std::vector<Chronosome<TruthTable, TruthTableParameters>> i_population
);
