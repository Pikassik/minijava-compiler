#pragma once

#include <Nodes/NodesHeaders/Node.h>
#include "Statement.h"

#include <vector>

namespace node {

struct Scope : Statement {
  std::vector<std::shared_ptr<Statement>> statements;

  Scope() = default;
  Scope(std::vector<std::shared_ptr<Statement>> statements);
  void Accept(Visitor& visitor) override;
};

} // namespace node