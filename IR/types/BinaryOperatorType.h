#pragma once

#include <string>
namespace IRT {
enum class BinaryOperatorType : char {
  PLUS,
  MINUS,
  MUL,
  DIV,
  AND,
  OR,
  PERC
};

std::string ToString(BinaryOperatorType type);
}