#pragma once

#include "../visitors/Visitor.h"
#include <memory>

namespace IRT {

class BaseElement : public std::enable_shared_from_this<BaseElement> {
 public:
  virtual ~BaseElement() = default;
  virtual void Accept(Visitor& visitor) = 0;
};
}
