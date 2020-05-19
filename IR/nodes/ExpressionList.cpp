#include "ExpressionList.h"

namespace IRT {
void ExpressionList::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}
void ExpressionList::Add(std::shared_ptr<Expression> expression) {
  expressions_.push_back(expression);
}

}