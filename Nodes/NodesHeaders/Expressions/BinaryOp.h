#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct BinaryOp : Expression {
  std::shared_ptr<Expression> lhvalue;
  std::shared_ptr<Expression> rhvalue;

  BinaryOp(std::shared_ptr<Expression> lhvalue,
           std::shared_ptr<Expression> rhvalue);
};


} // namespace node