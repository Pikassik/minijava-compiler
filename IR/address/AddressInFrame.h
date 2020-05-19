#pragma once

#include "Address.h"
namespace IRT {

class AddressInFrame: public Address {
 public:
  AddressInFrame(
    std::shared_ptr<Address> frame_address,
    int offset
  );
  ~AddressInFrame() = default;
  std::shared_ptr<Expression> ToExpression() override;
 private:
  std::shared_ptr<Address> frame_address_;
  int offset_;
};

}
