#include "../Interpreter.h"
#include <Nodes/Nodes.h>

#include <iostream>

void Interpret(node::Program& program) {
  interpreter::Interpreter interpreter;
  interpreter.Visit(program);
}

namespace interpreter {

// for undefined situations
#define pass Throw("not implemented")

void Interpreter::Visit(node::Node&) {
  pass;
}

void Interpreter::Visit(node::Class& node) {
  /*
   * Only public static void main is visited
   */

   node.methods.at(0)->Accept(*this);
}

void Interpreter::Visit(node::Formal&) {
  pass;
}

void Interpreter::Visit(node::MethodDeclaration& node) {
  /*
   * Executes only public static void main
   */

  node.scope->Accept(*this);
}

void Interpreter::Visit(node::Type&) {
  // only ints
  pass;
}

void Interpreter::Visit(node::VarDeclaration& node) {
  //  only ints && arrays
  if (node.type->is_array) {
    if (HasArray(node.identifier)) {
      Throw("redefinition of array: " + node.identifier);
    }

    arrays_[node.identifier] = std::vector<int>();
  } else {
    if (HasVariable(node.identifier)) {
      Throw("redefinition of variable: " + node.identifier);
    }

    variables_[node.identifier] = 0;
  }
}

void Interpreter::Visit(node::Add& node) {
  tos_value_ = Accept(*node.lhvalue) + Accept(*node.rhvalue);
}

void Interpreter::Visit(node::And& node) {
  tos_value_ = Accept(*node.lhvalue) && Accept(*node.rhvalue);
}

void Interpreter::Visit(node::At& node) {
  Accept(*node.array);

  if (last_identifier_.empty()) {
    Throw("invalid array expression");
  }

  if (!HasArray(last_identifier_)) {
    Throw("undeclared array: " + last_identifier_);
  }

  int index = Accept(*node.index);
  if (index < 0) {
    Throw("index is out of range : " + last_identifier_ +
          "[" + std::to_string(index) + "]");
  }

  tos_value_ = arrays_[last_identifier_][index];
  last_identifier_.clear();
}

void Interpreter::Visit(node::BooleanLiteral& node) {
  tos_value_ = node.is_true;
}

void Interpreter::Visit(node::Div& node) {
  tos_value_ = Accept(*node.lhvalue) / Accept(*node.rhvalue);
}

void Interpreter::Visit(node::Equals& node) {
  tos_value_ = Accept(*node.lhvalue) == Accept(*node.rhvalue);
}

void Interpreter::Visit(node::Identifier& node) {
  if (HasVariable(node.identifier)) {
    tos_value_ = variables_.at(node.identifier);
    return;
  }

  if (!HasArray(node.identifier)) {
    Throw("undeclared identifier: " + node.identifier);
  }

  last_identifier_ = node.identifier;
}

void Interpreter::Visit(node::Length& node) {
  Accept(*node.array_expression);

  if (last_identifier_.empty()) {
    Throw("invalid array expression");
  }

  if (!HasArray(last_identifier_)) {
    Throw("undeclared array: " + last_identifier_);
  }

  tos_value_ = arrays_[last_identifier_].size();

  last_identifier_.clear();
}

void Interpreter::Visit(node::Less& node) {
  tos_value_ = Accept(*node.lhvalue) < Accept(*node.rhvalue);
}

void Interpreter::Visit(node::MethodInvocation&) {
  pass;
}

void Interpreter::Visit(node::More& node) {
  tos_value_ = Accept(*node.lhvalue) > Accept(*node.rhvalue);
}

void Interpreter::Visit(node::Mul& node) {
  tos_value_ = Accept(*node.lhvalue) * Accept(*node.rhvalue);
}

void Interpreter::Visit(node::New&) {
  pass;
}

void Interpreter::Visit(node::NewArray& node) {
  tos_value_ = Accept(*node.size_expression);
  new_array_expr = true;
}

void Interpreter::Visit(node::Not& node) {
  tos_value_ = !Accept(node);
}

void Interpreter::Visit(node::Number& node) {
  tos_value_ = node.number;
}

void Interpreter::Visit(node::Or& node) {
  tos_value_ = Accept(*node.lhvalue) || Accept(*node.rhvalue);
}

void Interpreter::Visit(node::Percent& node) {
  tos_value_ = Accept(*node.lhvalue) % Accept(*node.rhvalue);
}

void Interpreter::Visit(node::Subtract& node) {
  tos_value_ = Accept(*node.lhvalue) - Accept(*node.rhvalue);
}

void Interpreter::Visit(node::This&) {
  pass;
}

void Interpreter::Visit(node::Assert& node) {
  if (!Accept(*node.condition)) {
    Throw("assertion failed");
  }
}

void Interpreter::Visit(node::Assign& node) {
  int expr_value = Accept(*node.expression);
  if (new_array_expr) {
    if (node.lvalue->index_expression) {
      Throw("can't assign array to array element");
    }

    if (!HasArray(node.lvalue->identifier)) {
      Throw("undeclared array:" + node.lvalue->identifier);
    }

    arrays_[node.lvalue->identifier] = std::vector<int>(expr_value);

    new_array_expr = false;
    return;
  }

  if (!node.lvalue->index_expression) {
    if (!HasVariable(node.lvalue->identifier)) {
      Throw("undeclared variable: " + node.lvalue->identifier);
    }
    variables_[node.lvalue->identifier] = expr_value;
  } else {
    if (!HasArray(node.lvalue->identifier)) {
      Throw("undeclared array: " + node.lvalue->identifier);
    }

    arrays_[node.lvalue->identifier][Accept(*node.lvalue->index_expression)] =
        expr_value;
  }
}

void Interpreter::Visit(node::If& node) {
  if (Accept(*node.condition)) {
    Accept(*node.then_statement);
  } else if (node.else_statement) {
    Accept(*node.else_statement);
  }
}

void Interpreter::Visit(node::Lvalue&) {
  pass;
}

void Interpreter::Visit(node::Print& node) {
  std::cout << Accept(*node.print_expression) << std::endl;
}

void Interpreter::Visit(node::Return&) {
  pass;
}

void Interpreter::Visit(node::Scope& node) {
  for (auto&& statement: node.statements) {
    statement->Accept(*this);
  }
}

void Interpreter::Visit(node::While& node) {
  while (Accept(*node.condition)) {
    Accept(*node.then_statement);
  }
}

void Interpreter::Visit(node::Program& node) {
  /*
   * Only first class is visited
   */
   node.classes.at(0)->Accept(*this);
}

template<class T>
bool Interpreter::IsNodeType(node::Node& node) {
  auto* ptr = dynamic_cast<T*>(&node);

  return ptr != nullptr;
}

void Interpreter::Throw(const std::string& error) {
  std::cerr << error << std::endl;
  throw std::runtime_error(error);
}

bool Interpreter::HasVariable(const std::string& identifier) {
  return variables_.find(identifier) != variables_.end();
}

bool Interpreter::HasArray(const std::string& identifier) {
  return arrays_.find(identifier) != arrays_.end();
}

}