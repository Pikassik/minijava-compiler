#pragma once

#include <Nodes/NodesHeaders/Statements/Statement.h>
#include "MemberDeclaration.h"
#include "Type.h"

namespace node {

struct VarDeclaration : virtual Statement, virtual MemberDeclaration {
  std::shared_ptr<Type> type;
  std::string identifier;

  VarDeclaration(std::shared_ptr<Type> type,
                 std::string identifier);
  void Accept(Visitor& visitor) override;
};

} // namespace node