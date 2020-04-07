#include <Visitors/SymbolTables/ProgramTable.h>

std::shared_ptr<ClassTable>
ProgramTable::GetClass(const std::string& symbol) const {
  return classes_.at(symbol);
}

bool ProgramTable::HasClass(const std::string& symbol) const {
  return classes_.find(symbol) != classes_.end();
}

void ProgramTable::Put(const std::string& symbol,
                       std::shared_ptr<ClassTable> class_v) {
  classes_[symbol] = std::move(class_v);
}
