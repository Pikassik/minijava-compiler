#include "../Interpreter.h"
#include "../SymbolTableBuilder.h"
#include "../Typer.h"

#include <Nodes/Nodes.h>

#include <iostream>

void Interpret(node::Program& program) {
  interpreter::Interpreter interpreter;
  interpreter.program_table_ = MakeProgramTable(program);
  SetTypes(program, interpreter.program_table_);
  interpreter.Visit(program);
}

namespace interpreter {

// for undefined situationspush
#define pass throw std::runtime_error("impossible state")

void Interpreter::Visit(node::Node&) {
  pass;
}

void Interpreter::Visit(node::Class&) {
  pass;
}

void Interpreter::Visit(node::Formal&) {
  pass;
}

void Interpreter::Visit(node::MethodDeclaration& node) {
  std::vector<std::shared_ptr<ScopeTable>>
      table{classes_.top()->GetMethodScope(node. identifier)};
  iters_.push(table.cbegin());

  scopes_sizes_.push_back(node.formals.size());

  method_declared_ = true;

  node.scope->Accept(*this);

  returned_ = false;

  iters_.pop();
}

void Interpreter::Visit(node::Type&) {
  pass;
}

void Interpreter::Visit(node::VarDeclaration&) {
  Push(0l);
  ++scopes_sizes_.back();
}

void Interpreter::Visit(node::Add& node) {
  tos_value_ = Accept(*node.lhvalue).int_v + Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::And& node) {
  tos_value_ = Accept(*node.lhvalue).bool_v && Accept(*node.rhvalue).bool_v;
}

void Interpreter::Visit(node::At& node) {
  tos_value_ = (Accept(*node.array).ptr_v)[Accept(*node.index).int_v];
}

void Interpreter::Visit(node::BooleanLiteral& node) {
  tos_value_.bool_v = node.is_true;
}

void Interpreter::Visit(node::Div& node) {
  tos_value_ = Accept(*node.lhvalue).int_v / Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::Equals& node) {
  tos_value_ = Accept(*node.lhvalue).int_v == Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::Identifier& node) {
  tos_value_ =
      scopes_.top()->HasVariable(node.identifier, scopes_sizes_) ?
      stack_[rbp_ + scopes_.top()->GetOffset(node.identifier, scopes_sizes_)] :
      stack_[rbp_ - 1].ptr_v[classes_.top()->GetFieldOffset(node.identifier)];
}

void Interpreter::Visit(node::Length& node) {
  tos_value_ = (Accept(*node.array_expression).ptr_v)[-1].int_v;
}

void Interpreter::Visit(node::Less& node) {
  tos_value_ = Accept(*node.lhvalue).int_v < Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::MethodInvocation& node) {
  Push(rbp_);
  Push(Accept(*node.class_expression).ptr_v);

  int64_t new_rbp = rsp_;

  for (auto&& arg: node.arguments) {
    Push(Accept(*arg));
  }

  rbp_ = new_rbp;

  classes_.push(
      program_table_->GetClass(node.class_expression->type->identifier));

  Accept(*program_table_->
          GetClass(node.class_expression->type->identifier)->
          GetMethodNode(node.method_identifier));

  tos_value_ = ret_value_;

  classes_.pop();
  rbp_ = stack_[rbp_ - 2].int_v;
  Pop(2);

}

void Interpreter::Visit(node::More& node) {
  tos_value_ = Accept(*node.lhvalue).int_v > Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::Mul& node) {
  tos_value_ = Accept(*node.lhvalue).int_v * Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::New& node) {
  tos_value_ =
      static_cast<Value*>(
      std::calloc(program_table_->GetClass(node.type->identifier)->SizeOf(), 1));
}

void Interpreter::Visit(node::NewArray& node) {
  int64_t length = Accept(*node.size_expression).int_v;
  auto* array = New((1 + length) * sizeof(Value));
  array = array + 1;
  array[-1].int_v = length;
  tos_value_ = array;
}

void Interpreter::Visit(node::Not& node) {
  tos_value_ = !Accept(*node.argument).bool_v;
}

void Interpreter::Visit(node::Number& node) {
  tos_value_.int_v = node.number;
}

void Interpreter::Visit(node::Or& node) {
  tos_value_ = Accept(*node.lhvalue).bool_v || Accept(*node.rhvalue).bool_v;
}

void Interpreter::Visit(node::Percent& node) {
  tos_value_ = Accept(*node.lhvalue).int_v % Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::Subtract& node) {
  tos_value_ = Accept(*node.lhvalue).int_v - Accept(*node.rhvalue).int_v;
}

void Interpreter::Visit(node::This& node) {
  tos_value_ = stack_[rbp_ - 1];
}

void Interpreter::Visit(node::Assert& node) {
  if (!Accept(*node.condition).bool_v) {
    throw std::runtime_error("assertion failed");
  }
}

void Interpreter::Visit(node::Assign& node) {
  auto lvalue =
    scopes_.top()->HasVariable(node.lvalue->identifier, scopes_sizes_) ?
    &stack_[rbp_ + scopes_.top()->GetOffset(node.lvalue->identifier, scopes_sizes_)] :
    stack_[rbp_ - 1].ptr_v +
    classes_.top()->GetFieldOffset(node.lvalue->identifier);

  if (auto rhvalue = Accept(*node.expression);
      node.lvalue->index_expression) {
    lvalue->ptr_v[Accept(*node.lvalue->index_expression).int_v] = rhvalue;
  } else {
    *lvalue = rhvalue;
  }
}

void Interpreter::Visit(node::If& node) {
  if (Accept(*node.condition).bool_v) {
    Accept(*node.then_statement);
    if (node.else_statement && IsNodeType<node::Scope>(*node.else_statement)) {
      ++iters_.top();
    }
  } else if (node.else_statement) {
    if (IsNodeType<node::Scope>(*node.then_statement)) {
      ++iters_.top();
    }
    Accept(*node.else_statement);
  }
}

void Interpreter::Visit(node::Lvalue&) {
  pass;
}

void Interpreter::Visit(node::Print& node) {
  std::cout << Accept(*node.print_expression).int_v << std::endl;
}

void Interpreter::Visit(node::Return& node) {
  returned_ = true;
  ret_value_ = Accept(*node.return_expression);
}

void Interpreter::Visit(node::Scope& node) {
  scopes_.push(*iters_.top()++);
  iters_.push(scopes_.top()->GetNext().cbegin());

  if (!method_declared_) {
    scopes_sizes_.push_back(0);
  }
  method_declared_ = false;

  for (auto&& stmt: node.statements) {
    Accept(*stmt);
    if (returned_) {
      break;
    }
  }

  rsp_ -= scopes_sizes_.back();
  scopes_sizes_.pop_back();
  iters_.pop();
  scopes_.pop();
}

void Interpreter::Visit(node::While& node) {
  while (Accept(*node.condition).bool_v) {
    Accept(*node.then_statement);
    if (IsNodeType<node::Scope>(*node.then_statement)) {
      --iters_.top();
    }
  }

  if (IsNodeType<node::Scope>(*node.then_statement)) {
    ++iters_.top();
  }
}

void Interpreter::Visit(node::Program& node) {
  classes_.push(program_table_->GetClass(node.classes[0]->identifier));
  Push(0l);
  Push(New(classes_.top()->SizeOf()));
  rbp_ = 2;
  Accept(*program_table_->
          GetClass(node.classes[0]->identifier)->
          GetMethodNode("main"));
}

template<class T>
bool Interpreter::IsNodeType(node::Node& node) {
  auto* ptr = dynamic_cast<T*>(&node);

  return ptr != nullptr;
}

Value* Interpreter::New(size_t size) {
  return reinterpret_cast<Value*>(std::calloc(size, 1));
}

void Interpreter::Push(int64_t int_v) {
  stack_[rsp_++].int_v = int_v;
}

void Interpreter::Push(bool bool_v) {
  stack_[rsp_++].bool_v = bool_v;
}

void Interpreter::Push(Value* ptr_v) {
  stack_[rsp_++].ptr_v = ptr_v;
}

void Interpreter::Push(Value value) {
  stack_[rsp_++] = value;
}

void Interpreter::Pop(size_t size) {
  rsp_ -= size;
}

Value::Value()
    : int_v(0) {
}

Value::Value(int64_t int_v)
    : int_v(int_v) {
}

Value::Value(bool bool_v)
    : bool_v(bool_v) {
}

Value::Value(Value* ptr_v)
    : ptr_v(ptr_v) {
}

}