#if !defined(instructions_IRCsq4)
#define instructions_IRCsq4
#include "../AST/ast.h"


enum instructions{
    PUSHVAR,
    VARASSIGN,
    DEF,
    CALL,
    FOR,
    WHILE,
    IF,
    ELIF,
    ELSE,
    CLASS,
    PUSHVALUE,
};


/*
    Example::
    Csq code: a = 49
    AST representation:
    Variable Declaration
        /       \
       a        49
    IR representation:
    PUSHVAR a 49
*/

#endif // instructions_IRCsq4
