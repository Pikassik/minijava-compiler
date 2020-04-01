#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

struct At : Expression {
  std::shared_ptr<Expression> array;
  std::shared_ptr<Expression> index;

  At(std::shared_ptr<Expression> array,
     std::shared_ptr<Expression> index);
  void Accept(Visitor& visitor) override;
};


} // namespace node