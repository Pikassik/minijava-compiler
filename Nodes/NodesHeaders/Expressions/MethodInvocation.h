#pragma once

#include <Nodes/NodesHeaders/Expressions/Expression.h>
#include <Nodes/NodesHeaders/Statements/Statement.h>

#include <vector>

namespace node {

struct MethodInvocation : Expression, Statement {
  std::shared_ptr<Expression> class_expression;
  std::string method_identifier;
  std::vector<std::shared_ptr<Expression>> arguments;

  MethodInvocation(std::shared_ptr<Expression> class_expression,
                   std::string method_identifier,
                   std::vector<std::shared_ptr<Expression>> arguments);
  void Accept(Visitor& visitor) override;
};

} // namespace node