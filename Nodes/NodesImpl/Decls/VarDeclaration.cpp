#include <Nodes/NodesHeaders/Decls/VarDeclaration.h>

namespace node {

VarDeclaration::VarDeclaration(std::shared_ptr<Type> type,
                               std::string identifier)
: type(std::move(type))
, identifier(std::move(identifier))
{}

void VarDeclaration::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node