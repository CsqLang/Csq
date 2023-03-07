#if !defined(AST_Csq4_H)
#define AST_Csq4_H
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
//Types of AST
enum AST_TYPE{
    VALUE_TYPE = 1,
    VAR_DECLARATION = 2,
    VAR_ASSIGNMENT = 3,
    FUN_DEFINITION = 4,
    CLASS_DEFINITION = 5,
    FOR_LOOP = 6,
    WHILE_LOOP = 7,
    BINARY_EXP = 8,
};

//Base class for all AST.
struct AST{
    AST_TYPE type;
};


#endif // AST_Csq4_H
