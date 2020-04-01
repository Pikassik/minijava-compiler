#pragma once

#include <Nodes/NodesHeaders/Statements/Scope.h>
#include "MemberDeclaration.h"
#include "Type.h"
#include "Formal.h"

#include <vector>

namespace node {

struct MethodDeclaration : MemberDeclaration {
  std::string identifier;
  std::shared_ptr<Type> type;
  std::vector<std::shared_ptr<Formal>> formals;
  std::shared_ptr<Scope> scope;

  MethodDeclaration(std::shared_ptr<Type> type,
                    std::string identifier,
                    std::vector<std::shared_ptr<Formal>> formals,
                    std::shared_ptr<Scope> scope);
  void Accept(Visitor& visitor) override;
};

} // namespace node

