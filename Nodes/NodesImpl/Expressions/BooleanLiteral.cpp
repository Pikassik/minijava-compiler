#include <Nodes/NodesHeaders/Expressions/BooleanLiteral.h>

namespace node {

BooleanLiteral::BooleanLiteral(bool is_true)
: is_true(is_true)
{}

void BooleanLiteral::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

}