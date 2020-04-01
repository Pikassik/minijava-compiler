#include <Nodes/NodesHeaders/Expressions/Number.h>

namespace node {

Number::Number(int number)
: number(number)
{}

void Number::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}


} // namespace node