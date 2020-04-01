#pragma once

#include "MethodDeclaration.h"
#include "VarDeclaration.h"

namespace node {

struct Class : Node {
  std::string identifier;
  std::string base;
  std::vector<std::shared_ptr<MethodDeclaration>> methods;
  std::vector<std::shared_ptr<VarDeclaration>> fields;


  Class(std::string identifier,
        std::vector<std::shared_ptr<MethodDeclaration>> methods,
        std::vector<std::shared_ptr<VarDeclaration>> fields);
  Class(std::string identifier,
        std::string base,
        std::vector<std::shared_ptr<MethodDeclaration>> methods,
        std::vector<std::shared_ptr<VarDeclaration>> fields);
  void Accept(Visitor& visitor) override;
};

} // namespace node