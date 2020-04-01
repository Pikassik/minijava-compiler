#include <Nodes/NodesHeaders/Decls/MethodDeclaration.h>

namespace node {

MethodDeclaration::
MethodDeclaration(std::shared_ptr<Type> type,
                  std::string identifier,
                  std::vector<std::shared_ptr<Formal>> formals,
                  std::shared_ptr<Scope> scope)
: type(std::move(type))
, identifier(std::move(identifier))
, formals(std::move(formals))
, scope(std::move(scope))
{}

void MethodDeclaration::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node