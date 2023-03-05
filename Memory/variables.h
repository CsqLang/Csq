#if !defined(Variable_H_Csq4)
#define Variable_H_Csq4
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include "exception.h"
//Errors for invalid use cases.
void ExpectedAValue(int line){
    printf("Error: At line %d expected a value after '='.\n",line);
    error_count++;
}

//This struct will be storing the properties of a variable.
struct Variable{
    string name;
    string type;
    string value;
    int lineOfDeclaration;
};

//The syntax of variables
/*
    Syntax:
    <name> : <type> = <value>
    Example:
    a:i32 = 59
*/

//This function will take tokens and return the object of Variable struct.
Variable VariableAssignment(vector<Token> tokens, int line){
    Variable variable;
    bool value_end = true;
    int pos = 0;
    for(Token tok : tokens){
        if(pos == 0 && tok.type == IDENTIFIER){
            variable.name = tok.token;
            pos++;
        }
        else if(tok.type == ASOPERATOR && value_end == true){
            value_end = false;
            pos++;
        }
        else if(value_end == false && pos+1 != tokens.size()){
            variable.value += tok.token;
        }
        else if(value_end == false && pos+1 == tokens.size()){
            variable.value += tok.token;
            value_end = true;
        }
    }
    if(variable.value == ""){
        ExpectedAValue(line);
    }
    return variable;
}

#endif // Variable_H_Csq4
