#pragma once

#include "../address/Address.h"
#include <SymbolTables/ClassTable.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <stack>
#include <vector>

namespace IRT {

class FrameTranslator {
 public:
  FrameTranslator(std::shared_ptr<ClassTable> class_table,
                  const std::string& method_name);

  void SetupScope();
  void TearDownScope();

  void AddArgumentAddress(const std::string& name);

  std::shared_ptr<Address> GetAddress(const std::string& name);
  std::shared_ptr<Address> GetReturnAddress();
  std::shared_ptr<Address> GetFramePointer();
  std::shared_ptr<Address> GetReturnValueAddress();
  std::shared_ptr<Address> GetThis();

  class ScopeGuard {
   public:
    explicit ScopeGuard(FrameTranslator*);
    ~ScopeGuard();
   private:
    FrameTranslator* translator_;
  };

  ScopeGuard GetGuard();

 private:
  static constexpr int word_size_ = 4;
  std::shared_ptr<Address> return_address_;
  std::shared_ptr<Address> frame_pointer_;
  std::shared_ptr<Address> return_value_address_;
  std::shared_ptr<Address> this_;
  std::shared_ptr<ClassTable> class_table_;
  std::stack<std::shared_ptr<ScopeTable>> scopes_;
  std::stack<std::vector<std::shared_ptr<ScopeTable>>::const_iterator> iters_;
  std::vector<std::shared_ptr<ScopeTable>> root_dummy_;
};

}

