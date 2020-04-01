#include <Nodes/NodesHeaders/Program.h>

namespace node {

Program::Program(std::vector<std::shared_ptr<Class>> classes)
: classes(std::move(classes))
{}

void Program::Accept(Visitor& visitor) {
  visitor.Visit(*this);
}

} // namespace node