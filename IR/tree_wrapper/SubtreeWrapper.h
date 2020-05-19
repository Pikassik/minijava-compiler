#pragma once

#include "../generators/Label.h"
#include "../nodes/expressions/Expression.h"
#include "../nodes/statements/Statement.h"

#include <memory>

namespace IRT {
class SubtreeWrapper {
 public:
  virtual ~SubtreeWrapper() = default;
  virtual std::shared_ptr<Expression> ToExpression() = 0;
  virtual std::shared_ptr<Statement> ToStatement() = 0;
  virtual std::shared_ptr<Statement> ToConditional(Label true_label,
                                                   Label false_label) = 0;
};

}