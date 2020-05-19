#pragma once

#include "Expression.h"
namespace IRT {

class MemExpression : public Expression {
 public:
  MemExpression(std::shared_ptr<IRT::Expression> expression);
  void Accept(Visitor& visitor) override;
  std::shared_ptr<Expression> expression_;
};

}


