#pragma once

#include <cmath>
#include <string>
#include <tuple>

#include <baseStructures/truthTable/TruthTable.hpp>
#include <settings/Settings.hpp>

template<typename Type, typename ParametersTypes>
class ChromosomeType {
public:
  ChromosomeType(const std::string &i_name, const Type &i_Chromosome) {
    d_Chromosome = i_Chromosome;
    d_name = i_name;
    adaptationFunction();
  }
  // ChromosomeType(const ChromosomeType & r)
  //   : d_Chromosome(r.d_Chromosome),
  //     d_name(r.d_name),
  //     d_adaptationIndex(r.d_adaptationIndex),
  //     d_settings(Settings::getInstance("TruthTable"))
  // { }

  const Type &getChromosomeType() const { return d_Chromosome; }
  void setChromosomeType(const Type &i_Chromosome) {
    d_Chromosome = i_Chromosome;
  }
  double getAdaptationIndex() const { return d_adaptationIndex; }
  void setAdaptationIndex(double i_adaptationIndex) {
    d_adaptationIndex = i_adaptationIndex;
  }
  std::string getName() const { return d_name; }
  void adaptationFunction() {
    if constexpr (std::is_same_v<Type, TruthTable>) {
      uint32_t numInt = 0;
      for (const auto &nucleosoms: d_Chromosome.getOutTable())
        for (const auto &nucleosom: nucleosoms)
          if (nucleosom)
            numInt++;
      d_adaptationIndex = abs(
          0.5 - (numInt / (d_Chromosome.size() * d_Chromosome.getOutput())));
    }
  }
  bool operator==(const ChromosomeType<Type, ParametersTypes> &r) const {
    return std::tie(d_adaptationIndex, d_Chromosome, d_name) ==
           std::tie(r.d_adaptationIndex, r.d_Chromosome, r.d_name);
  }

private:
  double d_adaptationIndex;
  Type d_Chromosome;
  std::shared_ptr<Settings> d_settings = Settings::getInstance("GraphVertex");
  std::string d_name;
};

// template<typename Type, typename ParametersTypes>
// ChromosomeType<Type, ParametersTypes>::ChromosomeType(const std::string
// i_name, const Type i_Chromosome)
// {
//   this->d_Chromosome = i_Chromosome;
//   this->d_name = i_name;
//   adaptationFunction();
// }

// template<typename Type, typename ParametersTypes>
// Type ChromosomeType<Type, ParametersTypes>::getChromosomeType() const
// {
//   return d_Chromosome;
// }

// template<typename Type, typename ParametersTypes>
// void ChromosomeType<Type, ParametersTypes>::setChromosomeType(const Type&
// i_Chromosome)
// {
//   d_Chromosome = i_Chromosome;
// }

// template<typename Type, typename ParametersTypes>
// void ChromosomeType<Type, ParametersTypes>::adaptationFunction()
// {
//   if constexpr (std::is_same_v<Type, TruthTable>)
//   {
//     int numInt = 0;
//     for (const auto& nucleosoms : d_Chromosome.getOutTable())
//       for (const auto& nucleosom : nucleosoms)
//         if (nucleosom)
//           numInt++;
//     d_adaptationIndex = abs(0.5 - (numInt / (d_Chromosome.size() *
//     d_Chromosome.getOutput())));
//   }
// }

// template<typename Type, typename ParametersTypes>
// double ChromosomeType<Type, ParametersTypes>::getAdaptationIndex() const
// {
//   return d_adaptationIndex;
// }

// template<typename Type, typename ParametersTypes>
// void ChromosomeType<Type, ParametersTypes>::setAdaptationIndex(double
// i_adaptationIndex)
// {
//   d_adaptationIndex = i_adaptationIndex;
// }

// template<typename Type, typename ParametersTypes>
// std::string ChromosomeType<Type, ParametersTypes>::getName() const
// {
//   return d_name;
// }

// template<typename Type, typename ParametersTypes>
// bool ChromosomeType<Type, ParametersTypes>::operator== (const
// ChromosomeType<Type, ParametersTypes>& r) const
// {
//   return std::tie(d_adaptationIndex, d_Chromosome, d_name) ==
//   std::tie(r.d_adaptationIndex, r.d_Chromosome, r.d_name);
// }
