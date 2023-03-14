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
//Base class for all AST.
class Node{
    public:
        NODE_TYPE type;
        virtual string tostr();
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
    string tostr(){
        return "";
    }
};



//Body for expr node.
struct Expr : Node{
    string expr;
    Expr(){
        type = EXPR_TYPE;
    }
    Expr(string expr_){
        type = EXPR_TYPE;
        expr = expr_;
    }
    virtual string tostr(){
        return expr;
    }
};

//Body for VarDecl struct
struct VarDecl : Node{
    string name;
    string Dtype;
    Expr value;
    VarDecl(){type = VAR_DECLARATION;}
    VarDecl(string name_, Expr value_){
        name = name_;
        value = value_;
        type = VAR_DECLARATION;
    }
    virtual string tostr(){
        return "VAR " + name + " = " + value.tostr();
    }
};

//Body for VarAssign struct
struct VarAssign : Node{
    Expr value;
    string name;
    VarAssign(){type = VAR_ASSIGNMENT;}
    VarAssign(string name_, Expr val){
        type = VAR_ASSIGNMENT;
        name = name_;
        value = val;
    }
    string tostr(){
        return "";
    }
};

//Body for ForLoop struct
struct ForLoop : Node{
    NODE_TYPE type = FOR_LOOP;
    Node* condition;
    string iter_name;
    Block* body;
    virtual string tostr(){
        return "";
    }
};

//Body for WhileLoop struct
struct WhileLoop : Node{
    NODE_TYPE type = FOR_LOOP;
    Node* condition;
    Block* body;
    virtual string tostr(){
        return "";
    }
};

//Body for FunctionCall struct
struct FunctionCall : Node{
    NODE_TYPE type = FUNCTION_CALL;
    string name;
    vector<Node*> param;
    virtual string tostr(){
        return "";
    }
};

//Body for Block struct
struct Block : Node{
    NODE_TYPE type = BLOCK;
    vector<Node*> statements;
    virtual string tostr(){
        return "";
    }
};

//Body for FunctionDecl struct
struct FunctionDecl : Node{
    NODE_TYPE type = FUNCTION_DECL;
    string name;
    Block* body;
    vector<VarDecl*> param;
    virtual string tostr(){
        return "";
    }
};

//Body for IfStmt struct
struct IfStmt : Node{
    NODE_TYPE type = IF_STATEMENT;
    Expr* condition;
    Block* body;
    virtual string tostr(){
        return "";
    }
};
//Body for ElifStmt struct
struct ElifStmt : Node{
    NODE_TYPE type = ELIF_STATEMENT;
    Node* condition;
    Block* body;
    virtual string tostr(){
        return "";
    }
};
//Body for ElseStmt struct
struct ElseStmt : Node{
    NODE_TYPE type = ELSE_STATEMENT;
    Block* body;
    virtual string tostr(){
        return "";
    }
};

//Struct for ClassDef
struct ClassDef : Node{
    NODE_TYPE type = CLASS_DEFINITION;
    string name;
    Block* body;
    string tostr(){
        return "";
    }
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
// Visitor function to visit the AST nodes and generate IR codes
string visit(Node& node) {
    switch (node.type) {
        case VAR_DECLARATION: {
            VarDecl& varDecl = static_cast<VarDecl&>(node);
            return varDecl.tostr();
        }
        case VAR_ASSIGNMENT: {
            VarAssign& varAssign = static_cast<VarAssign&>(node);
            return varAssign.tostr();
        }
        case FUNCTION_DECL: {
            FunctionDecl& funcDecl = static_cast<FunctionDecl&>(node);
            return funcDecl.tostr();
        }
        case FUNCTION_CALL: {
            FunctionCall& funcCall = static_cast<FunctionCall&>(node);
            return funcCall.tostr();
        }
        case BLOCK: {
            Block& block = static_cast<Block&>(node);
            string result;
            for (Node* statement : block.statements) {
                result += visit(*statement);
            }
            return result;
        }
        case IF_STATEMENT: {
            IfStmt& ifStmt = static_cast<IfStmt&>(node);
            return ifStmt.tostr() + visit(*ifStmt.condition) + visit(*ifStmt.body);
        }
        case ELIF_STATEMENT: {
            ElifStmt& elifStmt = static_cast<ElifStmt&>(node);
            return elifStmt.tostr() + visit(*elifStmt.condition) + visit(*elifStmt.body);
        }
        case ELSE_STATEMENT: {
            ElseStmt& elseStmt = static_cast<ElseStmt&>(node);
            return elseStmt.tostr() + visit(*elseStmt.body);
        }
        case FOR_LOOP: {
            ForLoop& forLoop = static_cast<ForLoop&>(node);
            return forLoop.tostr() + visit(*forLoop.condition) + visit(*forLoop.body);
        }
        case WHILE_LOOP: {
            WhileLoop& whileLoop = static_cast<WhileLoop&>(node);
            return whileLoop.tostr() + visit(*whileLoop.condition) + visit(*whileLoop.body);
        }
        case CLASS_DEFINITION: {
            ClassDef& classDef = static_cast<ClassDef&>(node);
            return classDef.tostr() + visit(*classDef.body);
        }
        case VALUE_TYPE: {
            Value& value = static_cast<Value&>(node);
            return value.tostr();
        }
        case EXPR_TYPE: {
            Expr& expr = static_cast<Expr&>(node);
            return expr.tostr();
        }
        default: {
            return "";
        }
    }
}



#endif // AST_Csq4_H
