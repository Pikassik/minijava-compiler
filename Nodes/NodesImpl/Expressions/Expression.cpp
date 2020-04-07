#include <Nodes/NodesHeaders/Expressions/Expression.h>

namespace node {

void Expression::SetType(std::shared_ptr<Type> type_v) {
  type = std::move(type_v);
}

Expression::Expression(std::shared_ptr<Type> type)
: type(std::move(type)) {
}

} // namespace node