#pragma once

#include <Nodes/NodesHeaders/Node.h>

namespace node {

struct Type : Node {
  std::string identifier;
  bool is_array;

  Type(std::string identifier, bool is_array = false);
  void Accept(Visitor& visitor) override;
};

}