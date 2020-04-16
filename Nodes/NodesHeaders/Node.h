#pragma once

#include <memory>

#include <Parser/location.hh>
#include <Visitors/Visitor.h>

namespace node {

struct Node : std::enable_shared_from_this<Node> {
  virtual void Accept(Visitor& visitor) = 0;
  void SetLocation (const yy::location& loc_);
  yy::location loc;
};

} // namespace node