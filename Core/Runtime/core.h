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
Possible types of symbols for the symbol table.
*/
enum SYMBOL_TYPE
{
    FUNCTION,
    VARIABLE,
};
/*
This struct stores an object of both Variable and Function which are to be used
as a symbol to make it easy to traverse the symbol table.
*/
struct Symbol
{
    Variable var;
    Function fun;
    SYMBOL_TYPE type;
};

/* Symbol table
Creating a map for a variable table storing the key-value pairs of name and a variable struct.
We could even utilize this to do type checking easily.
*/
unordered_map<string, Symbol> SymTable;

inline int inTable(string name)
{
    return SymTable.find(name) != SymTable.end();
}

inline void traverseSymTable()
{
    for (const auto& pair : SymTable)
    {
        if (pair.second.type == VARIABLE)
        {
            printf("%s : { Type: %d Name: %s Value : %d }\n",
                   pair.first.c_str(), pair.second.type, pair.second.var.name.c_str(),
                   pair.second.var.value_address);
        }
        else
        {
        }
    }
}

inline Cell id(string identifier)
{
    if (SymTable.find(identifier) != SymTable.end())
    {
        return memory[SymTable[identifier].var.value_address];
    }
    else if (identifier != "ignore")
    {
        return f_val(0);  // Assuming f_val creates a Cell of the desired type
    }
    else
    {
        return f_val(0);  // Change to a default value as needed
    }
}

inline void allocateVar(string id_, const Cell& c)
{
    memory.push_back(c);
    Symbol sym;
    sym.var.name = id_;
    sym.type = VARIABLE;
    sym.var.value_address = memory.size() - 1;
    SymTable[id_] = sym;
}

inline void assignVar(string id_, const Cell& c)
{
    if (SymTable.find(id_) != SymTable.end())
    {
        memory[SymTable[id_].var.value_address] = c;
    }
    else
    {
        // Handle undefined identifier error
    }
}

// Ultimate class storage where a table of every class will be made.
map<string, Class> __classes__;

#endif // RUNTIME_CORE_CSQ
