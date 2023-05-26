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
void allocateVar(string name, string type, TokenStream tokens)
{
    Variable var;
    var.name = name;
    var.type = type;
    TokenStream value_;
    for(Token token : tokens){
        if(token.type == IDENTIFIER){
            if(inTable(token.token))
            {
                //Get the Symbol
                Symbol symbol = SymTable[token.token];
                switch(symbol.type){
                    case VARIABLE:{
                        //Get the value present 
                        string val = readCell(SymTable[token.token].var.value_address);
                        if(isInt(val) || isDecimal(val)){
                            Token tok_;
                            tok_.token = val;
                            tok_.type = VALUE;
                            value_.push_back(tok_);
                        }
                        else{
                            Token tok_;
                            tok_.token = val;
                            tok_.type = STR;
                            value_.push_back(tok_);
                        }
                    }
                }
            }
            else{
                RuntimeError("undefined identifier '" + token.token + "'");
            }
        }
        else{
            value_.push_back(token);
        }
    }
    //Allocate the data to the memory
    addCell(eval(value_));
    var.value_address = TopCellAddress();
    Symbol sym_;
    sym_.var = var;
    sym_.type = VARIABLE;
    SymTable[var.name] = sym_;
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
