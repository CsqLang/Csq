#if !defined(varAST_Csq4)
#define varAST_Csq4
#include "../Tokenizer/tokenizer.h"
#include "ast.h"
#include "../Parser/variables.h"
struct VarDec : AST{
    AST_TYPE type = VAR_DECLARATION;
    string name;
    AST* value;
};

VarDec addVariable(string name, AST* value){
    VarDec var;
    var.name = name;
    var.value = value;
    return var;
}

//Stuct to do variable assignment and generate AST.
struct VarAssign : AST{
    AST_TYPE type = VAR_ASSIGNMENT;
    string name;
    AST* value;
};

VarAssign assignVariable(string name, AST* value){
    VarAssign var;
    var.name = name;
    var.value = value;
}



#endif // varAST_Csq4
