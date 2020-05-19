#include "../address/AddressInRegister.h"
#include "../address/AddressInFrame.h"
#include "FrameTranslator.h"
#include "../generators/Temporary.h"
//#include "../../SymbolTables/ClassTable.h"

namespace IRT {

using std::shared_ptr;
using std::make_shared;

const std::string kReturnAddress = "::return";
const std::string kFramePointerAddress = "::fp";
const std::string kReturnValueAddress = "::return_value";
const std::string kThis = "::this";

FrameTranslator::FrameTranslator(shared_ptr<ClassTable> class_table, const std::string& method_name)
    : class_table_(std::move(class_table))
    , return_address_(make_shared<AddressInRegister>(Temporary(kReturnValueAddress)))
    , frame_pointer_(make_shared<AddressInRegister>(Temporary(kFramePointerAddress)))
    , return_value_address_(make_shared<AddressInRegister>(Temporary(kReturnValueAddress)))
    , this_(make_shared<AddressInRegister>(Temporary(kThis)))
    {
  root_dummy_ = {class_table_->GetMethodScope(method_name)};
  iters_.push(root_dummy_.cbegin());
}

void FrameTranslator::SetupScope() {
  scopes_.push(*iters_.top()++);
  iters_.push(scopes_.top()->GetNext().cbegin());
}

void FrameTranslator::TearDownScope() {
  iters_.pop();
  scopes_.pop();
}

std::shared_ptr<Address> FrameTranslator::GetAddress(const std::string &name) {
  if (scopes_.top()->HasVariable(name)) {
    return make_shared<AddressInFrame>(frame_pointer_, scopes_.top()->GetOffset(name) * word_size_);
  } else {
    return make_shared<AddressInFrame>(this_, class_table_->GetFieldOffset(name) * word_size_);
  }
}

FrameTranslator::ScopeGuard FrameTranslator::GetGuard() {
  return FrameTranslator::ScopeGuard(this);
}

std::shared_ptr<Address> FrameTranslator::GetReturnValueAddress() {
  return return_value_address_;
}

std::shared_ptr<Address> FrameTranslator::GetReturnAddress() {
  return return_address_;
}

std::shared_ptr<Address> FrameTranslator::GetFramePointer() {
  return frame_pointer_;
}

std::shared_ptr<Address> FrameTranslator::GetThis() {
  return this_;
}

FrameTranslator::ScopeGuard::ScopeGuard(FrameTranslator* tr) : translator_(tr) {
  translator_->SetupScope();
}

FrameTranslator::ScopeGuard::~ScopeGuard() {
  translator_->TearDownScope();
}

}