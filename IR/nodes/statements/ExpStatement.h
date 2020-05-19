#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"


namespace IRT {

class ExpStatement : public Statement {
 public:
  explicit ExpStatement(std::shared_ptr<Expression> expression);
  std::shared_ptr<Expression> GetExpression();
  ~ExpStatement() override = default;
  void Accept(Visitor& visitor) override;

 private:
  std::shared_ptr<Expression> expression_;
};

}

