#pragma once
#include "Statement.h"
namespace IRT {
class SeqStatement : public Statement {
 public:
  SeqStatement(std::shared_ptr<Statement> first,
               std::shared_ptr<Statement> second);
  void Accept(Visitor& visitor) override;
  std::shared_ptr<Statement> first_statement_;
  std::shared_ptr<Statement> second_statement_;
};

}


