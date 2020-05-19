#include <cassert>
#include "StatementWrapper.h"

namespace IRT {

std::shared_ptr<Expression> StatementWrapper::ToExpression() {
  assert(false);
}
std::shared_ptr<Statement> StatementWrapper::ToStatement() {
  return statement_;
}

std::shared_ptr<Statement> StatementWrapper::ToConditional(Label true_label,
                                                           Label false_label) {
  assert(false);
}

StatementWrapper::StatementWrapper(std::shared_ptr<Statement> statement)
    : statement_(std::move(statement)) {

}

}