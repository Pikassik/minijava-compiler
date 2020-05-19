/*
 * This Symbol table counts offsets as if we allocates
 * all local variables on the start of method. In SymbolTableBuilder i
 * builded offsets as if local variables are deallocated in the
 * end of the each scope. SymbolTableBuilder should be deleted then
 * but now some code depends on it.
 */

#pragma once

#include <Visitors/Visitor.h>
#include "SymbolTables/ProgramTable.h"
#include "SymbolTables/ScopeTable.h"
#include "SymbolTables/ClassTable.h"

#include <stack>

std::shared_ptr<ProgramTable> MakeTrueProgramTable(node::Program& node);

class TrueSymbolTableBuilder : public  Visitor {
 public:
  void Visit(node::Node&) override;
  void Visit(node::Class&) override;
  void Visit(node::Formal&) override;
  void Visit(node::MethodDeclaration&) override;
  void Visit(node::Type&) override;
  void Visit(node::VarDeclaration&) override;
  void Visit(node::Add&) override;
  void Visit(node::And&) override;
  void Visit(node::At&) override;
  void Visit(node::BooleanLiteral&) override;
  void Visit(node::Div&) override;
  void Visit(node::Equals&) override;
  void Visit(node::Identifier&) override;
  void Visit(node::Length&) override;
  void Visit(node::Less&) override;
  void Visit(node::MethodInvocation&) override;
  void Visit(node::More&) override;
  void Visit(node::Mul&) override;
  void Visit(node::New&) override;
  void Visit(node::NewArray&) override;
  void Visit(node::Not&) override;
  void Visit(node::Number&) override;
  void Visit(node::Or&) override;
  void Visit(node::Percent&) override;
  void Visit(node::Subtract&) override;
  void Visit(node::This&) override;
  void Visit(node::Assert&) override;
  void Visit(node::Assign&) override;
  void Visit(node::If&) override;
  void Visit(node::Lvalue&) override;
  void Visit(node::Print&) override;
  void Visit(node::Return&) override;
  void Visit(node::Scope&) override;
  void Visit(node::While&) override;
  void Visit(node::Program&) override;
 private:
  friend std::shared_ptr<ProgramTable> MakeTrueProgramTable(node::Program& node);

  void Visit(node::BinaryOp&);

  bool method_declared_ = false;

  size_t current_method_sp_ = 0; //sp is stack pointer

  std::shared_ptr<ProgramTable> program_table_;
  std::shared_ptr<ClassTable> current_class_;
  std::stack<std::shared_ptr<ScopeTable>> scopes_;
};

