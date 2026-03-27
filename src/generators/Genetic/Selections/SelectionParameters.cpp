/**
 * @file SelectionParameters.cpp
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Чернявских Илья Игоревич <fuuulkrum7@gmail.com>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Asdfds1 <ziazetdinov@list.ru>
 */

#include <cstdint>
#include <tuple>

#include "SelectionParameters.hpp"

namespace CG_Gen {

void SelectionParameters::setSelectionType(SelectionTypes i_selectionType) {
  d_selectionType = i_selectionType;
}

SelectionTypes SelectionParameters::getSelectionType() const {
  return d_selectionType;
}

int32_t SelectionParameters::getNumOfSurvivors() const {
  return d_numOfSurvivors;
}

void SelectionParameters::setNumOfSurvivors(int32_t i_survivors) {
  d_numOfSurvivors = i_survivors;
}

bool SelectionParameters::operator==(const SelectionParameters &r) const {
  return std::tie(d_selectionType, d_numOfSurvivors) ==
         std::tie(r.d_selectionType, r.d_numOfSurvivors);
}

} // namespace CG_Gen
