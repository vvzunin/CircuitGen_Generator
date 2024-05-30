#pragma once
#include <cstdint>

#include "../Parents/ParentsParameters.hpp"

enum RecombinationTypes {
  CrossingEachExitInTurnMany,  // relative to several reference points
  CrossingUniform,             //
  CrossingTriadic,
  CrossingReducedReplacement,
  CrossingShuffling
};

class RecombinationParameters {
public:
  RecombinationTypes getRecombinationType() const;
  ParentsParameters  getParentsParameters() const;
  int32_t            getRefPoints() const;
  void               setRefPoints(int32_t i_refPoints);
  double             getMaskProbability() const;
  void               setRecombinationParameters(int32_t i_rp);
  int32_t            getRecombinationParameters() const;
  bool               operator==(const RecombinationParameters& r) const;
  void               setMaskProbability(double i_maskProbability);
  void               setParentsParameters(
                    ParentsTypes  i_parentsType,
                    const int32_t i_tournamentSize
                );
  void setRecombinationType(RecombinationTypes i_recombinationType);

private:
  RecombinationTypes d_recombinationType =
      RecombinationTypes::CrossingEachExitInTurnMany;
  ParentsParameters d_parentsParameters   = ParentsParameters();
  int32_t           d_refPoints           = 1;
  double            d_maskProbability     = 0.5;
  int32_t           d_recombinationNumber = 1;
};
