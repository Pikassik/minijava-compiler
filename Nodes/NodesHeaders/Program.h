#pragma once

#include "Nodes/NodesHeaders/Decls/Class.h"

namespace node {

struct Program : Node {
  std::vector<std::shared_ptr<Class>> classes;

  Program(std::vector<std::shared_ptr<Class>> classes);
  void Accept(Visitor& visitor) override;
};

} // namespace node