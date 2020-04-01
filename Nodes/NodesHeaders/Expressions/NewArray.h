#pragma once

#include <Nodes/NodesHeaders/Decls/Type.h>
#include <Nodes/NodesHeaders/Expressions/Expression.h>


namespace node {

struct NewArray : Expression {
  std::shared_ptr<Type> type;
  std::shared_ptr<Expression> size_expression;

  NewArray(std::shared_ptr<Type> type,
           std::shared_ptr<Expression> size_expression);
  void Accept(Visitor& visitor) override;
};

} // namespace node