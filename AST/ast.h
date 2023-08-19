#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
using namespace std;

typedef vector<Token> TokenStream;
typedef vector<string> StringStream;
typedef vector<vector<Token>> Lines;

enum NodeType{
    EXPR,
    VAR_DECL,
    VAR_ASSIGN,
    FUN_DECL,
    IF_STMT,
    ELSE_STMT,
    ELIF_STMT,
    FOR_STMT,
    WHILE_STMT,
    BLOCK,
    FUN_CALL,
    PRINT,
    TYPE, // to print the type of an object
    ACCESS,
    COLLECTION_UPDATE,
    RETURN,
    UNKNOWN_NODE,
};

struct ASTNode {
    NodeType type;
    int indent_level;
};

struct ExprNode : ASTNode {
    TokenStream tokens;
    ExprNode(){
        type = EXPR;
    }
};

struct VarDeclNode : ASTNode {
    string identifier;
    string var_type;
    ExprNode value;
    VarDeclNode(){
        type = VAR_DECL;
    }
};

struct VarAssignNode : ASTNode {
    string identifier;
    ExprNode value;
    VarAssignNode(){
        type = VAR_ASSIGN;
    }
};

struct BlockNode : ASTNode {
    vector<ASTNode*> statements;
    BlockNode(){
        type = BLOCK; 
    }
};

struct FunDeclNode : ASTNode {
    string identifier;
    vector<string> parameters;
    FunDeclNode(){
        type = FUN_DECL;
    }
    // BlockNode body;
};

struct IfStmtNode : ASTNode {
    ExprNode condition;
    IfStmtNode(){
        type = IF_STMT;
    }
    IfStmtNode(IfStmtNode cond, int ind){
        type = IF_STMT;
        condition = cond.condition;
        indent_level = ind;
    }
    // BlockNode body;
};

struct ElseStmtNode : ASTNode {
    ElseStmtNode(){
        type = ELSE_STMT;
    }
    // BlockNode body;
};

struct ElifStmtNode : ASTNode {
    ExprNode condition;
    ElifStmtNode(){
        type = ELIF_STMT;
    }
    // BlockNode body;
};

struct ForStmtNode : ASTNode {
    BlockNode body;
    string iter_name;
    ExprNode condition;
    ForStmtNode(){
        type = FOR_STMT;
    }
};

struct WhileStmtNode : ASTNode {
    // BlockNode body;
    ExprNode condition;
    WhileStmtNode(){
        type = WHILE_STMT;
    }
};

struct CallNode : ASTNode {
    string name;
    vector<Token> params;
    CallNode(){
        type = FUN_CALL;
    }
};

struct PrintNode : ASTNode {
    ExprNode value;
    PrintNode(){
        type = PRINT;
    }
    PrintNode(PrintNode node, int ind){
        type = PRINT;
        indent_level = ind;
        value = node.value;
    }
};
struct TypeNode : ASTNode {
    TypeNode(){
        type = TYPE;
    }
};
struct UnknownNode : ASTNode {
    UnknownNode(){
        type = UNKNOWN_NODE;
    }
};

struct AccessNode : ASTNode {
    int index = 0;
    string source;
    AccessNode(){
        type = ACCESS;
    }
};

struct CollectionUpdateNode : ASTNode {
    ExprNode index;
    string source;
    ExprNode value;
    CollectionUpdateNode(){
        type = COLLECTION_UPDATE;
    }
};

struct ReturnNode : ASTNode {
    ExprNode value;
    ReturnNode(){
        type = RETURN;
    }
};


#endif // AST_Csq4_H
