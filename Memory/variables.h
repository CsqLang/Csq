#if !defined(Variable_H_Csq4)
#define Variable_H_Csq4
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
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
Variable VariableAssignment(vector<Token> tokens){
    Variable variable;
    bool type_end,value_end = true;
    int pos = 0;
    for(Token tok : tokens){
        if(tok.type == IDENTIFIER){
            variable.name = tok.token;
            pos++;
        }
        else if(tok.type == SYMBOL && tok.token == ":"){
            type_end = false;
            pos++;
        }
        else if(type_end == false && tok.type != ASOPERATOR){
            variable.type += tok.token;
            pos++;
        }
        else if(type_end == false && tok.type == ASOPERATOR && value_end == true){
            type_end = true;
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
    return variable;
}

#endif // Variable_H_Csq4
