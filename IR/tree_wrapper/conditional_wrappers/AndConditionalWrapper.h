//
// Created by akhtyamovpavel on 4/8/20.
//


#pragma once

#include "ConditionalWrapper.h"
namespace IRT {

class AndConditionalWrapper : public ConditionalWrapper {
 public:
  AndConditionalWrapper(std::shared_ptr<SubtreeWrapper> first,
                        std::shared_ptr<SubtreeWrapper> second);
  std::shared_ptr<Statement> ToConditional(Label true_label,
                                           Label false_label) override;
 private:
  std::shared_ptr<SubtreeWrapper> first_;
  std::shared_ptr<SubtreeWrapper> second_;
};

}

