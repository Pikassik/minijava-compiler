#pragma once

#include "Visitor.h"
#include "TrueSymbolTableBuilder.h"
#include "AcceptRetType.h"
#include <SymbolTables/ProgramTable.h>
#include <IR/include.h>

#include <memory>


std::unordered_map<std::string, std::shared_ptr<IRT::Statement>>
BuildIRT(std::shared_ptr<ProgramTable>  program_table_,
         std::shared_ptr<node::Program> program);

class IRTBuilder : public AcceptRetType<std::shared_ptr<IRT::SubtreeWrapper>> {
 public:
  IRTBuilder(std::shared_ptr<ProgramTable> program_table);
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
  friend
  std::unordered_map<std::string, std::shared_ptr<IRT::Statement>>
  BuildIRT(std::shared_ptr<ProgramTable> program_table_,
           std::shared_ptr<node::Program> program);

  void Visit(node::BinaryOp& node, IRT::BinaryOperatorType type);
  void Visit(node::BinaryOp& node, IRT::LogicOperatorType type);

  std::shared_ptr<ProgramTable> program_table_;
  std::shared_ptr<ClassTable> current_class_;
  std::shared_ptr<node::Class> current_class_node_;
  std::shared_ptr<node::MethodDeclaration> current_method_node_;
  std::shared_ptr<IRT::FrameTranslator> current_frame_;

  std::unordered_map<std::string, std::shared_ptr<IRT::Statement>> method_trees_;
};