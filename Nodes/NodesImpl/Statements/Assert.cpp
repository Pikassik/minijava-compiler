#include <Nodes/NodesHeaders/Statements/Assert.h>

namespace node {

Assert::Assert(std::shared_ptr<Expression> condition)
: condition(std::move(condition))
{}

void Assert::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node