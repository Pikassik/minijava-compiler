#include <Nodes/NodesHeaders/Expressions/And.h>

namespace node { 

void And::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node