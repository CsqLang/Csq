#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include "../IR/IRcode.h"
#include <memory>
using namespace std;

//Alias for shared_ptr;
#define Ptr shared_ptr
typedef enum {
    VAR_DECLARATION,
    VAR_ASSIGNMENT,
    FUN_DEFINITION,
    CLASS_DEFINITION,
    FOR_LOOP,
    WHILE_LOOP,
    EXPR_TYPE,
    FUNCTION_DECL,
    BLOCK,
    IF_STATEMENT,
    ELIF_STATEMENT,
    ELSE_STATEMENT,
} NODE_TYPE;

//Node struct
struct Node;
//body struct for node type
typedef struct Node{
    NODE_TYPE type;
    Node(NODE_TYPE nodetype){
        type = nodetype;
    }
    Node(){}
};

//Declaration for Node types.
typedef struct Expr;
typedef struct VarDecl;
typedef struct VarAssign;
typedef struct Block;
typedef struct FunctionDecl;
typedef struct ClassDecl;
typedef struct ForLoop;
typedef struct WhileLoop;
typedef struct IfStmt;
typedef struct ElifStmt;
typedef struct ElseStmt;

// Definitions for above node types

typedef struct VarDecl : Node{
    string name;
    string value;
    VarDecl(string name_, string value_){
        name = name_;
        value = value_;
        type = VAR_DECLARATION;
    }
    VarDecl(){
        name = "";
        value = "";
        type = VAR_DECLARATION;
    }
};


//Visit function.
string visit(const Ptr<Node>& node);
//Definition for visit function 

string visit(const Ptr<Node>& node) {
    switch (node->type) {
        case VAR_DECLARATION: {
            Ptr<VarDecl> var = static_pointer_cast<VarDecl>(node);
            return "VarDecl: name=" + var->name + ", value=" + var->value;
        }
        default:
            return "Unknown node type";
    }
}

#endif // AST_Csq4_H
