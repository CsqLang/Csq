#if !defined(varAST_Csq4)
#define varAST_Csq4
#include "../Tokenizer/tokenizer.h"
#include "ast.h"
#include "../Parser/variables.h"
struct VarAST{
    AST_TYPE type = VAR_ASSIGNMENT;
    Variable variable;
};


#endif // varAST_Csq4
