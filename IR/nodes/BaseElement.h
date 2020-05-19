#pragma once

#include "../visitors/Visitor.h"
#include <memory>

namespace IRT {

class BaseElement {
 public:
  virtual ~BaseElement() = default;
  virtual void Accept(Visitor& visitor) = 0;
};
}
