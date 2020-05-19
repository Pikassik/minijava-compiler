#include "ConditionalWrapper.h"
#include "../../generators/Temporary.h"
#include "../../nodes/expressions/TempExpression.h"
#include "../../nodes/expressions/ConstExpression.h"
#include "../../nodes/expressions/EseqExpression.h"
#include "../../nodes/statements/SeqStatement.h"
#include "../../nodes/statements/MoveStatement.h"
#include "../../nodes/statements/LabelStatement.h"

namespace IRT {
std::shared_ptr<Expression> IRT::ConditionalWrapper::ToExpression() {
  using std::make_shared;
  auto temp_expression = std::make_shared<TempExpression>(Temporary());
  Label label_true;
  Label label_false;
  return make_shared<EseqExpression>(
    make_shared<SeqStatement>(
      make_shared<MoveStatement>(temp_expression, make_shared<ConstExpression>(1)),
      make_shared<SeqStatement>(
        ToConditional(label_true, label_false),
        make_shared<SeqStatement>(
          make_shared<LabelStatement>(label_false),
          make_shared<SeqStatement>(
            make_shared<MoveStatement>(temp_expression, make_shared<ConstExpression>(0)),
            make_shared<LabelStatement>(label_true)
          )
        )
      )
    ),
    temp_expression
  );
}

std::shared_ptr<Statement> IRT::ConditionalWrapper::ToStatement() {
  return nullptr;
}

}