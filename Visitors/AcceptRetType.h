#pragma once
#include <Nodes/Nodes.h>

template <class T>
class AcceptRetType : public Visitor {
  public:
    T Accept(node::Node& element);
  protected:
    T tos_value_;
};

template <class T>
T AcceptRetType<T>::Accept(node::Node& node) {
    node.Accept(*this);
    return tos_value_;
}

