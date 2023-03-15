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
struct Node{
    NODE_TYPE type;
    Node(NODE_TYPE nodetype){
        type = nodetype;
    }
    Node(){}
};

//Declaration for Node types.
struct Expr;
struct VarDecl;
struct VarAssign;
struct Block;
struct FunctionDecl;
struct ClassDecl;
struct ForLoop;
struct WhileLoop;
struct IfStmt;
struct ElifStmt;
struct ElseStmt;

// Definitions for above node types

struct Expr : Node{
    string expr;
    Expr(){type = EXPR_TYPE; expr = "";}
    Expr(string express){type = EXPR_TYPE; expr = express;}
};

struct VarDecl : Node{
    string name;
    Expr value;
    VarDecl(string name_, string value_){
        name = name_;
        value = value_;
        type = VAR_DECLARATION;
    }
    VarDecl(){
        name = "";
        value = Expr();
        type = VAR_DECLARATION;
    }
};


struct VarAssign : Node{
    string name;
    Expr value;
    VarAssign(string name_, string value_){
        name = name_;
        value = value_;
        type = VAR_ASSIGNMENT;
    }
    VarAssign(){
        name = "";
        value = Expr();
        type = VAR_ASSIGNMENT;
    }
};

struct Block : Node{
    vector<string> statements;
    Block(){type = BLOCK;}
    Block(string statement){statements.push_back(statement);type = BLOCK;}
};

//Definition for visit function 
string visit(const Ptr<Node>& node) {
    switch (node->type) {
        case VAR_DECLARATION: {
            Ptr<VarDecl> var = static_pointer_cast<VarDecl>(node);
            return "VAR " + var->name + " = " + var->value.expr;
        }
        case VAR_ASSIGNMENT: {
            Ptr<VarDecl> var = static_pointer_cast<VarDecl>(node);
            return var->name + " = " + var->value.expr;
        }
        case BLOCK:{
            Ptr<Block> block = static_pointer_cast<Block>(node);
            string code;
            for(string statement : block->statements)
                code += statement + ";\n";
            return code;
        }
        default:
            return "Unknown node type";
    }
}

#endif // AST_Csq4_H
