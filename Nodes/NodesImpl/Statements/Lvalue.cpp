#include <Nodes/NodesHeaders/Statements/Lvalue.h>

namespace node {

Lvalue::Lvalue(std::string identifier,
                     std::shared_ptr<Expression> index_expression)
: identifier(std::move(identifier))
, index_expression(std::move(index_expression))
{}

void Lvalue::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node