#include <Nodes/NodesHeaders/Expressions/Subtract.h>

namespace node {

void Subtract::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node