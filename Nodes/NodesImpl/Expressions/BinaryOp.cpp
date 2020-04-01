#include <Nodes/NodesHeaders/Expressions/BinaryOp.h>

namespace node {

BinaryOp::BinaryOp(std::shared_ptr<node::Expression> lhvalue,
                         std::shared_ptr<node::Expression> rhvalue)
: lhvalue(std::move(lhvalue))
, rhvalue(std::move(rhvalue))
{}

} // namespace node
