#include <Visitors/Dumper.h>

#include <iostream>
#include <exception>


Dumper::Dumper(std::shared_ptr<node::Program> program,
               std::string filename)
: program(std::move(program))
, filename_(std::move(filename))
, stream_(filename_) {
  if (!stream_.is_open()) {
    throw std::invalid_argument("Unable to open file");
  }
}

void Dumper::Dump() {
  stream_ << "digraph program {\n";
  stream_ <<
    "graph [nodesep=0.5];\n"
    "node [fontname=\"Helvetica\", color=\"Lavender\", style=\"filled\"];";

  PrintNode(nullptr, "root");
  pointers_.push(nullptr);

  Visit(*program);

  pointers_.pop();

  stream_ << "}\n";

  stream_.close();
}

void Dumper::Visit(node::Node&) {}

void Dumper::Visit(node::Class& node) {
  PrintNode(&node, "{class} " +
                   node.identifier +
                   ((node.base != "") ? " extends " + node.base : ""));
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  for (auto&& method: node.methods) {
    method->Accept(*this);
  }

  for (auto&& field: node.fields) {
    field->Accept(*this);
  }

  pointers_.pop();
}

void Dumper::Visit(node::Formal& node) {
  PrintNode(&node, "{formal} " + node.identifier);
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.type->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::MethodDeclaration& node) {
  PrintNode(&node, "{method decl} " + node.identifier);
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.type->Accept(*this);
  for (auto&& formal: node.formals) {
    formal->Accept(*this);
  }

  node.scope->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Type& node) {
  PrintNode(&node, "{type} " + node.identifier);
  PrintEdge(pointers_.top(), &node);
}

void Dumper::Visit(node::VarDeclaration& node) {
  PrintNode(&node, "{var decl} " + node.identifier);
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.type->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Add& node) {
  PrintNode(&node, "+");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::At& node) {
  PrintNode(&node, "[]");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.array->Accept(*this);
  node.index->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Div& node) {
  PrintNode(&node, "/");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Equals& node) {
  PrintNode(&node, "==");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Identifier& node) {
  PrintNode(&node, "{id} " + node.identifier);
  PrintEdge(pointers_.top(), &node);
}

void Dumper::Visit(node::Length& node) {
  PrintNode(&node, "length");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.array_expression->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Less& node) {
  PrintNode(&node, "<");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::MethodInvocation& node) {
  PrintNode(&node, "{method invocation} " + node.method_identifier);
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.class_expression->Accept(*this);

  for (auto&& arg: node.arguments) {
    arg->Accept(*this);
  }

  pointers_.pop();
}

void Dumper::Visit(node::More& node) {
  PrintNode(&node, ">");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Mul& node) {
  PrintNode(&node, "*");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::New& node) {
  PrintNode(&node, "new ()");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.type->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::NewArray& node) {
  PrintNode(&node, "new []");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.type->Accept(*this);
  node.size_expression->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Not& node) {
  PrintNode(&node, "!");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.argument->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Number& node) {
  PrintNode(&node, "{number} " + std::to_string(node.number));
  PrintEdge(pointers_.top(), &node);
}

void Dumper::Visit(node::Percent& node) {
  PrintNode(&node, "%");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Subtract& node) {
  PrintNode(&node, "-");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::This& node) {
  PrintNode(&node, "this");
  PrintEdge(pointers_.top(), &node);
}

void Dumper::Visit(node::Assert& node) {
  PrintNode(&node, "assert");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.condition->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Assign& node) {
  PrintNode(&node, "=");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lvalue->Accept(*this);
  node.expression->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::If& node) {
  PrintNode(&node, "if");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.condition->Accept(*this);
  node.then_statement->Accept(*this);

  if (node.else_statement) {
    node.else_statement->Accept(*this);
  }

  pointers_.pop();
}

void Dumper::Visit(node::Lvalue& node) {
  PrintNode(&node, "{lvalue} " + node.identifier);
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  if (node.index_expression) {
    node.index_expression->Accept(*this);
  }

  pointers_.pop();
}

void Dumper::Visit(node::Print& node) {
  PrintNode(&node, "print");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.print_expression->Accept(*this);

  pointers_.pop();
}
void Dumper::Visit(node::Return& node) {
  PrintNode(&node, "return");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.return_expression->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Scope& node) {
  PrintNode(&node, "scope");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  for (auto&& statement: node.statements) {
    statement->Accept(*this);
  }

  pointers_.pop();
}



void Dumper::Visit(node::While& node) {
  PrintNode(&node, "while");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.condition->Accept(*this);
  node.then_statement->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Program& node) {
  PrintNode(&node, "program");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  for (auto&& class_node: node.classes) {
    class_node->Accept(*this);
  }

  pointers_.pop();
}

void Dumper::PrintNode(void* ptr, const std::string& label) {
  stream_ << "node" << ptr << " [label=\""  << label << "\"];\n";
}

void Dumper::PrintEdge(void* from, void* to) {
  stream_ << "node" << from << " -> node" << to << '\n';
}
void Dumper::Visit(node::And& node) {
  PrintNode(&node, "&&");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::Or& node) {
  PrintNode(&node, "||");
  PrintEdge(pointers_.top(), &node);

  pointers_.push(&node);

  node.lhvalue->Accept(*this);
  node.rhvalue->Accept(*this);

  pointers_.pop();
}

void Dumper::Visit(node::BooleanLiteral& node) {
  PrintNode(&node, node.is_true ? "true" : "false");
  PrintEdge(pointers_.top(), &node);
}
