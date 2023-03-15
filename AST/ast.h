#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include "../IR/IRcode.h"
#include <memory>
using namespace std;

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
//A short alias for shared_ptr<Node>
#define Ptr(type_) shared_ptr<type_>
//body struct for node type
struct Node{
    NODE_TYPE type;
    Node(NODE_TYPE nodetype){
        type = nodetype;
    }
    Node(){}
};

struct VarDecl : Node{
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

string visit(const Ptr(Node)& node) {
    switch (node->type) {
        case VAR_DECLARATION: {
            Ptr(VarDecl) var = static_pointer_cast<VarDecl>(node);
            return "VarDecl: name=" + var->name + ", value=" + var->value;
        }
        default:
            return "Unknown node type";
    }
}

#endif // AST_Csq4_H
