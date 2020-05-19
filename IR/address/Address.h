#pragma once

#include "../nodes/expressions/Expression.h"
namespace IRT {

class Address {
 public:
  virtual ~Address() = default;
  virtual std::shared_ptr<Expression> ToExpression() = 0;
};

}
