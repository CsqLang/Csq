#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include "../IR/IRcode.h"
#include <memory>

typedef enum {
    VALUE_TYPE = 1,
    VAR_DECLARATION,
    VAR_ASSIGNMENT,
    FUN_DEFINITION,
    CLASS_DEFINITION,
    FOR_LOOP,
    WHILE_LOOP,
    EXPR_TYPE,
    FUNCTION_CALL,
    FUNCTION_DECL,
    BLOCK,
    IF_STATEMENT,
    ELIF_STATEMENT,
    ELSE_STATEMENT,
} NODE_TYPE;

//Node struct
struct Node;
//A short alias for unique_ptr<Node>
typedef std::unique_ptr<Node> Nodetype;

//body struct for node type
struct Node{
    
};

#endif // AST_Csq4_H
