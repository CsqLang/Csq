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

typedef struct Node {
    NODE_TYPE type;
    union {
        struct {
            char* value;
        } value_node;
        struct {
            char* name;
            std::unique_ptr<Node> value;
        } var_declaration_node;
        struct {
            char* name;
            std::unique_ptr<Node> value;
        } var_assignment_node;
        struct {
            char* name;
            std::unique_ptr<Node> args;
            std::unique_ptr<Node> body;
        } fun_definition_node;
        struct {
            char* name;
            std::unique_ptr<Node> body;
        } class_definition_node;
        struct {
            std::unique_ptr<Node> initialization;
            std::unique_ptr<Node> condition;
            std::unique_ptr<Node> update;
            std::unique_ptr<Node> body;
        } for_loop_node;
        struct {
            std::unique_ptr<Node> condition;
            std::unique_ptr<Node> body;
        } while_loop_node;
        struct {
            char* op;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
        } expr_type_node;
        struct {
            char* name;
            std::unique_ptr<Node> args;
        } function_call_node;
        struct {
            char* name;
            std::unique_ptr<Node> args;
            std::unique_ptr<Node> body;
        } function_decl_node;
        struct {
            std::unique_ptr<Node> statements;
        } block_node;
        struct {
            std::unique_ptr<Node> condition;
            std::unique_ptr<Node> body;
        } if_statement_node;
        struct {
            std::unique_ptr<Node> condition;
            std::unique_ptr<Node> body;
        } elif_statement_node;
        struct {
            std::unique_ptr<Node> body;
        } else_statement_node;
    };
} Node;

// Function to create a new value node
std::unique_ptr<Node> create_value_node(char* value) {
    auto node = std::make_unique<Node>();
    node->type = VALUE_TYPE;
    node->value_node.value = value;
    return node;
}

// Function to create a new variable declaration node
std::unique_ptr<Node> create_var_declaration_node(char* name, std::unique_ptr<Node> value) {
    auto node = std::make_unique<Node>();
    node->type = VAR_DECLARATION;
    node->var_declaration_node.name = name;
    node->var_declaration_node.value = std::move(value);
    return node;
}

// Function to create a new variable assignment node
std::unique_ptr<Node> create_var_assignment_node(char* name, std::unique_ptr<Node> value) {
    auto node = std::make_unique<Node>();
    node->type = VAR_ASSIGNMENT;
    node->var_assignment_node.name = name;
    node->var_assignment_node.value = std::move(value);
    return node;
}

#endif // AST_Csq4_H
