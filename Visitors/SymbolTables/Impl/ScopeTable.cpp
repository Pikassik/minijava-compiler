#include "../ScopeTable.h"

#include <cassert>

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

size_t ScopeTable::GetOffset(const std::string& symbol,
                             const std::vector<size_t>& scopes_sizes) const {
  if (auto layer = GetLayerWithSymbol(symbol, scopes_sizes); layer) {
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

std::shared_ptr<node::VarDeclaration>
ScopeTable::GetNode(const std::string& symbol,
                    const std::vector<size_t>& scopes_sizes) const {
  if (auto layer = GetLayerWithSymbol(symbol, scopes_sizes); layer) {
    return layer->variables_.at(symbol);
  }

  return nullptr;
}

bool ScopeTable::HasVariable(const std::string& symbol) const {
  return GetLayerWithSymbol(symbol) != nullptr;
}

bool ScopeTable::HasVariable(const std::string& symbol,
                             const std::vector<size_t>& scopes_sizes) const {
  return GetLayerWithSymbol(symbol, scopes_sizes) != nullptr;
}

void ScopeTable::PutChild(std::shared_ptr<ScopeTable> child) {
  children_.emplace_back(std::move(child));
}

void ScopeTable::PutVariable(const std::string& symbol,
                             std::shared_ptr<node::VarDeclaration> variable,
                             size_t offset) {
  variables_[symbol] = std::move(variable);
  offsets_[symbol] = offset;
  variable_num_[symbol] = variable_num_.size();
}

bool ScopeTable::HasVariableOnActuallyThisLayer(const std::string& symbol) const {
  return variables_.find(symbol) != variables_.end();
}

std::shared_ptr<const ScopeTable>
ScopeTable::GetLayerWithSymbol(const std::string& symbol) const {
  auto current_layer = shared_from_this();

  do {
    if (current_layer->HasVariableOnActuallyThisLayer(symbol)) {
      return current_layer;
    }
    
    current_layer = current_layer->GetParent();
  } while (current_layer);

  return current_layer;
}

std::shared_ptr<const ScopeTable>
ScopeTable::GetLayerWithSymbol(const std::string& symbol,
                               const std::vector<size_t>& scopes_sizes) const {
  auto current_layer = shared_from_this();
  size_t index = scopes_sizes.size() - 1;

  do {
    assert(index >= 0);

    if (current_layer->HasVariableOnActuallyThisLayer(symbol) &&
        variable_num_.at(symbol) < scopes_sizes[index]) {
      return current_layer;
    }

    current_layer = current_layer->GetParent();
    --index;
  } while (current_layer);

  return current_layer;
}
