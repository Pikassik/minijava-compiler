#include "BinopExpression.h"

namespace IRT {

void BinopExpression::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}
BinopExpression::BinopExpression(
    BinaryOperatorType type,
    std::shared_ptr<Expression> first,
    std::shared_ptr<Expression> second
  ) : operator_type_(type), first_(std::move(first)), second_(std::move(second)) {

}

}