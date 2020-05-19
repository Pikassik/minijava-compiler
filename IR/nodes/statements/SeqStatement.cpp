#include "SeqStatement.h"

namespace IRT {

void SeqStatement::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}
SeqStatement::SeqStatement(std::shared_ptr<Statement> first,
                           std::shared_ptr<Statement> second)
  : first_statement_(std::move(first))
  , second_statement_(std::move(second)) {

}
}