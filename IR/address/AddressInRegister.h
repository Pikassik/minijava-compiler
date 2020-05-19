#pragma once
#include "../generators/Temporary.h"
#include "Address.h"
namespace IRT {

class AddressInRegister : public Address {
 public:
  AddressInRegister(Temporary temp);
  std::shared_ptr<Expression> ToExpression() override;
 private:
  Temporary temp_;
};

}

