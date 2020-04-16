#pragma once

#include <exception>

#include <Parser/location.hh>
#include <Nodes/NodesHeaders/Node.h>

std::runtime_error MakeLocalizedError(const yy::location& node, const std::string& what_arg);
std::runtime_error MakeLocalizedError(const node::Node& node, const std::string& what_arg);


/*todo: remove
class LocalizedError : public std::runtime_error {
  LocalizedError(const yy::location& loc, const std::string& what_arg);
  LocalizedError(const node::Node& node, const std::string& what_arg);

 private:
  yy::location loc_;
};
*/