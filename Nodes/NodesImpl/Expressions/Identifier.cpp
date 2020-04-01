#include <Nodes/NodesHeaders/Expressions/Identifier.h>

namespace node {

Identifier::Identifier(std::string identifier)
: identifier(std::move(identifier))
{}

void Identifier::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node