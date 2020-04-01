#include <Nodes/NodesHeaders/Statements/While.h>

namespace node {

While::While(std::shared_ptr<Expression> condition,
                   std::shared_ptr<Statement> then_statement)
: condition(std::move(condition))
, then_statement(std::move(then_statement))
{}

void While::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node