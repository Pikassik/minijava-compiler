#include <Nodes/NodesHeaders/Decls/Formal.h>

namespace node {

Formal::Formal(std::shared_ptr<Type> type,
               std::string identifier)
: type(std::move(type))
, identifier(std::move(identifier))
{}

void Formal::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node
