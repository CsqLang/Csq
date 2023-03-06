#if !defined(AST_Csq4_H)
#define AST_Csq4_H
#include "../Grammar/grammar.h"
enum AST_TYPE{
    VALUE = 1,
    VAR_DECLARATION = 2,
    VAR_ASSIGNMENT = 3,
    FUN_DEFINITION = 4,
    CLASS_DEFINITION = 5,
    FOR_LOOP = 6,
    WHILE_LOOP = 7,
};

#endif // AST_Csq4_H
