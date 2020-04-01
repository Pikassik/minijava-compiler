#pragma once

#include "Statement.h"

namespace node {

struct Lvalue : Statement {
  std::string identifier;
  std::shared_ptr<Expression> index_expression;

  Lvalue(std::string identifier,
         std::shared_ptr<Expression> index_expression = nullptr);
  void Accept(Visitor& visitor) override;
};

} // namespace node