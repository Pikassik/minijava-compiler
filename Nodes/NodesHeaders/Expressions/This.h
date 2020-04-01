#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct This : Expression {
  void Accept(Visitor& visitor) override;
};

} // namespace node