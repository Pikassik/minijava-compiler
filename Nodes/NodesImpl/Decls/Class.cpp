#include <Nodes/NodesHeaders/Decls/Class.h>

namespace node {

Class::Class(std::string identifier,
             std::vector<std::shared_ptr<MethodDeclaration>> methods,
             std::vector<std::shared_ptr<VarDeclaration>> fields)
: identifier(std::move(identifier))
, methods(std::move(methods))
, fields(std::move(fields))
{}

Class::Class(std::string identifier,
             std::string base,
             std::vector<std::shared_ptr<MethodDeclaration>> methods,
             std::vector<std::shared_ptr<VarDeclaration>> fields)
: identifier(std::move(identifier))
, base(std::move(base))
, methods(std::move(methods))
, fields(std::move(fields))
{}

void Class::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node