#pragma once

#include "Visitor.h"
#include "SymbolTables/ProgramTable.h"


#include <memory>
#include <stack>

void SetTypes(std::shared_ptr<node::Program>& program,
              std::shared_ptr<ProgramTable> program_table);

class Typer : Visitor {
 public:
  Typer(std::shared_ptr<ProgramTable> program_table);
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
  void VisitInt(node::BinaryOp&);
  void VisitBoolean(node::BinaryOp&);

  bool IsEqualTypes(const std::shared_ptr<node::Type>& lhvalue,
                    const std::shared_ptr<node::Type>& rhvalue) const;

  bool IsPrimitive(const std::shared_ptr<node::Type>& type) const;
  bool IsInt(const std::shared_ptr<node::Type>& type) const;
  bool IsBoolean(const std::shared_ptr<node::Type>& type) const;
  bool IsDeclaredType(const std::shared_ptr<node::Type>& type) const;

  void AssertIsEqualTypes(const std::shared_ptr<node::Type>& lhvalue,
                          const std::shared_ptr<node::Type>& rhvalue) const;
  void AssertIsArray(const std::shared_ptr<node::Type>& type) const;
  void AssertIsInt(const std::shared_ptr<node::Type>& type) const;
  void AssertIsBoolean(const std::shared_ptr<node::Type>& type) const;
  void AssertIsDeclaredType(const std::shared_ptr<node::Type>& type) const;

  std::shared_ptr<ProgramTable> program_table_;
  std::shared_ptr<ClassTable> current_class_;
  std::shared_ptr<node::Class> current_class_node_;
  std::shared_ptr<node::MethodDeclaration> current_method_node;
  std::stack<std::shared_ptr<ScopeTable>> scopes_;
  std::vector<size_t> scopes_sizes_;
  std::stack<std::vector<std::shared_ptr<ScopeTable>>::const_iterator> iters_;

  bool method_declared_ = false;

  std::shared_ptr<node::Type> int_type_ =
      std::make_shared<node::Type>("int", false);

  std::shared_ptr<node::Type> boolean_type_ =
      std::make_shared<node::Type>("boolean", false);
};