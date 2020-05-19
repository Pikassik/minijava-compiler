#pragma once

#include "ConditionalWrapper.h"
namespace IRT {
class NegateConditionalWrapper : public ConditionalWrapper {
 public:
  explicit NegateConditionalWrapper(std::shared_ptr<SubtreeWrapper> wrapper);
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;
 private:
  std::shared_ptr<SubtreeWrapper> wrapper_;
};

}


