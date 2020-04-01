#pragma once

#include "Lvalue.h"
#include "Statement.h"

namespace node {

struct Assign : Statement {
  std::shared_ptr<Lvalue> lvalue;
  std::shared_ptr<Expression> expression;

  Assign(std::shared_ptr<Lvalue>,
         std::shared_ptr<Expression> expression);
  void Accept(Visitor& visitor) override;
};

} // namespace node