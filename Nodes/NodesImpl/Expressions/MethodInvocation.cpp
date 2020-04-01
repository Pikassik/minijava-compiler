#include <Nodes/NodesHeaders/Expressions/MethodInvocation.h>

namespace node {

MethodInvocation::
MethodInvocation(std::shared_ptr<Expression> class_expression,
                 std::string method_identifier,
                 std::vector<std::shared_ptr<Expression>> arguments)
: class_expression(std::move(class_expression))
, method_identifier(std::move(method_identifier))
, arguments(std::move(arguments))
{}

void MethodInvocation::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node