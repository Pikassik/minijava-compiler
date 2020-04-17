#pragma once

#include <exception>

#include <Parser/location.hh>
#include <Nodes/NodesHeaders/Node.h>

std::runtime_error MakeLocalizedError(const yy::location& node,
                                      const std::string& what_arg);
std::runtime_error MakeLocalizedError(const node::Node& node,
                                      const std::string& what_arg);
