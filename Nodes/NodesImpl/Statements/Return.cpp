#include <Nodes/NodesHeaders/Statements/Return.h>

namespace node {

Return::Return(std::shared_ptr<Expression> return_expression)
: return_expression(std::move(return_expression))
{}

void Return::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node