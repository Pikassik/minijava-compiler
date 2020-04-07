#include <Nodes/NodesHeaders/Expressions/New.h>

namespace node {

New::New(std::shared_ptr<Type> type)
: Expression(std::move(type))
{}

New::New(std::string type_identifier)
: Expression(std::make_shared<Type>(type_identifier))
{}

void New::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node