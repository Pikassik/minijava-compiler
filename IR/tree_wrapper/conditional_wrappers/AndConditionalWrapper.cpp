#include "AndConditionalWrapper.h"

#include "../../nodes/statements/SeqStatement.h"
#include "../../nodes/statements/LabelStatement.h"
namespace IRT {

std::shared_ptr<Statement> AndConditionalWrapper::ToConditional(Label true_label,
                                                                Label false_label) {
  using std::make_shared;
  Label middle_label;

  return make_shared<SeqStatement>(
      first_->ToConditional(middle_label, false_label),
      make_shared<SeqStatement>(
          make_shared<LabelStatement>(middle_label),
          second_->ToConditional(true_label, false_label)
      )
  );
}

AndConditionalWrapper::AndConditionalWrapper(std::shared_ptr<SubtreeWrapper> first,
                                             std::shared_ptr<SubtreeWrapper> second)
    : first_(std::move(first)), second_(std::move(second)) {
}

}