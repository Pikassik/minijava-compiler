#include "EseqExpression.h"
namespace IRT {


EseqExpression::EseqExpression(std::shared_ptr<Statement> statement,
                               std::shared_ptr<Expression> expression):
statement_(std::move(statement)), expression_(std::move(expression)) {

}

void EseqExpression::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}

}
