#include <Nodes/NodesHeaders/Expressions/Not.h>

namespace node {

Not::Not(std::shared_ptr<Expression> argument)
: argument(std::move(argument))
{}

void Not::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node