#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>

#include <string>

namespace node {

struct Identifier : Expression {
  std::string identifier;

  Identifier(std::string identifier);
  void Accept(Visitor& visitor) override;
};


} // namespace node