#pragma once

#include "ScopeTable.h"

class ClassTable {
 public:
  size_t GetFieldOffset(const std::string& symbol) const;

  std::shared_ptr<node::VarDeclaration>
  GetFieldNode(const std::string& symbol) const;

  bool HasField(const std::string& symbol) const;


  std::shared_ptr<ScopeTable> GetMethodScope(const std::string& symbol) const;

  std::shared_ptr<node::MethodDeclaration>
  GetMethodNode(const std::string& symbol) const;

  bool HasMethod(const std::string& symbol) const;

  size_t Size() const;

  size_t SizeOf() const;

 private:
  friend class SymbolTableBuilder;
  void PutField(const std::string& symbol,
                std::shared_ptr<node::VarDeclaration> field,
                size_t offset);

  void PutMethod(const std::string& symbol,
                 std::shared_ptr<node::MethodDeclaration> method,
                 std::shared_ptr<ScopeTable> scope);
  std::unordered_map<std::string, size_t> field_offsets_;
  std::unordered_map<std::string, std::shared_ptr<node::VarDeclaration>> fields_;
  std::unordered_map<std::string, std::shared_ptr<ScopeTable>> methods_tables_;
  std::unordered_map<std::string, std::shared_ptr<node::MethodDeclaration>> methods_;
};