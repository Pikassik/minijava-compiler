#pragma once

#include "../SubtreeWrapper.h"
namespace IRT {

class ConditionalWrapper : public SubtreeWrapper {
 public:
  virtual ~ConditionalWrapper() = default;
  std::shared_ptr<Expression> ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;

};

}


