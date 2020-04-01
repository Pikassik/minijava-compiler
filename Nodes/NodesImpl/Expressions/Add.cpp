#include <Nodes/NodesHeaders/Expressions/Add.h>

namespace node {

void Add::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node