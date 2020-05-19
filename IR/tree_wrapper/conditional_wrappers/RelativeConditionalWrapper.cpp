#include "RelativeConditionalWrapper.h"
#include "../../nodes/statements/JumpConditionalStatement.h"


namespace IRT {

std::shared_ptr<Statement>
RelativeConditionalWrapper::ToConditional(Label true_label, Label false_label) {
  return std::make_shared<JumpConditionalStatement>(
    operator_type_,
    lhs_,
    rhs_,
    std::move(true_label),
    std::move(false_label)
  );
}

RelativeConditionalWrapper::RelativeConditionalWrapper(
    LogicOperatorType type,
    std::shared_ptr<Expression> lhs,
    std::shared_ptr<Expression> rhs
): operator_type_(type), lhs_(std::move(lhs)), rhs_(std::move(rhs))  {
}
}