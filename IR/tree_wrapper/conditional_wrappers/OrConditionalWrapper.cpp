#include "OrConditionalWrapper.h"

#include "../../nodes/statements/LabelStatement.h"
#include "../../nodes/statements/SeqStatement.h"
namespace IRT {

std::shared_ptr<Statement> OrConditionalWrapper::ToConditional(Label true_label,
                                                               Label false_label) {
  Label middle_label;
  return std::make_shared<SeqStatement>(
      first_->ToConditional(true_label, middle_label),
      std::make_shared<SeqStatement>(
          std::make_shared<LabelStatement>(middle_label),
          second_->ToConditional(true_label, std::move(false_label))
      )
  );
}

OrConditionalWrapper::OrConditionalWrapper(std::shared_ptr<SubtreeWrapper> first,
                                           std::shared_ptr<SubtreeWrapper> second)
    : first_(std::move(first)), second_(std::move(second)) {

}
}