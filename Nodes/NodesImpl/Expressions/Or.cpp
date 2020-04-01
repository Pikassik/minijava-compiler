#include <Nodes/NodesHeaders/Expressions/Or.h>

namespace node {

void Or::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node