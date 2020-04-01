#include <Nodes/NodesHeaders/Statements/Print.h>

namespace node {

Print::Print(std::shared_ptr<Expression> print_expression)
: print_expression(std::move(print_expression))
{}

void Print::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node