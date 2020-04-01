#include <Nodes/NodesHeaders/Expressions/Equals.h>

namespace node {

void Equals::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node