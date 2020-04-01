#include <Nodes/NodesHeaders/Expressions/At.h>

namespace node {

At::At(std::shared_ptr<Expression> array,
       std::shared_ptr<Expression> index)
: array(std::move(array))
, index(std::move(index))
{}

void At::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node