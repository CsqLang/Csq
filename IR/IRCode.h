#if !defined(IRCODE_H_Csq4)
#define IRCODE_H_Csq4

#include "instructions.h"
//Struct to represent every IR code:
struct IR;
struct IR{
    instructions type;
    string code;
};

//The stack storing the IR codes.
vector<IR> IRStack;

//Functions used to add IR codes to the stack.
void pushVariable(string name, Node* value);
void pushValue(Value value);
void defFunction(string name, Block body);

#endif // IRCODE_H_Csq4
