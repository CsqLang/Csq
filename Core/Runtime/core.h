#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

int line_ = 1;

#include "object.h"
#include "memory.h"
#include "function.h"
#include "eval.h"
#include "class.h"
#include <unordered_map>

map<string, Cell*> SymTable;

inline int inTable(const string& name) {
    return SymTable.find(name) != SymTable.end();
}

inline Cell id(const string& identifier) {
    auto it = SymTable.find(identifier);
    if (it != SymTable.end()) {
        return *(it->second);
    }
    // Handle the case when the identifier is not found
    return f_val(0); // Provide an appropriate default value
}

inline void allocateVar(const string& id_, const Cell& c) {
    memory.emplace_back(c);
    SymTable[id_] = &memory[memory.size() - 1];
}
inline void assignVar(const string& id_, const Cell& c) {
    auto it = SymTable.find(id_);
    *(it->second) = c;
}

map<string, Class> __classes__;

#endif // RUNTIME_CORE_CSQ
