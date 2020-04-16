#include <Nodes/NodesHeaders/Node.h>

namespace node {

void Node::SetLocation(const yy::location& loc_) {
  loc = loc_;
}

} // namespace node