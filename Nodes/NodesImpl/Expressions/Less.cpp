#include <Nodes/NodesHeaders/Expressions/Less.h>

namespace node {

void Less::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node