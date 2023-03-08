#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"

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
    BINARY_EXPR = 8,
    FUNCTION_CALL = 9,
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
struct FunctionDef;
//Function struct for functions calls.
struct FunctionCall;
//Class struct for Classes.
struct ClassDef;

//Body for above AST node types

//Body for Value struct
struct Value : Node{
    NODE_TYPE type = VALUE_TYPE;
    Token value;
};


//Body for BinaryExpr struct
struct BinaryExpr : Node{
    NODE_TYPE type = BINARY_EXPR;
    Token opt;
    Node* value1;
    Node* value2;
};

//Body for VarDecl struct
struct VarDecl : Node{
    NODE_TYPE type = VAR_DECLARATION;
    string name;
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
};

//Body for WhileLoop struct
struct WhileLoop : Node{
    NODE_TYPE type = FOR_LOOP;
    Node* condition;
};

//Body for FunctionCall struct
struct FunctionCall : Node{
    NODE_TYPE type = FUNCTION_CALL;
    string name;
    vector<Node*> param;
};


void printNode(Node* node){
    switch (node->type) {
        case VALUE_TYPE: {
            Value* valueNode = static_cast<Value*>(node);
            printf("|Value : %s\n",valueNode->value.token.c_str());
            break;
        }
        case VAR_DECLARATION: {
            VarDecl* varDeclNode = static_cast<VarDecl*>(node);
            printf("|Variable Declaration: %s\n",varDeclNode->name.c_str());
            printNode(varDeclNode->value);
            break;
        }
        case VAR_ASSIGNMENT: {
            VarAssign* varAssignNode = static_cast<VarAssign*>(node);
            printf("|Variable Assignment : %s\n",varAssignNode->name.c_str());
            printNode(varAssignNode->value);
            break;
        }
        case BINARY_EXPR: {
            BinaryExpr* binaryExprNode = static_cast<BinaryExpr*>(node);
            printf("|Binary Expression : %s\n",binaryExprNode->opt.token.c_str());
            printNode(binaryExprNode->value1);
            printNode(binaryExprNode->value2);
            break;
        }
        case FOR_LOOP:{
            ForLoop* forLoopNode = static_cast<ForLoop*>(node);
            printf("|For Loop: %s over ",forLoopNode->iter_name.c_str());
            printNode(forLoopNode->condition);
        }
        case WHILE_LOOP:{
            WhileLoop* whileLoopNode = static_cast<WhileLoop*>(node);
            printf("|While Loop for ");
            printNode(whileLoopNode->condition);
        }
        case FUNCTION_CALL:{
            FunctionCall* functionCallNode = static_cast<FunctionCall*>(node);
            printf("Function Call : Name : %s \n",functionCallNode->name.c_str());
            if(functionCallNode->param.size() > 0)
                for(int paramCount = 1; paramCount <= functionCallNode->param.size();paramCount++){
                    printf("|Argument %d: \n\t",paramCount);
                    printNode(functionCallNode->param[paramCount-1]);
                    printf("\n");
                }
            else
                ignore;
        }
    }
}

#endif // AST_Csq4_H
