#include <Nodes/NodesHeaders/Expressions/More.h>

namespace node {

void More::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node