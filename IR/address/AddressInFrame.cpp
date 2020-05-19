#include "AddressInFrame.h"

#include "../nodes/expressions/BinopExpression.h"
#include "../nodes/expressions/ConstExpression.h"
#include "../nodes/expressions/MemExpression.h"


namespace IRT {

using std::shared_ptr;
using std::make_shared;

shared_ptr<Expression> AddressInFrame::ToExpression() {
  shared_ptr<Expression> offset_expression;
  if (offset_ != 0) {
    offset_expression = make_shared<BinopExpression>(
      BinaryOperatorType::PLUS,
      frame_address_->ToExpression(),
      make_shared<ConstExpression>(offset_)
    );
  } else {
    offset_expression = frame_address_->ToExpression();
  }
  return make_shared<MemExpression>(offset_expression);
}

AddressInFrame::AddressInFrame(
    shared_ptr<Address> frame_address, int offset
) : frame_address_(std::move(frame_address)), offset_(offset) {

}

}