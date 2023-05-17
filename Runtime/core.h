/*
Csq's runtime is responsible for the memory management and other runtime features.
*/

#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

#include "object.h"
#include "memory.h"
#include "error.h"

/*
This will be used by parser to resemble current line.
*/
int line = 1;

/*Symbol table
Creating map for variable table storing the key value pair of name and variable struct.
We could even utilize this to do type checking easily.
*/
map<string, Variable> SY_Var;

void addVar(Variable var){
    SY_Var[var.name] = var;
}


/*
a<i32> = 4390 -------->i32 a = i32(memory[0])
b<i32> = a + a ------->i32 b = toi32(memory[0]) + toi32(memory[0])
*/
void assignVar(string var, string val, string type){
    if(isIdentifier(val)){
        auto it = SY_Var.find(val);
        if (it != SY_Var.end())
        {
            //Defied so:
            SY_Var[var].value_address = SY_Var[val].value_address;
        }
        else 
        {
            
        }
    }
}

#endif // RUNTIME_CORE_CSQ
