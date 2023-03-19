#include "SimpleGenerators.h"
#include "../graph/OrientedGraph.h"

namespace {
  int maxValueInMap(const std::map<std::string, int>& i_map)
  {
    if (i_map.size() == 0)
    {
      return -1;
    }
    int res = (*i_map.begin()).second;

    for (const auto &[key, value] : i_map)
    {
      res = std::max(res, value);
    }
    return res;
  }
}

SimpleGenerators::SimpleGenerators()
{
  std::srand(std::time(0));
}

std::vector<std::string> SimpleGenerators::cnfFromTruthTable(
  const TruthTable& i_table, 
  bool i_tp
)
{
  std::vector<std::string> fun;
  std::vector<std::vector<bool>> bin = i_table.convToBinary();

  for (int j = 0; j < i_table.getOutput(); ++j)
  {
    fun.push_back("f" + std::to_string(j) + " = ");
    int mem = 0;
    int tmp = 0;

    for (int i = 0; i < i_table.size(); ++i)
    {
      if (!(i_table.getOutTable(i, j) ^ i_tp))
        mem++;
    }

    if (mem == 0)
    {
      if (i_tp)
        fun[j] += "1'0";
      else
        fun[j] += "1'1";
      continue;
    }

    if (mem == i_table.size())
    {
      if (i_tp)
        fun[j] += "1'1";
      else
        fun[j] += "1'0";
      continue;
    }

    for (int i = 0; i < mem; ++i)
    {
      fun[j] += '(';
      while ((i_table.getOutTable(tmp, j) ^ i_tp) && tmp < i_table.size())
        tmp++;

      for (int k = 0; k < i_table.getInput(); ++k)
      {
        if (bin[tmp][k] ^ i_tp)
          fun[j] += d_settings->getLogicOperation("not").first + " ";

        fun[j] += 'x';
        fun[j] += std::to_string(k);

        if (k != i_table.getInput() - 1)
          fun[j] += " " + (i_tp ? 
                           d_settings->getLogicOperation("and").first : 
                           d_settings->getLogicOperation("or").first
                        ) + " ";
      }

      fun[j] += ')';

      if (i != mem - 1)
        fun[j] += " " + (i_tp ? 
                       d_settings->getLogicOperation("or").first : 
                       d_settings->getLogicOperation("and").first
                      ) + " ";

      tmp++;
    }
  }

  return fun;
}

OrientedGraph SimpleGenerators::generatorRandLevel(int i_maxLevel, int i_maxElements, int i_inputs, int i_outputs)
{
  int maxLevel = rand() % i_maxLevel;
  std::vector<int> elemLevel(maxLevel + 1);
  std::vector<std::string> logOper = d_settings->getLogicOperationsKeys();
  logOper.erase(std::find(logOper.begin(), logOper.end(), "input"));
  logOper.erase(std::find(logOper.begin(), logOper.end(), "output"));
  logOper.erase(std::find(logOper.begin(), logOper.end(), "const"));

  //maxLevel++ // what?
  elemLevel[0] = i_inputs;
  elemLevel[maxLevel] = i_outputs;
  for (int i = 1; i < maxLevel; ++i)
    elemLevel[i] = (rand() % (i_maxElements - 1)) + 2;

  int choice;
  std::string expr;
  OrientedGraph graph;
  int child1, child2;

  for (int i = 0; i < elemLevel[0]; ++i)
  {
    expr = "x" + std::to_string(i);
    graph.addVertex(expr, "input");
  }

  int currIndex = elemLevel[0];
  int prevIndex = 0;

  for (int i = 1; i < i_maxLevel - 1; ++i)
  {
    int position = 0;
    for (int j = 0; j < elemLevel[i]; ++j)
    {
      choice = rand() % logOper.size();
      if (logOper[choice] == "not")
      {
        child1 = rand() % currIndex;
        expr = d_settings->fromOperationsToName(logOper[choice]) + " (" +
          graph.getVertice(currIndex + position).getLogicExpression() + ")";

        if (graph.addVertex(expr, "not"))
          graph.addEdge(graph.getVertice(child1).getLogicExpression(), graph.getVertice(currIndex + position).getLogicExpression());
        else
          --position;
      }
      else
      {
        child1 = (rand() % (currIndex - prevIndex)) + prevIndex;
        child2 = (rand() % (currIndex - prevIndex)) + prevIndex;

        expr = "(" + graph.getVertice(child2).getLogicExpression() + " )" +
          d_settings->fromOperationsToName(logOper[choice]) + " (" + graph.getVertice(child1).getLogicExpression() + ")";

        if (graph.addVertex(expr, logOper[choice]))
          graph.addDoubleEdge(graph.getVertice(child2).getLogicExpression(),
                              graph.getVertice(child1).getLogicExpression(),
                              graph.getVertice(currIndex + position).getLogicExpression());
        else
          --position;
      }
      ++position;
    }

    prevIndex += currIndex - prevIndex;
    currIndex += position;
  }

  for (int i = 0; i < i_outputs; ++i)
  {
    child1 = (rand() % (currIndex - prevIndex)) + prevIndex;
    expr = "f" + std::to_string(i + 1);
    graph.addVertex(expr, "output");
    graph.addEdge(graph.getVertice(child1).getLogicExpression(),
                  graph.getVertice(currIndex + i).getLogicExpression()
    );
  }
  return graph;
}

OrientedGraph SimpleGenerators::generatorNumOperation(
  int i_input,
  int i_output,
  std::map<std::string, int> i_logicOper,
  bool i_leaveEmptyOut
)
{
  int sumOper = 0, maxLvl;
  std::string name;
  std::map<std::string, int> copyLogicOper, levelName;
  std::vector<std::string> nameOut, nameInput;

  copyLogicOper = i_logicOper;
  
  OrientedGraph graph;

  for (int i = 0; i < i_input; ++i)
  {
    name = "x" + std::to_string(i);
    graph.addVertex(name, "input");
    levelName[name] = graph.getVertice(graph.getIndexOfExpression(name)).getLevel();
    if (!i_leaveEmptyOut)
      nameInput.push_back(name);
  }

  for (int i = 0; i < i_output; ++i)
  {
    name = "f" + std::to_string(i);
    graph.addVertex(name, "output");
    nameOut.push_back(name);
  }

  for (const auto &[key, value] : copyLogicOper)
    sumOper += value;

  for (int i = 0; i < sumOper; ++i)
  {
    copyLogicOper = delNull(copyLogicOper);
    std::string oper = randomGenerator(copyLogicOper);
    copyLogicOper[oper]--;

    if (oper == "not")
    {
      std::string ver1 = randomGenerator(levelName);
      name = d_settings->getLogicOperation(oper).first + "(" + ver1 + ")";
      if (graph.addVertex(name, oper))
      {
        graph.addEdge(ver1, name);
      }
      else
      {
        copyLogicOper[oper]++;
        sumOper++;
      }
    }
    else
    {
      std::string ver1 = randomGenerator(levelName);
      std::string ver2 = randomGenerator(levelName);
      name = "(" + ver1 + ") " + d_settings->getLogicOperation(oper).first + "(" + ver2 + ")";
      std::string reserveName = "(" + ver2 + ") " + d_settings->getLogicOperation(oper).first + "(" + ver1 + ")";
      if (graph.addVertex(name, oper))
      {
        graph.addDoubleEdge(ver1, ver2, name);
        levelName[name] = graph.getVertice(graph.getIndexOfExpression(name)).getLevel();
      }
      else
      {
        copyLogicOper[oper]++;
        sumOper++;
      }
    }
  }

  while ((nameOut.size() > 0) & ((levelName.size() > 0 || i_leaveEmptyOut == false)))
  {
    if (levelName.size() > 0)
    {
      std::vector<std::string> help;
      maxLvl = maxValueInMap(levelName);
      
      for (const auto &[key, value] : levelName)
      {
        if (value == maxLvl)
          help.push_back(key);
      }

      while (help.size() > 0 && nameOut.size() > 0)
      {
        int R1 = rand() % help.size();
        int R2 = rand() % nameOut.size();
        graph.addEdge(help[R1], nameOut[R2]);
        levelName.erase(help[R1]);
        help.erase(help.begin() + R1);
        nameOut.erase(nameOut.begin() + R2);
      }
    }
    else
    {
      int R1 = rand() % nameInput.size();
      int R2 = rand() % nameOut.size();

      graph.addEdge(nameInput[R1], nameOut[R2]);
      nameOut.erase(nameOut.begin() + R2);
    }
  }
  return graph;
}

std::map<std::string, int> SimpleGenerators::delNull(std::map<std::string, int> i_copyLogicOper)
{
  std::vector<std::string> delList;
  for (const auto &[key, value] : i_copyLogicOper)
    if (value == 0)
      delList.push_back(key);

  for (const auto& op : delList)
    i_copyLogicOper.erase(op);
  return i_copyLogicOper;
}

std::string SimpleGenerators::randomGenerator(const std::map<std::string, int>& i_map)
{
  int i = rand() % i_map.size();

  auto p = i_map.begin();

  while(i--)
    p++;

  return (*p).first;

}
