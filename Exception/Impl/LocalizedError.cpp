#include "../LocalizedError.h"

#include <sstream>

namespace {

std::string GetStr(std::ostream& stream) {
  return dynamic_cast<std::stringstream&>(stream).str();
}

}

std::runtime_error MakeLocalizedError(const yy::location& loc,
                                      const std::string& what_arg) {
  return std::runtime_error(
      "\n" + GetStr(std::stringstream() << loc) + ": " + what_arg);
}

std::runtime_error MakeLocalizedError(const node::Node& node,
                                      const std::string& what_arg) {
  return MakeLocalizedError(node.loc, what_arg);
}
