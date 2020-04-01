#include <Nodes/NodesHeaders/Statements/If.h>

namespace node {

If::If(std::shared_ptr<Expression> condition,
             std::shared_ptr<Statement> then_statement,
             std::shared_ptr<Statement> else_statement)
: condition(std::move(condition))
, then_statement(std::move(then_statement))
, else_statement(std::move(else_statement))
{}

void If::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node