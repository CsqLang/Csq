#if !defined(Stack_H)
#define Stack_H
#include "../Grammar/grammar.h"

vector<string> Variables;
vector<string> Functions;
vector<string> Group_stack;

int FunctionStackLength(){
    return Functions.size();
}

int VariableStackLength(){
    return Variables.size();
}

#endif // Stack_H
