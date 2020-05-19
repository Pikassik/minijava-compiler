//
// Created by akhtyamovpavel on 4/8/20.
//

#include "NegateConditionalWrapper.h"

namespace IRT {

std::shared_ptr<Statement> NegateConditionalWrapper::ToConditional(Label true_label,
                                                                   Label false_label) {
  return wrapper_->ToConditional(false_label, true_label);
}

NegateConditionalWrapper::NegateConditionalWrapper(std::shared_ptr<SubtreeWrapper> wrapper)
    : wrapper_(std::move(wrapper)) {
}
}