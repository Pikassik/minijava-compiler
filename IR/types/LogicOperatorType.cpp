#include "LogicOperatorType.h"
#include <cassert>
std::string IRT::ToString(IRT::LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::EQ:
      return "EQ";
    case LogicOperatorType::NE:
      return "NE";
    case LogicOperatorType::LT:
      return "LT";
    case LogicOperatorType::GT:
      return "GT";
    default: assert(false);
  }
}
