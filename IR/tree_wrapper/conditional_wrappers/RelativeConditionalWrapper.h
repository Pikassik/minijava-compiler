#pragma once

#include "ConditionalWrapper.h"
#include "../../types/LogicOperatorType.h"


namespace IRT {
class RelativeConditionalWrapper: public ConditionalWrapper {
 public:
  RelativeConditionalWrapper(LogicOperatorType type,
                             std::shared_ptr<Expression> lhs,
                             std::shared_ptr<Expression> rhs);
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;

  std::shared_ptr<Expression> lhs_;
  std::shared_ptr<Expression> rhs_;
  LogicOperatorType operator_type_;

};

}


