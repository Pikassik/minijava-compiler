#pragma once

#include <Nodes/Nodes.h>
#include <string>
#include <memory>
#include <unordered_map>

class ScopeTable : public std::enable_shared_from_this<ScopeTable> {
 public:
  ScopeTable(const std::shared_ptr<const ScopeTable>& parent);

  std::shared_ptr<const ScopeTable> GetParent() const;

  const std::vector<std::shared_ptr<ScopeTable>>& GetNext() const;


  size_t GetOffset(const std::string& symbol) const;

  size_t GetOffset(const std::string& symbol,
                   const std::vector<size_t>& scopes_sizes) const;

  std::shared_ptr<node::VarDeclaration> GetNode(const std::string& symbol) const;

  std::shared_ptr<node::VarDeclaration>
  GetNode(const std::string& symbol,
          const std::vector<size_t>& scopes_sizes) const;

  bool HasVariable(const std::string& symbol) const;

  bool HasVariable(const std::string& symbol,
                   const std::vector<size_t>& scopes_sizes) const;

 public:
  friend class SymbolTableBuilder;
  friend class TrueSymbolTableBuilder;
  bool HasVariableOnActuallyThisLayer(const std::string& symbol) const;
  std::shared_ptr<const ScopeTable>
  GetLayerWithSymbol(const std::string& symbol) const;

  std::shared_ptr<const ScopeTable>
  GetLayerWithSymbol(const std::string& symbol,
                     const std::vector<size_t>& scopes_sizes) const;

  void PutChild(std::shared_ptr<ScopeTable> child);
  void PutVariable(const std::string& symbol,
                   std::shared_ptr<node::VarDeclaration> variable,
                   size_t offset);

  std::weak_ptr<const ScopeTable> parent_;
  std::vector<std::shared_ptr<ScopeTable>> children_;
  std::unordered_map<std::string, size_t> variable_num_;
  std::unordered_map<std::string, size_t> offsets_;
  std::unordered_map<std::string, std::shared_ptr<node::VarDeclaration>> variables_;
};