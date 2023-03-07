#if !defined(AST_CSQ4_VISITOR_H)
#define AST_CSQ4_VISITOR_H

//All AST Source
#include "varAST.h"
#include "valueAST.h"
#include "binaryExpAST.h"
#include "functionAST.h"

//IR imports to generate IR after visiting AST.
#include "../IR/instructions.h"

//Cast alias for static_cast
#define cast(v) static_cast<v>

/*
Sample code : var a = 44 + 6

AST view: 
                VAR_DEC
                  /  \
                a    BinaryExp
                      /  |   \
                     44  +   6


To visit AST there are several algorithms but for Csq we are gonna use DFS(Depth First Search).
*/

//This function will traverse and print the types of statements:
void DFSprint(AST* tree){
    switch(tree->type){
      case VALUE_TYPE:{
        Value* val = cast(Value*)(tree);
        printf("|----VALUE--->%s\n", val->token.token.c_str());
        break;
      }
      case BINARY_EXP:{
        BinaryExp* expr = cast(BinaryExp*)(tree);
        printf("Binary Expression : %s ",expr->opt.token.c_str());
        //Now creating separate nodes for Values to get meta AST.
        AST* val1_ast = addNode(expr->val1);
        AST* val2_ast = addNode(expr->val2);
        DFSprint(val1_ast);
        DFSprint(val2_ast);
        break;
      }
    }
}


#endif // AST_CSQ4_VISITOR_H
