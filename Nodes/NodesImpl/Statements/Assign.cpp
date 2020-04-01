#include <Nodes/NodesHeaders/Statements/Assign.h>

namespace node {

Assign::Assign(std::shared_ptr<Lvalue> lvalue,
                     std::shared_ptr<Expression> expression)
: lvalue(std::move(lvalue))
, expression(std::move(expression))
{}

void Assign::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node