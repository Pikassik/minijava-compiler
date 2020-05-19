#pragma once
#include "Statement.h"
#include "../../generators/Label.h"
namespace IRT {

class LabelStatement : public Statement {
 public:
  explicit LabelStatement(Label label);
  void Accept(Visitor& visitor) override;
  Label label_;
};

}

