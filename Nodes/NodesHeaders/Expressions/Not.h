#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct Not : Expression {
  std::shared_ptr<Expression> argument;

  Not(std::shared_ptr<Expression> argument);
  void Accept(Visitor& visitor) override;
};

} // namespace node