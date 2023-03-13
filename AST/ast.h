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

//Base class for all AST.
struct Node{
    NODE_TYPE type;
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
//Body for above AST node types

//Body for Value struct
struct Value : Node{
    NODE_TYPE type = VALUE_TYPE;
    Token value;
};


//Body for BinaryExpr struct
// struct BinaryExpr : Node{
//     NODE_TYPE type = BINARY_EXPR;
//     Token opt;
//     Node* value1;
//     Node* value2;

//     BinaryExpr(Node* value1, Node* value2, Token opt){
//         this->value1 = value1;
//         this->value2 = value2;
//         this->opt = opt;
//     }
//     BinaryExpr(){}
// };

//Body for expr node.
struct Expr : Node{
    string expr;
    NODE_TYPE type = EXPR_TYPE;
};

//Body for VarDecl struct
struct VarDecl : Node{
    NODE_TYPE type = VAR_DECLARATION;
    string name;
    string Dtype;
    Node* value;
};

//Body for VarAssign struct
struct VarAssign : Node{
    NODE_TYPE type = VAR_ASSIGNMENT;
    Node* value;
    string name;
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
    Node* condition;
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
string generateCode(Node* node) {
    switch (node->type) {
        case VALUE_TYPE: {
            Value* valueNode = static_cast<Value*>(node);
            return valueNode->value.token; // return the value as C++ code
        }
        case VAR_DECLARATION: {
            VarDecl* varDeclNode = static_cast<VarDecl*>(node);
            return  "VAR " + varDeclNode->name + " = " + generateCode(varDeclNode->value) + ";";
        }
        case VAR_ASSIGNMENT: {
            VarAssign* varAssignNode = static_cast<VarAssign*>(node);
            return varAssignNode->name + " = " + generateCode(varAssignNode->value) + ";";
        }
        case EXPR_TYPE:{
            Expr* exprNode = static_cast<Expr*>(node);
            return exprNode->expr;
        }
        case FOR_LOOP:{
            ForLoop* forLoopNode = static_cast<ForLoop*>(node);
            Block* bodyNode = static_cast<Block*>(forLoopNode->body);
            string condition = generateCode(forLoopNode->condition);
            string bodyCode = "";
            for (int i = 0; i < bodyNode->statements.size(); i++) {
                bodyCode += generateCode(bodyNode->statements[i]);
                bodyCode += "\n";
            }
            return "FOR (VAR " + forLoopNode->iter_name + " : " + condition + ") {\n"+ bodyCode + "}";
        }

        case WHILE_LOOP:{
            WhileLoop* whileLoopNode = static_cast<WhileLoop*>(node);
            string condition = generateCode(whileLoopNode->condition);
            Block* bodyNode = static_cast<Block*>(whileLoopNode->body);
            string bodyCode = "";
            for (int i = 0; i < bodyNode->statements.size(); i++) {
                bodyCode += generateCode(bodyNode->statements[i]);
                bodyCode += "\n";
            }
            return "WHILE (" + condition + ") {\n" + bodyCode + "}";
        }
        case IF_STATEMENT:{
            IfStmt* ifNode = static_cast<IfStmt*>(node);
            string condition = generateCode(ifNode->condition);
            Block* bodyNode = static_cast<Block*>(ifNode->body);
            string bodyCode = "";
            for (int i = 0; i < bodyNode->statements.size(); i++) {
                bodyCode += generateCode(bodyNode->statements[i]);
                bodyCode += "\n";
            }
            return "IF (" + condition + ") {\n" + bodyCode + "}\n";
        }
        case ELIF_STATEMENT:{
            ElifStmt* elifNode = static_cast<ElifStmt*>(node);
            string condition = generateCode(elifNode->condition);
            Block* bodyNode = static_cast<Block*>(elifNode->body);
            string bodyCode = "";
            for (int i = 0; i < bodyNode->statements.size(); i++) {
                bodyCode += generateCode(bodyNode->statements[i]);
                bodyCode += "\n";
            }
            return "ELIF (" + condition + ") {\n" + bodyCode + "}\n";
        }
        case ELSE_STATEMENT:{
            ElseStmt* elseNode = static_cast<ElseStmt*>(node);
            Block* bodyNode = static_cast<Block*>(elseNode->body);
            string bodyCode = "";
            for (int i = 0; i < bodyNode->statements.size(); i++) {
                bodyCode += generateCode(bodyNode->statements[i]);
                bodyCode += "\n";
            }
            return "ELSE{" + bodyCode + "}\n";
        }
        case FUNCTION_CALL:{
            FunctionCall* functionCallNode = static_cast<FunctionCall*>(node);
            string name = functionCallNode->name;
            string params = "";
            for (int i = 0; i < functionCallNode->param.size(); i++) {
                params += generateCode(functionCallNode->param[i]);
                if (i != functionCallNode->param.size() - 1) {
                    params += ", ";
                }
            }
            return name + "(" + params + ")";
        }
        case BLOCK:{
            Block* blockNode = static_cast<Block*>(node);
            string code = "{\n";
            for (int i = 0; i < blockNode->statements.size(); i++) {
                code += generateCode(blockNode->statements[i]);
                code += "\n";
            }
            code += "}";
            return code;
        }
        case FUNCTION_DECL:{
            FunctionDecl* funNode = static_cast<FunctionDecl*>(node);
            string params;
            for(VarDecl* var : funNode->param)
                params += var->name + ",";
            return "DEF " + funNode->name + " (" + params + ") {\n" + generateCode(funNode->body) + "}\n";
        }
        default: {
            return ""; // return empty string for unknown node types
        }
    }
}
#endif // AST_Csq4_H
