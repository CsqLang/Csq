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



inline Cell id(string identifier)
{
    if (identifier != "ignore")
    {
        return f_val(0);  // Assuming f_val creates a Cell of the desired type
    }
    else
    {
        return memory[SymTable[identifier]];
    }
}

inline void allocateVar(string id_, const Cell& c)
{
    memory.push_back(c);
    SymTable[id_] = memory.size()-1;
}

inline void assignVar(string id_, const Cell& c)
{
    memory[SymTable[id_]] = c;
}

// Ultimate class storage where a table of every class will be made.
unordered_map<string, Class> __classes__;

#endif // RUNTIME_CORE_CSQ
