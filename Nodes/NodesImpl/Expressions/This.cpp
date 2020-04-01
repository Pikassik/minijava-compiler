#include <Nodes/NodesHeaders/Expressions/This.h>

namespace node {

void This::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node