#include "../Typer.h"

#include <Nodes/Nodes.h>

#define pass throw std::runtime_error("impossible state")

void Typer::Visit(node::Node&) {
  pass;
}

void Typer::Visit(node::Class& node) {

}

void Typer::Visit(node::Formal&) {
  pass;
}

void Typer::Visit(node::MethodDeclaration&) {

}

void Typer::Visit(node::Type&) {

}

void Typer::Visit(node::VarDeclaration&) {

}

void Typer::Visit(node::Add&) {

}

void Typer::Visit(node::And&) {

}

void Typer::Visit(node::At&) {

}

void Typer::Visit(node::BooleanLiteral&) {

}

void Typer::Visit(node::Div&) {

}

void Typer::Visit(node::Equals&) {

}

void Typer::Visit(node::Identifier&) {

}

void Typer::Visit(node::Length&) {

}

void Typer::Visit(node::Less&) {

}

void Typer::Visit(node::MethodInvocation&) {

}

void Typer::Visit(node::More&) {

}

void Typer::Visit(node::Mul&) {

}

void Typer::Visit(node::New&) {

}

void Typer::Visit(node::NewArray&) {

}

void Typer::Visit(node::Not&) {

}

void Typer::Visit(node::Number&) {

}

void Typer::Visit(node::Or&) {

}

void Typer::Visit(node::Percent&) {

}

void Typer::Visit(node::Subtract&) {

}

void Typer::Visit(node::This&) {

}

void Typer::Visit(node::Assert&) {

}

void Typer::Visit(node::Assign&) {

}

void Typer::Visit(node::If&) {

}

void Typer::Visit(node::Lvalue&) {

}

void Typer::Visit(node::Print&) {

}

void Typer::Visit(node::Return&) {

}

void Typer::Visit(node::Scope&) {

}

void Typer::Visit(node::While&) {

}

void Typer::Visit(node::Program& node) {
  for (auto&& class_v: node.classes) {
    current_class_ = program_table_->GetClass(class_v->identifier);
    
  }
}
