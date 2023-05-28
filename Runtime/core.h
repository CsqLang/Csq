/*
Csq's runtime is responsible for the memory management and other runtime features.
*/

#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ


/*
This will be used by parser to resemble current line.
*/
int line = 1;

#include "error.h" 
#include "object.h"
#include "memory.h"
#include "function.h"
#include "jit.h"
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

int inTable(string name){
    int s = 0;
    for(pair<string, Symbol> p : SymTable){
        if(p.first == name){
            s = 1;
            break;
        }
    }
    return s;
}

/*
Function to allocate variables 
basically it first allocates the value into memory and then it creates Variable
object to add it to the symbol table.
*/
void allocateVar(string name, string type, TokenStream value)
{
    Variable var;
    var.name = name;
    var.type = type;

    TokenStream nval;
    //Filter identifiers by placing their values
    for(int i = 0;i<value.size();i++){
        Token token = value[i];
        if(token.type == IDENTIFIER){
            if(inTable(token.token)){
                if(SymTable[token.token].type == VARIABLE){
                    Cell cell = memory[(SymTable[token.token].var.value_address)];
                    if(cell.type == STRING){
                        nval.push_back(create(STR,cell.sval));
                    }
                    else if(cell.type == FLOAT){
                        nval.push_back(create(VALUE,to_string(cell.fval)));
                    }
                    else{
                        nval.push_back(create(VALUE,to_string(cell.ival)));
                    }
                }
                else{
                    // ... For functions
                }
            }
            else{
                RuntimeError("undefined identifier '" + token.token + "'.");
            }
        }
        else{
            nval.push_back(token);
        }
    }

    var.value_address = eval(nval);
    Symbol sym;
    sym.type = VARIABLE;
    sym.var = var;
    SymTable[name] = sym;
}

void assignVar(string name, TokenStream value){
    TokenStream nval;
    //Filter identifiers by placing their values
    for(int i = 0;i<value.size();i++){
        Token token = value[i];
        if(token.type == IDENTIFIER){
            if(inTable(token.token)){
                if(SymTable[token.token].type == VARIABLE){
                    Cell cell = memory[(SymTable[token.token].var.value_address)];
                    if(cell.type == STRING){
                        nval.push_back(create(STR,cell.sval));
                    }
                    else if(cell.type == FLOAT){
                        nval.push_back(create(VALUE,to_string(cell.fval)));
                    }
                    else{
                        nval.push_back(create(VALUE,to_string(cell.ival)));
                    }
                }
                else{
                    // ... For functions
                }
            }
            else{
                RuntimeError("undefined identifier '" + token.token + "'.");
            }
        }
        else{
            nval.push_back(token);
        }
    }
    
}

void traverseSymTable(){
    for(pair<string,Symbol> p : SymTable){
        if(p.second.type == VARIABLE){
            printf("%s : { %d {%s %s %d} }\n",p.first.c_str(),p.second.type, p.second.var.name.c_str(), p.second.var.type.c_str(), p.second.var.value_address);
        }
        else{
            // printf("%s : { %d {%s %s %d} }\n",p.first,p.second.type, p.second.var.name, p.second.var.type, p.second.var.value_address);
        }
    }
}

#endif // RUNTIME_CORE_CSQ
