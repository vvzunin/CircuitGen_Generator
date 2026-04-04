#include "SimpleGenerator.hpp"

#include "additional/auxiliaryMethods/AuxiliaryMethods.hpp"
#include <limits.h> // INT_MAX

namespace CG_Gen {

SimpleGenerator::SimpleGenerator() {
  d_randGenerator.setSeed(AuxMethods::getRandSeed());
}

SimpleGenerator::SimpleGenerator(uint_fast32_t i_seed) {
  d_randGenerator.setSeed(i_seed);
}

SimpleGenerator::SimpleGenerator(const GenerationParameters &i_param) :
    d_parameters(&i_param) {
  d_randGenerator.setSeed(i_param.getSeed());
  setGatesInputsInfo(i_param.getGatesInputsInfo());
}

const GenerationParameters &SimpleGenerator::getParameters() const {
  return *d_parameters;
}

void SimpleGenerator::setGatesInputsInfo(
    const std::map<std::string, std::vector<int32_t>> &i_info) {
  d_minGateNumber = INT_MAX;

  for (const auto &[key, value]: i_info) {
    d_maxGateNumber = std::max(*std::max_element(value.begin(), value.end()),
                               d_maxGateNumber);
    d_minGateNumber = std::min(*std::max_element(value.begin(), value.end()),
                               d_minGateNumber);
    d_gatesInputsInfo[GraphUtils::parseStringToGate(key)] = value;
  }

  // TODO is it a good idea to add here hew gates
  d_gatesInputsInfo[Gates::GateNot] = {1};
  d_gatesInputsInfo[Gates::GateBuf] = {1};
}

GatesInfo SimpleGenerator::getGatesInputsInfo() const {
  return d_gatesInputsInfo;
}

#if FALSE
int32_t SimpleGenerator::getRandomAndNumber() {
  return d_gatesInputsInfo[Gates::GateAnd][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateAnd].size())];
}

int32_t SimpleGenerator::getRandomOrNumber() {
  return d_gatesInputsInfo[Gates::GateOr][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateOr].size())];
}

int32_t SimpleGenerator::getRandomNandNumber() {
  return d_gatesInputsInfo[Gates::GateNand][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNand].size())];
}

int32_t SimpleGenerator::getRandomNorNumber() {
  return d_gatesInputsInfo[Gates::GateNor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateNor].size())];
}

int32_t SimpleGenerator::getRandomXorNumber() {
  return d_gatesInputsInfo[Gates::GateXor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXor].size())];
}

int32_t SimpleGenerator::getRandomXnorNumber() {
  return d_gatesInputsInfo[Gates::GateXnor][d_randGenerator.getRandInt(
      0, d_gatesInputsInfo[Gates::GateXnor].size())];
}
#endif

std::pair<Gates, int32_t>
SimpleGenerator::getRandomElement(const GatesInfo &i_info) {
  // rand element of map
  auto val = i_info.begin();
  std::advance(val, d_randGenerator.getRandInt(0, i_info.size()));

  // random gate number from of random element
  return std::make_pair(
      val->first,
      val->second[d_randGenerator.getRandInt(0, val->second.size())]);
}

std::pair<Gates, int32_t>
SimpleGenerator::getRandomElement(uint32_t i_gatesLimit) {
  if (i_gatesLimit >= d_maxGateNumber)
    return getRandomElement(d_gatesInputsInfo);

  if (i_gatesLimit <= 1)
    return std::make_pair(
        d_randGenerator.getRandInt(0, 2) ? Gates::GateNot : Gates::GateBuf, 1);

  GatesInfo info;
  std::vector<int32_t> subval;

  for (auto [key, value]: d_gatesInputsInfo) {
    for (size_t i = 0; i < value.size() && value[i] <= i_gatesLimit; ++i)
      subval.push_back(value[i]);

    if (subval.size())
      info[key] = std::move(subval);
    subval.clear();
  }

  return getRandomElement(info);
}

std::map<Gates, int32_t>
SimpleGenerator::delNull(std::map<Gates, int32_t> i_copyLogicOper) {
  std::vector<Gates> delList;
  for (const auto &[key, value]: i_copyLogicOper)
    if (value == 0)
      delList.push_back(key);

  for (const auto &op: delList)
    i_copyLogicOper.erase(op);
  return i_copyLogicOper;
}

} // namespace CG_Gen
