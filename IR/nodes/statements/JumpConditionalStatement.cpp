#include "JumpConditionalStatement.h"

namespace IRT {

void JumpConditionalStatement::Accept(Visitor& visitor) {
  visitor.Visit(*this);

}
JumpConditionalStatement::JumpConditionalStatement(
    LogicOperatorType type,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    Label label_true,
    Label label_false
) : operator_type_(type)
    , left_operand_(std::move(left))
    , right_operand_(std::move(right))
    , label_true_(std::move(label_true))
    , label_false_(std::move(label_false)) {

}
}
