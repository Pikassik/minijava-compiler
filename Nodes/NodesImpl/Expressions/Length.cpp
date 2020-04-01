#include <Nodes/NodesHeaders/Expressions/Length.h>

namespace node {

Length::Length(std::shared_ptr<Expression> array_expression)
: array_expression(std::move(array_expression))
{}

void Length::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node