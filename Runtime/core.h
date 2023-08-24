#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

/*
Csq's runtime is responsible for the memory management and other runtime features.
*/

/*
This will be used by parser to resemble current line.
*/
int line_ = 1;

#include "error.h" 
#include "object.h"
#include "memory.h"
#include "function.h"
#include "eval.h"
#include <unordered_map>
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
unordered_map<string, Symbol> SymTable;

vector<string> var_names;

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

int isVar(string name){
    int s = 0;
    for(string p : var_names){
        if(p == name){
            s = 1;
            break;
        }
    }
    return s;
}

void traverseSymTable(){
    for(pair<string,Symbol> p : SymTable){
        if(p.second.type == VARIABLE){
            printf("%s : { %d Name: %s Type: %s Value : %d }\n",p.first.c_str(),p.second.type, p.second.var.name.c_str(), p.second.var.type.c_str(), p.second.var.value_address);
        }
        else{}
    }
}


Cell id(string identifier){
    return memory[SymTable[identifier].var.value_address];
}

void allocateVar(string id_, string type, Cell c){
    memory.push_back(c);
    Symbol sym;
    sym.var.name = id_;
    sym.type = VARIABLE;
    sym.var.value_address = TopCellAddress();
    SymTable[id_] = sym;
}

void allocateVar(string id_){
    memory.push_back(Cell(f_val(0)));
    Symbol sym;
    sym.var.name = id_;
    sym.type = VARIABLE;
    sym.var.value_address = TopCellAddress();
    SymTable[id_] = sym;
}


void allocateVar(string id_, string type, vector<Cell> c){
    int cell_addr = TopCellAddress();
    addCell(c);
    Symbol sym;
    sym.var.name = id_;
    sym.type = VARIABLE;
    sym.var.isCollection = true;
    sym.var.value_address = cell_addr+1;

    SymTable[id_] = sym;
    
}

vector<Cell> removeItemAt(vector<Cell>& vec, int itemNum) {
    // Check if the itemNum is valid (within the range of vector's size)
    if (itemNum >= 0 && itemNum < vec.size()) {
        // Erase the element at the specified position
        vec.erase(vec.begin() + itemNum);
    }
    // Return the modified vector
    return vec;
}

void assignVar(string id_, Cell c) {
    int oldAddress = SymTable[id_].var.value_address;
    memory[oldAddress] = c;
}

void assignVar(string id, int index, Cell c){
    memory[SymTable[id].var.value_address + index] = c;
}

Cell id(string identifier, int index){
    if(index == 0){
        return memory[SymTable[identifier].var.value_address];
    }
    else{
        return memory[SymTable[identifier].var.value_address + index];
    }
}



#endif // RUNTIME_CORE_CSQ
