#pragma once

#include "../../types/BinaryOperatorType.h"
#include "Expression.h"
namespace IRT {
class BinopExpression : public Expression {
 public:
  BinopExpression(BinaryOperatorType type,
                  std::shared_ptr<Expression>first,
                  std::shared_ptr<Expression> second);
  void Accept(Visitor& visitor) override;
  BinaryOperatorType operator_type_;
  std::shared_ptr<Expression> first_;
  std::shared_ptr<Expression> second_;
};

}


