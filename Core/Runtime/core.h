#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

/*
Csq's runtime is responsible for the memory management and other runtime features.
*/

/*
This will be used by parser to resemble the current line.
*/
int line_ = 1;

#include "object.h"
#include "memory.h"
#include "function.h"
#include "eval.h"
#include "class.h"
#include <unordered_map>

/*
Creating a map for a variable table storing the key-value pairs of name and the address of value.
*/
unordered_map<string, int> SymTable;

inline int inTable(string name)
{
    return SymTable.find(name) != SymTable.end();
}


inline Cell id(const string& identifier) {
    auto it = SymTable.find(identifier);
    if (it != SymTable.end()) {
        return memory[it->second];
    }
    // Handle the case when the identifier is not found
    return f_val(0); // Provide an appropriate default value
}


inline void allocateVar(string id_, const Cell& c)
{
    memory.emplace_back(c);
    SymTable[id_] = memory.size()-1;
}

inline void assignVar(const string& id_, const Cell& c) {
    auto it = SymTable.find(id_);
    if (it != SymTable.end()) {
        memory[it->second] = c; // Update the existing value
    } else {
        // Handle the case when the identifier is not found
    }
}
// Ultimate class storage where a table of every class will be made.
unordered_map<string, Class> __classes__;

#endif // RUNTIME_CORE_CSQ
