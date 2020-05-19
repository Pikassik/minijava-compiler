#include "ExpressionWrapper.h"
#include "../nodes/statements/ExpStatement.h"
#include "../nodes/statements/JumpConditionalStatement.h"
#include "../nodes/expressions/ConstExpression.h"

namespace IRT {

std::shared_ptr<Expression> ExpressionWrapper::ToExpression() {
  return expression_;
}

std::shared_ptr<Statement> ExpressionWrapper::ToStatement() {
  return std::make_shared<ExpStatement>(expression_);
}

std::shared_ptr<Statement> ExpressionWrapper::ToConditional(Label true_label,
                                                            Label false_label) {
  return std::make_shared<JumpConditionalStatement>(
      LogicOperatorType::NE,
      expression_,
      std::shared_ptr<ConstExpression>(0),
      true_label,
      false_label
  );
}

ExpressionWrapper::ExpressionWrapper(std::shared_ptr<Expression> expression)
    : expression_(std::move(expression)) {
}

}