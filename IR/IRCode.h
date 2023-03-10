#if !defined(IRCODE_H_Csq4)
#define IRCODE_H_Csq4

#include "instructions.h"
//The stack storing the IR codes.
string IR = "Program : \n";

void defClass(string name, Block* body){
    IR += "CLASS " + name + "\n" + generateCode(body) + ";\n";
}

void declVar(string name,string type, Node* val){
    IR += type + " " + name + " = " + generateCode(val) + ";\n";
}

void assignVar(string name, Node* val){
    IR += name + " =  " + generateCode(val) + ";\n";
}

#endif // IRCODE_H_Csq4
