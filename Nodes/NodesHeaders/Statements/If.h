#pragma once

#include "Statement.h"

namespace node {

struct If : Statement {
  std::shared_ptr<Expression> condition;
  std::shared_ptr<Statement> then_statement;
  std::shared_ptr<Statement> else_statement;

  If(std::shared_ptr<Expression> condition,
     std::shared_ptr<Statement> then_statement,
     std::shared_ptr<Statement> else_statement = nullptr);
  void Accept(Visitor& visitor) override;
};

} // namespace node