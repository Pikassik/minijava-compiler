#pragma once

#include "ConditionalWrapper.h"
namespace IRT {
class OrConditionalWrapper: public ConditionalWrapper {
 public:
  OrConditionalWrapper(std::shared_ptr<SubtreeWrapper> first,
                       std::shared_ptr<SubtreeWrapper> second);
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;

  std::shared_ptr<SubtreeWrapper> first_;
  std::shared_ptr<SubtreeWrapper> second_;
};

}


