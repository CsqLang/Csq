#if !defined(varAST_Csq4)
#define varAST_Csq4
#include "../Tokenizer/tokenizer.h"
#include "ast.h"
#include "../Parser/variables.h"
struct VarAST : AST{
    AST_TYPE type = VAR_DECLARATION;
    string name;
    AST* value;
};

VarAST addVariable(string name, AST* value){
    VarAST var;
    var.name = name;
    var.value = value;
    return var;
}


#endif // varAST_Csq4
