#pragma once

#include "Statement.h"

namespace node {

struct Return : Statement {
  std::shared_ptr<Expression> return_expression;

  Return(std::shared_ptr<Expression> return_expression);
  void Accept(Visitor& visitor) override;
};

} // namespace node