#include <Nodes/NodesHeaders/Decls/Type.h>

namespace node {

Type::Type(std::string identifier, bool is_array)
: identifier(std::move(identifier))
, is_array(is_array)
{}

void Type::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node