#include "AddressInRegister.h"

#include "../nodes/expressions/TempExpression.h"

namespace IRT {
std::shared_ptr<Expression> AddressInRegister::ToExpression() {
  return std::make_shared<TempExpression>(temp_);
}
AddressInRegister::AddressInRegister(Temporary temp)
: temp_(std::move(temp)) {
}

}
