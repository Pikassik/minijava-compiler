#include "CallExpression.h"

namespace IRT {

void CallExpression::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}
CallExpression::CallExpression(
    std::shared_ptr<Expression> expression,
    std::shared_ptr<ExpressionList> args
  ): function_name_(std::move(expression)), args_(std::move(args)) {

}

}