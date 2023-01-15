enum MutationTypes
{
  Binary,
  Density,
  AccessionDel,
  InsertDel,
  Exchange,
  Delete
};

class MutationParameters
{
public:
  MutationParameters();

private:
  MutationTypes d_mutationType = MutationTypes::Binary;
  double probabilityGen = 0.1;
  int exchangeType = 0;
  double probabilityTruthTable = 0.1;
};
