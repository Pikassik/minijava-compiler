#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct Length : Expression {
  std::shared_ptr<Expression> array_expression;

  Length(std::shared_ptr<Expression> array_expression);
  void Accept(Visitor& visitor) override;
};

} // namespace node