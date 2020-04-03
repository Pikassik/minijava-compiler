#include "../ScopeTable.h"

ScopeTable::ScopeTable(const std::shared_ptr<const ScopeTable>& parent)
    : parent_ (parent) {}

std::shared_ptr<const ScopeTable> ScopeTable::GetParent() const {
  return parent_.lock();
}

const std::vector<std::shared_ptr<ScopeTable>> ScopeTable::GetNext() const {
  return children_;
}

size_t ScopeTable::GetOffset(const std::string& symbol) const {
  if (auto layer = GetLayerWithSymbol(symbol); layer) {
    return layer->offsets_.at(symbol);
  }

  return SIZE_MAX;
}

std::shared_ptr<node::VarDeclaration>
ScopeTable::GetNode(const std::string& symbol) const {
  if (auto layer = GetLayerWithSymbol(symbol); layer) {
    return layer->variables_.at(symbol);
  }

  return nullptr;
}

bool ScopeTable::HasVariable(const std::string& symbol) const {
  return GetLayerWithSymbol(symbol) != nullptr;
}

void ScopeTable::PutChild(std::shared_ptr<ScopeTable> child) {
  children_.emplace_back(std::move(child));
}

void ScopeTable::PutVariable(const std::string& symbol,
                             std::shared_ptr<node::VarDeclaration> variable,
                             size_t offset) {
  variables_[symbol] = std::move(variable);
  offsets_[symbol] = offset;
}

bool ScopeTable::HasVariableOnActuallyThisLayer(const std::string& symbol) const {
  return variables_.find(symbol) != variables_.end();
}

std::shared_ptr<const ScopeTable>
ScopeTable::GetLayerWithSymbol(const std::string& symbol) const {
  std::shared_ptr current_layer = shared_from_this();

  do {
    if (current_layer->HasVariableOnActuallyThisLayer(symbol)) {
      return current_layer;
    }
    
    current_layer = current_layer->parent_.lock();
  } while (current_layer);

  return current_layer;
}
