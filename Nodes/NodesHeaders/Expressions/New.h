#pragma once

#include <Nodes/NodesHeaders/Decls/Type.h>
#include <Nodes/NodesHeaders/Expressions/Expression.h>


namespace node {

static constexpr size_t kNotArray = SIZE_MAX;

struct New : Expression {
  New(std::shared_ptr<Type> type);
  New(std::string type_identifier);
  void Accept(Visitor& visitor) override;
};

} // namespace node