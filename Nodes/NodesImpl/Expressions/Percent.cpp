#include <Nodes/NodesHeaders/Expressions/Percent.h>

namespace node {

void Percent::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node