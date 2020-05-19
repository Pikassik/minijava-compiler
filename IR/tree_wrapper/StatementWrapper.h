#pragma once

#include "SubtreeWrapper.h"
namespace IRT {
class StatementWrapper : public SubtreeWrapper {
 public:
  explicit StatementWrapper(std::shared_ptr<Statement> statement);
  std::shared_ptr<Expression> ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;
 private:
  std::shared_ptr<Statement> statement_;
};

}

