#include "SymbolTables/ClassTable.h"

size_t ClassTable::GetFieldOffset(const std::string& symbol) const {
  return field_offsets_.at(symbol);
}

std::shared_ptr<node::VarDeclaration>
ClassTable::GetFieldNode(const std::string& symbol) const {
  return fields_.at(symbol);
}

bool ClassTable::HasField(const std::string& symbol) const {
  return fields_.find(symbol) != fields_.end();
}

std::shared_ptr<ScopeTable>
ClassTable::GetMethodScope(const std::string& symbol) const {
  return methods_tables_.at(symbol);
}

std::shared_ptr<node::MethodDeclaration>
ClassTable::GetMethodNode(const std::string& symbol) const {
  return methods_.at(symbol);
}

bool ClassTable::HasMethod(const std::string& symbol) const {
  return methods_.find(symbol) != methods_.end();
}

void ClassTable::PutField(const std::string& symbol,
                          std::shared_ptr<node::VarDeclaration> field,
                          size_t offset) {
  fields_[symbol] = std::move(field);
}

void ClassTable::PutMethod(const std::string& symbol,
                           std::shared_ptr<node::MethodDeclaration> method,
                           std::shared_ptr<ScopeTable> scope) {
  methods_[symbol] = std::move(method);
  methods_tables_[symbol] = std::move(scope);
}
