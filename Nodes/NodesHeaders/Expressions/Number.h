#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct Number : Expression {
  int number;

  explicit Number(int number);
  void Accept(Visitor& visitor) override;
};

} // namespace node