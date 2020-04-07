#include <Nodes/NodesHeaders/Expressions/NewArray.h>

namespace node {

NewArray::NewArray(std::shared_ptr<Type> type,
                   std::shared_ptr<Expression> size_expression)
: Expression(std::move(type))
, size_expression(std::move(size_expression))
{}

void NewArray::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node