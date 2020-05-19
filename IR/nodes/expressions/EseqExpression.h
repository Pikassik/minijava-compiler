#pragma once

#include "../statements/Statement.h"
#include "Expression.h"
namespace IRT {

class EseqExpression: public Expression {
 public:
  EseqExpression(std::shared_ptr<Statement> statement,
                 std::shared_ptr<Expression> expression);
  void Accept(Visitor& visitor) override;

  std::shared_ptr<Statement> statement_;
  std::shared_ptr<Expression> expression_;
};

}


