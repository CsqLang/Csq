#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include "../IR/IRcode.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Types of AST
enum NODE_TYPE{
    VALUE_TYPE = 1,
    VAR_DECLARATION = 2,
    VAR_ASSIGNMENT = 3,
    FUN_DEFINITION = 4,
    CLASS_DEFINITION = 5,
    FOR_LOOP = 6,
    WHILE_LOOP = 7,
    EXPR_TYPE = 8,
    FUNCTION_CALL = 9,
    FUNCTION_DECL  = 10,
    BLOCK = 11,
    IF_STATEMENT = 12,
    ELIF_STATEMENT = 13,
    ELSE_STATEMENT = 14,
};




//Inherited structs for different types of AST Node.

//Value struct for value_type AST node.
struct Value;
//BinaryExpr struct for binary expressions.
struct BinaryExpr;
//VarDecl struct for variable declarations.
struct VarDecl;
//VarAssign struct for variable assignments.
struct VarAssign;
//ForLoop struct for for loops.
struct ForLoop;
//WhileLoop struct for while loops.
struct WhileLoop;
//Function struct for functions definitions.
struct FunctionDecl;
//Function struct for functions calls.
struct FunctionCall;
//Class struct for Classes.
struct ClassDef;    
//Block struct for group of different nodes.
struct Block;
//IfStmt struct for if statements
struct IfStmt;
//ElifStmt struct for else if statements
struct ElifStmt;
//ElseStmt for Else statements
struct ElseStmt;
//Expr node to store any kind of expression without much processing.
struct Expr;

//Base class for all
class Node;
//Base class for all AST.
class Node{
    public:
        NODE_TYPE type;
};

//Body for Value struct
struct Value : public Node{
    Token value;
    Value(){
        type = VALUE_TYPE;
    }
    Value(Token val){
        value = val;
        type = VALUE_TYPE;
    }
};



//Body for expr node.
struct Expr : public Node{
    string expr;
    Expr(){
        type = EXPR_TYPE;
    }
    Expr(string expr_){
        type = EXPR_TYPE;
        expr = expr_;
    }
};

//Body for VarDecl struct
struct VarDecl : public Node{
    string name;
    string Dtype;
    Expr value;
    VarDecl(){type = VAR_DECLARATION;}
    VarDecl(string name_, Expr value_){
        name = name_;
        value = value_;
        type = VAR_DECLARATION;
    }
};

//Body for VarAssign struct
struct VarAssign : public Node{
    Expr value;
    string name;
    VarAssign(){type = VAR_ASSIGNMENT;}
    VarAssign(string name_, Expr val){
        type = VAR_ASSIGNMENT;
        name = name_;
        value = val;
    }
};

//Body for ForLoop struct
struct ForLoop : Node{
    NODE_TYPE type = FOR_LOOP;
    Node* condition;
    string iter_name;
    Block* body;
};

//Body for WhileLoop struct
struct WhileLoop : Node{
    NODE_TYPE type = FOR_LOOP;
    Node* condition;
    Block* body;
};

//Body for FunctionCall struct
struct FunctionCall : Node{
    NODE_TYPE type = FUNCTION_CALL;
    string name;
    vector<Node*> param;
};

//Body for Block struct
struct Block : Node{
    NODE_TYPE type = BLOCK;
    vector<Node*> statements;
};

//Body for FunctionDecl struct
struct FunctionDecl : Node{
    NODE_TYPE type = FUNCTION_DECL;
    string name;
    Block* body;
    vector<VarDecl*> param;
};

//Body for IfStmt struct
struct IfStmt : Node{
    NODE_TYPE type = IF_STATEMENT;
    Expr* condition;
    Block* body;
};
//Body for ElifStmt struct
struct ElifStmt : Node{
    NODE_TYPE type = ELIF_STATEMENT;
    Node* condition;
    Block* body;
};
//Body for ElseStmt struct
struct ElseStmt : Node{
    NODE_TYPE type = ELSE_STATEMENT;
    Block* body;
};

//Struct for ClassDef
struct ClassDef : Node{
    NODE_TYPE type = CLASS_DEFINITION;
    string name;
    Block* body;
};



//Help functions for Block node
Block newBlock(){
    Block block;
    block.type = BLOCK;
    return block;
}
void addStatement(Block block, Node* statement){
    block.statements.push_back(statement);
}


//Another visitor function to visit the AST nodes but this time it will also generate IR codes
string visit(Node node){
    switch(node.type){
        case VAR_DECLARATION:{
            
        }
    }
}


#endif // AST_Csq4_H
