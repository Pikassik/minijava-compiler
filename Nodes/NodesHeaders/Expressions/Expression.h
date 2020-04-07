#pragma once

#include <Nodes/NodesHeaders/Node.h>
#include <Nodes/NodesHeaders/Decls/Type.h>

namespace node {

struct Expression : virtual Node {
  void SetType(std::shared_ptr<Type> type_v);
  Expression() = default;
  Expression(std::shared_ptr<Type> type);

  std::shared_ptr<Type> type;
};

} // namespace node