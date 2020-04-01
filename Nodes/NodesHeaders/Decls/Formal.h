#pragma once

#include "Type.h"

namespace node {

struct Formal : Node {
  std::shared_ptr<Type> type;
  std::string identifier;

  Formal(std::shared_ptr<Type> type,
         std::string identifier);
  void Accept(Visitor& visitor) override;
};

} // namespace node