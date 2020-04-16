#pragma once

#include "Visitor.h"
#include <Nodes/Nodes.h>

#include <fstream>
#include <stack>
#include <memory>

class Dumper : public Visitor {
 public:
  Dumper() = delete;
  explicit Dumper(std::shared_ptr<node::Program> program,
                  std::string filename);
  void Dump();

  void Visit(node::Node&) override;

  void Visit(node::Formal&) override;
  void Visit(node::MethodDeclaration&) override;
  void Visit(node::Type&) override;
  void Visit(node::VarDeclaration&) override;
  void Visit(node::Add&) override;
  void Visit(node::At&) override;
  void Visit(node::And&) override;
  void Visit(node::BooleanLiteral&) override;
  void Visit(node::Class&) override;
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
  std::string filename_;
  std::ofstream stream_;
  std::shared_ptr<node::Program> program;

  std::stack<void*> pointers_;

  void PrintNode(void* ptr, const std::string& label);
  void PrintEdge(void* from, void* to);
};