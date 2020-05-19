#include "MoveStatement.h"
namespace IRT {
void MoveStatement::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

MoveStatement::MoveStatement(
    std::shared_ptr<Expression> source,
    std::shared_ptr<Expression> target
  ): source_(std::move(source)), target_(std::move(target)) {

}

}
