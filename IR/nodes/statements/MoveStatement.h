#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"
namespace IRT {

class MoveStatement : public Statement {
 public:
  MoveStatement(std::shared_ptr<Expression> source,
                std::shared_ptr<Expression> target);
  void Accept(Visitor& visitor) override;
  std::shared_ptr<Expression> source_;
  std::shared_ptr<Expression> target_;
};

};


