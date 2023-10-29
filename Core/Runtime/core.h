#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

int line_ = 1;

#include "object.h"
#include "memory.h"
#include "function.h"
#include "eval.h"
#include "class.h"

map<string, int> SymTable;
map<string, Class> __classes__;

inline bool inTable(const std::string& name) {
    return SymTable.find(name) != SymTable.end();
}

inline const Cell& id(const std::string& identifier) {
    auto it = SymTable.find(identifier);
    if (it != SymTable.end()) {
        return memory[it->second];
    }

    // Handle the case when the identifier is not found
    static Cell defaultCell = f_val(0); // Provide an appropriate default value
    return defaultCell;
}

inline void allocateVar(const std::string& id_, const Cell& c) {
    memory.push_back(c);
    SymTable[id_] = static_cast<int>(memory.size()) - 1;
}

inline void assignVar(const std::string& id_, const Cell& c) {
    auto it = SymTable.find(id_);
    if (it != SymTable.end()) {
        memory[it->second] = c;
    }
}



#endif // RUNTIME_CORE_CSQ