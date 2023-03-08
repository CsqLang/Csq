#if !defined(AST_Csq4_H)
#define AST_Csq4_H

//Imports
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
#include <iostream>
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
typedef struct Value;
//BinaryExpr struct for binary expressions.
typedef struct BinaryExpr;
//VarDecl struct for variable declarations.
typedef struct VarDecl;
//VarAssign struct for variable assignments.
typedef struct VarAssign;
//ForLoop struct for for loops.
typedef struct ForLoop;
//WhileLoop struct for while loops.
typedef struct WhileLoop;
//Function struct for functions definitions.
typedef struct FunctionDef;
//Function struct for functions calls.
typedef struct FunctionCall;
//Class struct for Classes.
typedef struct ClassDef;

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


void printNode(Node* node){
    switch (node->type) {
        case VALUE_TYPE: {
            Value* valueNode = static_cast<Value*>(node);
            std::cout << "|Value: " << valueNode->value.token << std::endl;
            break;
        }
        case VAR_DECLARATION: {
            VarDecl* varDeclNode = static_cast<VarDecl*>(node);
            std::cout << "|Variable Declaration: " << varDeclNode->name << std::endl;
            printNode(varDeclNode->value);
            break;
        }
        case VAR_ASSIGNMENT: {
            VarAssign* varAssignNode = static_cast<VarAssign*>(node);
            std::cout << "|Variable Assignment: " << varAssignNode->name << "\n";
            printNode(varAssignNode->value);
            break;
        }
        case BINARY_EXPR: {
            BinaryExpr* binaryExprNode = static_cast<BinaryExpr*>(node);
            std::cout << "|Binary Expression: " << binaryExprNode->opt.token << "\n|";
            printNode(binaryExprNode->value1);
            printNode(binaryExprNode->value2);
            break;
        }
    }
}

#endif // AST_Csq4_H
