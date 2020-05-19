#pragma once

#include "ClassTable.h"

class ProgramTable {
 public:

  std::shared_ptr<ClassTable> GetClass(const std::string& symbol) const;

  bool HasClass(const std::string& symbol) const;

 private:
  friend class SymbolTableBuilder;
  friend class TrueSymbolTableBuilder;
  void Put(const std::string& symbol, std::shared_ptr<ClassTable> class_v);
  std::unordered_map<std::string, std::shared_ptr<ClassTable>> classes_;
};