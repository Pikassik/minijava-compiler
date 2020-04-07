#include <SymbolTables/SymbolTableBuilder.h>

#include <cassert>
#include <queue>

#define pass throw std::runtime_error("impossible state")

namespace {

enum class Color {
  White = 0,       // not visited
  Grey,            // in call stack
  Black            // visited
};

void RecDfs(size_t ind,
            std::vector<size_t>& sorted,
            std::vector<enum Color>& color,
            const node::Program& program,
            const std::unordered_map<std::string_view, size_t>& indexes) {
  color[ind] = Color::Grey;

  if (!program.classes[ind]->base.empty()) {
    switch (size_t parent_ind = indexes.at(program.classes[ind]->base);
            color[parent_ind]) {
      case Color::White: {
        RecDfs(parent_ind, sorted, color, program, indexes);
        break;
      }
      case Color::Grey: {
        throw std::runtime_error("cyclic inheritance found");
      }
      case Color::Black: {
        break;
      }
      default: assert(false);
    }
  }

  color[ind] = Color::Black;
  sorted.push_back(ind);
}

void ClassInheritanceTopSort(node::Program& program) {
  std::unordered_map<std::string_view, size_t> indexes;
  for (size_t i = 0; i < program.classes.size(); ++i) {
    if (indexes.find(program.classes[i]->identifier) !=
        indexes.end()) {
      throw std::runtime_error("redefiniton of class: " +
                               program.classes[i]->identifier);
    }

    indexes[program.classes[i]->identifier] = i;
  }

  std::vector<size_t> sorted;
  sorted.reserve(program.classes.size());
  std::vector<enum Color> color(program.classes.size(), Color::White);
  RecDfs(0, sorted, color, program, indexes);

  assert(sorted.size() == program.classes.size());

  std::vector<std::shared_ptr<node::Class>> sorted_classes;
  sorted.resize(program.classes.size());


  for (size_t i = 0; i < sorted.size(); ++i) {
    sorted_classes[i] = std::move(program.classes[sorted[i]]);
  }

  program.classes = std::move(sorted_classes);
}

}

std::shared_ptr<ProgramTable> MakeProgramTable(node::Program& node) {
  ClassInheritanceTopSort(node);

  SymbolTableBuilder builder;
  node.Accept(builder);

  return builder.program_table_;
}

void SymbolTableBuilder::Visit(node::Node&) {
  pass;
}

void SymbolTableBuilder::Visit(node::Class& node) {
  current_class_ = std::make_shared<ClassTable>();

  for (size_t i = 0; i < node.fields.size(); ++i) {
    const auto& id = node.fields[i]->identifier;
    if (current_class_->HasField(id)) {
      throw std::runtime_error("redefinition of field: " + id);
    }
    current_class_->PutField(id, node.fields[i], i);
  }

  for (auto&& method: node.methods) {
    const auto& id = method->identifier;
    if (current_class_->HasMethod(id)) {
      throw std::runtime_error("redefinition of method: " + id);
    }

    method->Accept(*this);

    current_class_->PutMethod(id, method, scopes_.top());
    scopes_.pop();
    offsets_.pop();
  }
}

void SymbolTableBuilder::Visit(node::Formal& node) {
  pass;
}

void SymbolTableBuilder::Visit(node::MethodDeclaration& node) {
  offsets_.push(0);
  scopes_.push(std::make_shared<ScopeTable>(nullptr));

  for (auto&& formal: node.formals) {
    formal->Accept(*this);
  }

  method_declared_ = true;
  node.scope->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Type& node) {
  // pass
}

void SymbolTableBuilder::Visit(node::VarDeclaration& node) {
  if (scopes_.top()->HasVariableOnActuallyThisLayer(node.identifier)) {
    throw std::runtime_error("redefinition of variable: " + node.identifier);
  }

  scopes_.top()->PutVariable(
      node.identifier,
      std::dynamic_pointer_cast<node::VarDeclaration>(node.shared_from_this()),
      offsets_.top() + scopes_.top()->variables_.size()
  );
}

void SymbolTableBuilder::Visit(node::Add& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::And& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::At& node) {
  node.array->Accept(*this);
  node.index->Accept(*this);
}

void SymbolTableBuilder::Visit(node::BooleanLiteral& node) {
  // pass
}

void SymbolTableBuilder::Visit(node::Div& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::Equals& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::Identifier& node) {
  if (!scopes_.top()->HasVariable(node.identifier) &&
      !current_class_->HasField(node.identifier)) {
    throw std::runtime_error("undeclared identifier: " + node.identifier);
  }
}

void SymbolTableBuilder::Visit(node::Length& node) {
  node.array_expression->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Less& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::MethodInvocation& node) {
  node.class_expression->Accept(*this);

  for (auto&& arg: node.arguments) {
    arg->Accept(*this);
  }
}

void SymbolTableBuilder::Visit(node::More& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::Mul& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::New& node) {
  // pass
}

void SymbolTableBuilder::Visit(node::NewArray& node) {
  node.size_expression->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Not& node) {
  node.argument->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Number& node) {
  // pass
}

void SymbolTableBuilder::Visit(node::Or& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::Percent& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::Subtract& node) {
  Visit(static_cast<node::BinaryOp&>(node));
}

void SymbolTableBuilder::Visit(node::This& node) {
  // pass
}

void SymbolTableBuilder::Visit(node::Assert& node) {
  node.condition->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Assign& node) {
  node.lvalue->Accept(*this);
  node.expression->Accept(*this);
}

void SymbolTableBuilder::Visit(node::If& node) {
  node.condition->Accept(*this);
  node.then_statement->Accept(*this);
  node.else_statement->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Lvalue& node) {
  if (!scopes_.top()->HasVariable(node.identifier) &&
      !current_class_->HasField(node.identifier)) {
    throw std::runtime_error("undeclared variable: " + node.identifier);
  }

  if (node.index_expression) {
    node.index_expression->Accept(*this);
  }
}

void SymbolTableBuilder::Visit(node::Print& node) {
  node.print_expression->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Return& node) {
  node.return_expression->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Scope& node) {
  if (!method_declared_) {
    auto new_scope = std::make_shared<ScopeTable>(scopes_.top());
    scopes_.top()->PutChild(new_scope);
    offsets_.push(offsets_.top() + scopes_.top()->offsets_.size());
    scopes_.emplace(std::move(new_scope));
  }

  bool was_declared = method_declared_;
  method_declared_ = false;

  for (auto&& stmt: node.statements) {
    stmt->Accept(*this);
  }

  if (!was_declared) {
    scopes_.pop();
    offsets_.pop();
  }
}

void SymbolTableBuilder::Visit(node::While& node) {
  node.condition->Accept(*this);
  node.then_statement->Accept(*this);
}

void SymbolTableBuilder::Visit(node::Program& node) {
  program_table_ = std::make_shared<ProgramTable>();
  for (auto&& class_v: node.classes) {
    class_v->Accept(*this);
    program_table_->Put(class_v->identifier, current_class_);
  }

  assert(scopes_.empty());
  assert(offsets_.empty());
}

void SymbolTableBuilder::Visit(node::BinaryOp& node) {
  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);
}
