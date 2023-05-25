/*
Csq's runtime is responsible for the memory management and other runtime features.
*/

#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

#include "object.h"
#include "memory.h"
#include "error.h"
#include "function.h"
/*
This will be used by parser to resemble current line.
*/
int line = 1;


/*
Possible types of symbol for the symbol table.
*/
enum SYMBOL_TYPE{
    FUNCTION,
    VARIABLE,
};
/*
This struct stores a object of both Variable and Function which are to be used
as a symbol and make it easy to traverse the symbol table
*/
struct Symbol{
    Variable var;
    Function fun;
    SYMBOL_TYPE type;
};

/*Symbol table
Creating map for variable table storing the key value pair of name and variable struct.
We could even utilize this to do type checking easily.
*/
map<string, Symbol> SymTable;


/*
Function to allocate variables 
basically it first allocates the value into memory and then it creates Variable
object to add it to the symbol table.
*/
void allocateVar(string name, string type, TokenStream tokens)
{
    Variable var;
    
}

#endif // RUNTIME_CORE_CSQ
