#include <Nodes/NodesHeaders/Expressions/Mul.h>

namespace node {

void Mul::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node