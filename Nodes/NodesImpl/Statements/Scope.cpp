#include <Nodes/NodesHeaders/Statements/Scope.h>

namespace node {

Scope::Scope(std::vector<std::shared_ptr<Statement>> statements)
: statements(std::move(statements))
{}

void Scope::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node