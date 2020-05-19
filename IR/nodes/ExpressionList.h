#pragma once

#include "BaseElement.h"

#include <vector>
#include <memory>

namespace IRT {
class Expression;
class ExpressionList : public BaseElement {
 public:
  ExpressionList() = default;

  void Add(std::shared_ptr<Expression> expression);
  void Accept(Visitor& visitor) override;

  std::vector<std::shared_ptr<Expression>> expressions_;

};

}

