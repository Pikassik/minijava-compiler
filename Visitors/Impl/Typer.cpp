#include "../Typer.h"

#include <Exception/LocalizedError.h>
#include <Nodes/Nodes.h>

#define pass throw std::runtime_error("impossible state")

void SetTypes(node::Program& program,
              std::shared_ptr<ProgramTable> program_table) {
  Typer typer(std::move(program_table));
  typer.Visit(program);
}

Typer::Typer(std::shared_ptr<ProgramTable> program_table)
    : program_table_(std::move(program_table)){
}

void Typer::Visit(node::Node&) {
  pass;
}

void Typer::Visit(node::Class& node) {
  current_class_ = program_table_->GetClass(node.identifier);
  current_class_node_ =
      std::dynamic_pointer_cast<node::Class>(node.shared_from_this());

  scopes_sizes_.push_back(0);
  for (auto&& field: node.fields) {
    field->Accept(*this);
  }
  scopes_sizes_.pop_back();

  for (auto&& method: node.methods) {
    method->Accept(*this);
  }
}

void Typer::Visit(node::Formal&) {
  pass;
}

void Typer::Visit(node::MethodDeclaration& node) {
  if (node.type->identifier != "void") {
    AssertIsDeclaredType(node, node.type);
  }

  current_method_node =
    std::dynamic_pointer_cast<node::MethodDeclaration>(node.shared_from_this());

  std::vector<std::shared_ptr<ScopeTable>>
      table{current_class_->GetMethodScope(node.identifier)};
  iters_.push(table.cbegin());

  scopes_sizes_.push_back(0);
  for (auto&& formal: node.formals) {
    formal->Accept(*this);
  }

  method_declared_ = true;
  node.scope->Accept(*this);

  iters_.pop();
}

void Typer::Visit(node::Type&) {
  pass;
}

void Typer::Visit(node::VarDeclaration& node) {
  AssertIsDeclaredType(node, node.type);

  ++scopes_sizes_.back();
}

void Typer::Visit(node::Add& node) {
  VisitInt(node);
  node.type = int_type_;
}

void Typer::Visit(node::And& node) {
  VisitBoolean(node);
  node.type = boolean_type_;
}

void Typer::Visit(node::At& node) {
  node.array->Accept(*this);
  node.index->Accept(*this);

  AssertIsArray(node, node.array->type);
  AssertIsInt(node, node.index->type);

  node.type = std::make_shared<node::Type>(node.array->type->identifier);
}

void Typer::Visit(node::BooleanLiteral& node) {
  node.type = boolean_type_;
}

void Typer::Visit(node::Div& node) {
  VisitInt(node);
  node.type = int_type_;
}

void Typer::Visit(node::Equals& node) {
  VisitInt(node);
  node.type = boolean_type_;
}

void Typer::Visit(node::Identifier& node) {
  auto type =
      scopes_.top()->HasVariable(node.identifier, scopes_sizes_) ?
      scopes_.top()->GetNode(node.identifier, scopes_sizes_)->type :
      current_class_->GetFieldNode(node.identifier)->type;

  node.type = type;
}

void Typer::Visit(node::Length& node) {
  node.array_expression->Accept(*this);
  AssertIsArray(node, node.array_expression->type);
  node.type = int_type_;
}

void Typer::Visit(node::Less& node) {
  VisitInt(node);
  node.type = boolean_type_;
}

void Typer::Visit(node::MethodInvocation& node) {
  node.class_expression->Accept(*this);

  auto class_table_ =
      program_table_->GetClass(node.class_expression->type->identifier);

  if (!class_table_->HasMethod(node.method_identifier)) {
    throw MakeLocalizedError(node,
                             "calling undefined method: " +
                             node.method_identifier);
  }

  auto method = class_table_->GetMethodNode(node.method_identifier);

  if (method->formals.size() != node.arguments.size()) {
    throw MakeLocalizedError(node,
                             "invalid argument count in calling " +
                             method->identifier + " method, expected " +
                             std::to_string(method->formals.size()) +
                             ", got " + std::to_string(node.arguments.size()));
  }

  for (size_t i = 0; i < method->formals.size(); ++i) {
    node.arguments[i]->Accept(*this);
    AssertIsEqualTypes(*node.arguments[i], node.arguments[i]->type, method->formals[i]->type);
  }

  node.type = method->type;
}

void Typer::Visit(node::More& node) {
  VisitInt(node);
  node.type = boolean_type_;
}

void Typer::Visit(node::Mul& node) {
  VisitInt(node);
  node.type = int_type_;
}

void Typer::Visit(node::New& node) {
  AssertIsDeclaredType(node, node.type);
}

void Typer::Visit(node::NewArray& node) {
  node.size_expression->Accept(*this);
  AssertIsDeclaredType(node, node.type);
}

void Typer::Visit(node::Not& node) {
  AssertIsBoolean(node, node.argument->type);
  node.type = boolean_type_;
}

void Typer::Visit(node::Number& node) {
  node.type = int_type_;
}

void Typer::Visit(node::Or& node) {
  VisitBoolean(node);
  node.type = boolean_type_;
}

void Typer::Visit(node::Percent& node) {
  VisitInt(node);
  node.type = int_type_;
}

void Typer::Visit(node::Subtract& node) {
  VisitInt(node);
  node.type = int_type_;
}

void Typer::Visit(node::This& node) {
  node.type = std::make_shared<node::Type>(current_class_node_->identifier);
}

void Typer::Visit(node::Assert& node) {
  node.condition->Accept(*this);
}

void Typer::Visit(node::Assign& node) {
  node.expression->Accept(*this);
  node.lvalue->Accept(*this);
  auto lvalue_type =
      scopes_.top()->HasVariable(node.lvalue->identifier, scopes_sizes_) ?
      scopes_.top()->GetNode(node.lvalue->identifier, scopes_sizes_)->type :
      current_class_->GetFieldNode(node.lvalue->identifier)->type;


  if (node.lvalue->index_expression != nullptr) {
    if (!lvalue_type->is_array) {
      throw MakeLocalizedError(node, "assignment to the element of not array");
    }
    lvalue_type->is_array = false;
    AssertIsEqualTypes(node, lvalue_type, node.expression->type);
    lvalue_type->is_array = true;
  } else {
    AssertIsEqualTypes(node, lvalue_type, node.expression->type);
  }

}

void Typer::Visit(node::If& node) {
  node.condition->Accept(*this);
  AssertIsBoolean(node, node.condition->type);
  node.then_statement->Accept(*this);
  node.else_statement->Accept(*this);
}

void Typer::Visit(node::Lvalue& node) {
  if (node.index_expression) {
    node.index_expression->Accept(*this);
    AssertIsInt(node, node.index_expression->type);
  }
}

void Typer::Visit(node::Print& node) {
  node.print_expression->Accept(*this);
  AssertIsInt(node, node.print_expression->type);
}

void Typer::Visit(node::Return& node) {
  node.return_expression->Accept(*this);
  AssertIsEqualTypes(node, current_method_node->type, node.return_expression->type);
}

void Typer::Visit(node::Scope& node) {
  scopes_.push(*iters_.top()++);
  iters_.push(scopes_.top()->GetNext().cbegin());

  if (!method_declared_) {
    scopes_sizes_.push_back(0);
  }
  method_declared_ = false;


  for (auto&& stmt: node.statements) {
    stmt->Accept(*this);
  }

  scopes_sizes_.pop_back();
  iters_.pop();
  scopes_.pop();
}

void Typer::Visit(node::While& node) {
  node.condition->Accept(*this);
  AssertIsBoolean(node, node.condition->type);
  node.then_statement->Accept(*this);
}

void Typer::Visit(node::Program& node) {
  for (auto&& class_v: node.classes) {
    class_v->Accept(*this);
  }
}

void Typer::VisitInt(node::BinaryOp& node) {
  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  AssertIsInt(node, node.lhvalue->type);
  AssertIsInt(node, node.rhvalue->type);
}

void Typer::VisitBoolean(node::BinaryOp& node) {
  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  AssertIsBoolean(node, node.lhvalue->type);
  AssertIsBoolean(node, node.rhvalue->type);
}

bool Typer::IsEqualTypes(const std::shared_ptr<node::Type>& lhvalue,
                         const std::shared_ptr<node::Type>& rhvalue) const {
  return (lhvalue->identifier == rhvalue->identifier) &&
         (lhvalue->is_array   == rhvalue->is_array);
}

bool Typer::IsPrimitive(const std::shared_ptr<node::Type>& type) const {
  return IsInt(type) || IsBoolean(type);
}

bool Typer::IsInt(const std::shared_ptr<node::Type>& type) const {
  return type->identifier == "int";
}

bool Typer::IsBoolean(const std::shared_ptr<node::Type>& type) const {
  return type->identifier == "boolean";
}

bool Typer::IsDeclaredType(const std::shared_ptr<node::Type>& type) const {
  return IsPrimitive(type) || program_table_->HasClass(type->identifier);
}

std::string Typer::DumpType(const std::shared_ptr<node::Type>& type) {
  return type->identifier + (type->is_array ? "[]" : "");
}

void Typer::AssertIsEqualTypes(node::Node& node,
                               const std::shared_ptr<node::Type>& lhvalue,
                               const std::shared_ptr<node::Type>& rhvalue) const {
  if (!IsEqualTypes(lhvalue, rhvalue)) {
    throw MakeLocalizedError(node,
        "inequal types: " + DumpType(lhvalue) + " and " + DumpType(rhvalue));
  }
}

void Typer::AssertIsArray(node::Node& node,
                          const std::shared_ptr<node::Type>& type) const {
  if (!type->is_array) {
    throw MakeLocalizedError(node, "expected array type");
  }
}

void Typer::AssertIsInt(node::Node& node,
                        const std::shared_ptr<node::Type>& type) const {
  if (!IsInt(type)) {
    throw MakeLocalizedError(node,
                             "invalid type:" +
                             DumpType(type) +
                             ", expected int");
  }
}

void Typer::AssertIsBoolean(node::Node& node,
                            const std::shared_ptr<node::Type>& type) const {
  if (!IsBoolean(type)) {
    throw MakeLocalizedError(node,
                             "invalid type:" +
                             DumpType(type) +
                             ", expected boolean");
  }
}

void Typer::AssertIsDeclaredType(node::Node& node,
                                 const std::shared_ptr<node::Type>& type) const {
  if (!IsDeclaredType(type)) {
    throw MakeLocalizedError(node, "undeclared type: " + DumpType(type));
  }
}
