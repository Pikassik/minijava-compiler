#pragma once

#include "Statement.h"

namespace node {

struct Assert : Statement {
  std::shared_ptr<Expression> condition;

  Assert(std::shared_ptr<Expression> condition);
  void Accept(Visitor& visitor) override;
};

} // namespace node