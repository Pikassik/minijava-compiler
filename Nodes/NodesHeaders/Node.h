#pragma once

#include <memory>

#include <Visitors/Visitor.h>
//class Visitor;

namespace node {

struct Node : std::enable_shared_from_this<Node> {
  virtual void Accept(Visitor& visitor) = 0;
};

} // namespace node