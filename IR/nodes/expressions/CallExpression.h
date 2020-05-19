#pragma once

#include "Expression.h"
namespace IRT {
class CallExpression: public Expression {
 public:
  CallExpression(std::shared_ptr<Expression> expression,
                 std::shared_ptr<ExpressionList> args);
  void Accept(Visitor& visitor) override;
  std::shared_ptr<Expression> function_name_;
  std::shared_ptr<ExpressionList> args_;

};
}


