#pragma once

#include "SubtreeWrapper.h"
#include "../nodes/statements/Statement.h"
namespace IRT {

class ExpressionWrapper : public SubtreeWrapper {
 public:

  explicit ExpressionWrapper(std::shared_ptr<Expression> expression);
  virtual ~ExpressionWrapper() = default;
  std::shared_ptr<Expression> ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;
 private:
  std::shared_ptr<Expression> expression_;
};

}

