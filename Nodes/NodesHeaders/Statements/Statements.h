//#pragma once
//
//#include <Nodes/NodesHeaders/Node.h>
//#include "Statement.h"
//
//#include <vector>
//
//namespace node {
//
//struct Statements : Statement {
//  std::vector<std::shared_ptr<Statement>> statements;
//
//  Statements() = default;
//  Statements(std::vector<std::shared_ptr<Statement>> statements);
//  void Accept(Visitor& visitor) override;
//};
//
//} // namespace node