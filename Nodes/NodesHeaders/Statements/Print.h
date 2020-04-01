#pragma once

#include "Statement.h"

namespace node {

struct Print : Statement {
  std::shared_ptr<Expression> print_expression;

  Print(std::shared_ptr<Expression> print_expression);
  void Accept(Visitor& visitor) override;
};
} // namespace node