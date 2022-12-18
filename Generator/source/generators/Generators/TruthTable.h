#pragma once

class TruthTable : Chromosome<TruthTableParameters>
{
public:
  TruthTable();
  TruthTable(Chromosome<TruthTableParameters> i_chr);
  TruthTable(int i_input, int i_output, const std::vector<std::vector<bool>>& i_array = {});
  TruthTable(const TruthTable& i_tt, std::vector<std::vector<bool>> i_array = {});
  TruthTable(int i_input, int i_output, double i_p = 0.5);
  int getInput() const;
  int getOutput() const;
  int size() const;
  std::vector<std::vector<bool>> getOutTable() const;
  bool getOutTable(int i, int j) const;
  void generateTable(double i_p = 0);
  void generateRandom(TruthTableParameters i_gp);
  std::vector<std::vector<bool>> convToBinary() const;
  void printTable() const;


private:
  int d_input;
  int d_output;
  int d_size;
  Settings d_settings = readSettings();


}
