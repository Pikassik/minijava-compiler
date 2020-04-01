#pragma once

#include "Statement.h"

namespace node {

struct While : Statement {
  std::shared_ptr<Expression> condition;
  std::shared_ptr<Statement> then_statement;

  While(std::shared_ptr<Expression> condition,
        std::shared_ptr<Statement> then_statement);
  void Accept(Visitor& visitor) override;
};

} // namespace node