#pragma once

namespace node {
struct Node;

struct Class;
struct Formal;
struct MethodDeclaration;
struct Type;
struct VarDeclaration;
struct Add;
struct And;
struct At;
struct BooleanLiteral;
struct Div;
struct Equals;
struct Identifier;
struct Length;
struct Less;
struct MethodInvocation;
struct More;
struct Mul;
struct New;
struct NewArray;
struct Not;
struct Number;
struct Or;
struct Percent;
struct Subtract;
struct This;
struct Assert;
struct Assign;
struct If;
struct Lvalue;
struct Print;
struct Return;
struct Scope;
struct Statements;
struct While;
struct Program;
}

class Visitor {
 public:
  virtual ~Visitor() = default;

  virtual void Visit(node::Node&) = 0;
  virtual void Visit(node::Class&) = 0;
  virtual void Visit(node::Formal&) = 0;
  virtual void Visit(node::MethodDeclaration&) = 0;
  virtual void Visit(node::Type&) = 0;
  virtual void Visit(node::VarDeclaration&) = 0;
  virtual void Visit(node::Add&) = 0;
  virtual void Visit(node::And&) = 0;
  virtual void Visit(node::At&) = 0;
  virtual void Visit(node::BooleanLiteral&) = 0;
  virtual void Visit(node::Div&) = 0;
  virtual void Visit(node::Equals&) = 0;
  virtual void Visit(node::Identifier&) = 0;
  virtual void Visit(node::Length&) = 0;
  virtual void Visit(node::Less&) = 0;
  virtual void Visit(node::MethodInvocation&) = 0;
  virtual void Visit(node::More&) = 0;
  virtual void Visit(node::Mul&) = 0;
  virtual void Visit(node::New&) = 0;
  virtual void Visit(node::NewArray&) = 0;
  virtual void Visit(node::Not&) = 0;
  virtual void Visit(node::Number&) = 0;
  virtual void Visit(node::Or&) = 0;
  virtual void Visit(node::Percent&) = 0;
  virtual void Visit(node::Subtract&) = 0;
  virtual void Visit(node::This&) = 0;
  virtual void Visit(node::Assert&) = 0;
  virtual void Visit(node::Assign&) = 0;
  virtual void Visit(node::If&) = 0;
  virtual void Visit(node::Lvalue&) = 0;
  virtual void Visit(node::Print&) = 0;
  virtual void Visit(node::Return&) = 0;
  virtual void Visit(node::Scope&) = 0;
  virtual void Visit(node::While&) = 0;
  virtual void Visit(node::Program&) = 0;
};