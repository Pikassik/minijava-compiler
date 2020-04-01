#include <Nodes/NodesHeaders/Expressions/Div.h>

namespace node {

void Div::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node