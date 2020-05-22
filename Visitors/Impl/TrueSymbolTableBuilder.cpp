#include <Visitors/TrueSymbolTableBuilder.h>

#include <Exception/LocalizedError.h>

#include <cassert>
#include <queue>

#define pass throw std::runtime_error("impossible state")

std::shared_ptr<ProgramTable> MakeTrueProgramTable(node::Program& node) {
  TrueSymbolTableBuilder builder;
  node.Accept(builder);

  return builder.program_table_;
}

void TrueSymbolTableBuilder::Visit(node::Node&) {
  pass;
}

void TrueSymbolTableBuilder::Visit(node::Class& node) {
  current_class_ = std::make_shared<ClassTable>();

  for (size_t i = 0; i < node.fields.size(); ++i) {
    const auto& id = node.fields[i]->identifier;
    if (current_class_->HasField(id)) {
      throw MakeLocalizedError(*node.fields[i], "redefinition of field: " + id);
    }
    current_class_->PutField(id, node.fields[i], i);
  }

  for (auto&& method: node.methods) {
    const auto& id = method->identifier;
    if (current_class_->HasMethod(id)) {
      throw MakeLocalizedError(*method, "redefinition of method: " + id);
    }

    method->Accept(*this);

    current_class_->PutMethod(id, method, scopes_.top());
    scopes_.pop();
  }

  program_table_->Put(node.identifier, current_class_);
}

void TrueSymbolTableBuilder::Visit(node::Formal& node) {
  pass;
}

void TrueSymbolTableBuilder::Visit(node::MethodDeclaration& node) {
  current_method_sp_ = 0;
  scopes_.push(std::make_shared<ScopeTable>(nullptr));
  scopes_.top()->PutVariable("this", nullptr, current_method_sp_++);
  for (auto&& formal: node.formals) {
    formal->Accept(*this);
  }

  method_declared_ = true;
  node.scope->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Type& node) {
  pass;
}

void TrueSymbolTableBuilder::Visit(node::VarDeclaration& node) {
  if (scopes_.top()->HasVariableOnActuallyThisLayer(node.identifier)) {
    throw MakeLocalizedError(node, "redefinition of variable: " + node.identifier);
  }

  scopes_.top()->PutVariable(
      node.identifier,
      std::dynamic_pointer_cast<node::VarDeclaration>(node.shared_from_this()),
      current_method_sp_++
  );
}

void TrueSymbolTableBuilder::Visit(node::Add& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::And& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::At& node) {
  node.array->Accept(*this);
  node.index->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::BooleanLiteral& node) {
  // pass
}

void TrueSymbolTableBuilder::Visit(node::Div& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::Equals& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::Identifier& node) {
  if (!scopes_.top()->HasVariable(node.identifier) &&
      !current_class_->HasField(node.identifier)) {
    throw MakeLocalizedError(node, "undeclared identifier: " + node.identifier);
  }
}

void TrueSymbolTableBuilder::Visit(node::Length& node) {
  node.array_expression->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Less& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::MethodInvocation& node) {
  node.class_expression->Accept(*this);

  for (auto&& arg: node.arguments) {
    arg->Accept(*this);
  }
}

void TrueSymbolTableBuilder::Visit(node::More& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::Mul& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::New& node) {
  // pass
}

void TrueSymbolTableBuilder::Visit(node::NewArray& node) {
  node.size_expression->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Not& node) {
  node.argument->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Number& node) {
  // pass
}

void TrueSymbolTableBuilder::Visit(node::Or& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::Percent& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::Subtract& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void TrueSymbolTableBuilder::Visit(node::This& node) {
  // pass
}

void TrueSymbolTableBuilder::Visit(node::Assert& node) {
  node.condition->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Assign& node) {
  node.lvalue->Accept(*this);
  node.expression->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::If& node) {
  node.condition->Accept(*this);
  node.then_statement->Accept(*this);
  if (node.else_statement) {
    node.else_statement->Accept(*this);
  }
}

void TrueSymbolTableBuilder::Visit(node::Lvalue& node) {
  if (!scopes_.top()->HasVariable(node.identifier) &&
      !current_class_->HasField(node.identifier)) {
    throw MakeLocalizedError(node, "undeclared variable: " + node.identifier);
  }

  if (node.index_expression) {
    node.index_expression->Accept(*this);
  }
}

void TrueSymbolTableBuilder::Visit(node::Print& node) {
  node.print_expression->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Return& node) {
  node.return_expression->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Scope& node) {
  if (!method_declared_) {
    auto new_scope = std::make_shared<ScopeTable>(scopes_.top());
    scopes_.top()->PutChild(new_scope);
    scopes_.emplace(std::move(new_scope));
  }

  bool was_declared = method_declared_;
  method_declared_ = false;

  for (auto&& stmt: node.statements) {
    stmt->Accept(*this);
  }

  if (!was_declared) {
    scopes_.pop();
  }
}

void TrueSymbolTableBuilder::Visit(node::While& node) {
  node.condition->Accept(*this);
  node.then_statement->Accept(*this);
}

void TrueSymbolTableBuilder::Visit(node::Program& node) {
  program_table_ = std::make_shared<ProgramTable>();
  for (auto&& class_v: node.classes) {
    if (program_table_->HasClass(class_v->identifier)) {
      throw MakeLocalizedError(*class_v, "redefinition of class: " + class_v->identifier);
    }
    class_v->Accept(*this);
  }

  assert(scopes_.empty());
}

void TrueSymbolTableBuilder::Visit(node::BinaryOp& node) {
  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);
}
