#pragma once

#include "AcceptRetType.h"
#include <SymbolTables/ProgramTable.h>

#include <unordered_map>
#include <stack>

void Interpret(node::Program& program);

namespace interpreter {

union Value {
 public:
  int64_t int_v;
  bool    bool_v;
  Value*   ptr_v;

  Value();
  Value(int64_t int_v);
  Value(bool bool_v);
  Value(Value* ptr_v);
};

class Interpreter : public AcceptRetType<Value> {
  friend void ::Interpret(node::Program& program);
 private:
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

  template <class T>
  static bool IsNodeType(node::Node&);

  static Value* New(size_t size);

  void Push(int64_t int_v);
  void Push(bool bool_v);
  void Push(Value* ptr_v);
  void Push(Value value);

  void Pop(size_t size = 1);

  Value ret_value_;

  int64_t rsp_ = 0;
  int64_t rbp_ = 0;

  static constexpr size_t kStackSize = 1024;
  std::array<Value, kStackSize> stack_;

  std::shared_ptr<ProgramTable> program_table_;
  std::stack<std::shared_ptr<ClassTable>> classes_;
  std::stack<std::shared_ptr<ScopeTable>> scopes_;
  std::vector<size_t> scopes_sizes_;
  std::stack<std::vector<std::shared_ptr<ScopeTable>>::const_iterator> iters_;
  bool method_declared_ = false;
  bool returned_ = false;
};

} // namespace interpreter