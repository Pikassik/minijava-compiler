#pragma once

#include "../nodes/expressions/Expression.h"
#include "../nodes/statements/Statement.h"

namespace IRT {

struct IrtStorage {
  std::shared_ptr<Expression> expression_ = nullptr;
  std::shared_ptr<Statement> statement_ = nullptr;
  std::shared_ptr<ExpressionList> expression_list_ = nullptr;
};

}
