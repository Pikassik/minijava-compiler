#include "ExpStatement.h"

using namespace IRT;

std::shared_ptr<Expression> ExpStatement::GetExpression() {
  return expression_;
}

ExpStatement::ExpStatement(std::shared_ptr<Expression> expression)
    : expression_(std::move(expression)) {

}

void ExpStatement::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}
