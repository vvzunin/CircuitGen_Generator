#include "ParentsParameters.h"

void ParentsParameters::setParentsType(ParentsTypes i_parentsTypes)
{
  d_parentsType = i_parentsTypes;
}

ParentsTypes ParentsParameters::getParentsType() const
{
  return d_parentsType;
}
