#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct BooleanLiteral : Expression {
  bool is_true;

  explicit BooleanLiteral(bool is_true);
  void Accept(Visitor& visitor) override;
};

} // namespace node