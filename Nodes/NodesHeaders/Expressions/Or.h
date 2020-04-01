#pragma once

#include <Nodes/NodesHeaders/Expressions/BinaryOp.h>

namespace node {

struct Or : BinaryOp {
  using BinaryOp::BinaryOp;
  void Accept(Visitor& visitor) override;
};


} // namespace node