#pragma once

#include "Statement.h"
#include "../../types/LogicOperatorType.h"
#include "../expressions/Expression.h"
#include "../../generators/Label.h"
namespace IRT {
class JumpConditionalStatement : public Statement {
 public:
  JumpConditionalStatement(
      LogicOperatorType type,
      std::shared_ptr<Expression> left,
      std::shared_ptr<Expression> right,
      Label label_true,
      Label label_false
      );
  void Accept(Visitor& visitor);
  LogicOperatorType operator_type_;
  Label label_true_;
  Label label_false_;
  std::shared_ptr<Expression> left_operand_;
  std::shared_ptr<Expression> right_operand_;

};

}


