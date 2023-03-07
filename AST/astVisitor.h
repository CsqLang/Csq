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


//Traverse Binary Expression tree

void printTree(BinaryExp* tree){
  printf("Binary Expression : %s\n",tree->opt.token.c_str());
  printf("|Value : %s\n |Value : %s\n", tree->val1.token.token.c_str(), tree->val2.token.token.c_str());
}
void printTree(Value* tree){
  printf("Binary Expression : %s\n",tree->token.token.c_str());
}
void printTree(AST* tree){
  if(tree->type == VALUE_TYPE)
    printTree(cast(Value*)(tree));
  else if(tree->type == BINARY_EXP)
    printTree(cast(BinaryExp*)(tree));
  else{
    printf("NONE %d \n",tree->type);
  }
}
void printTree(VarDec* dec){
  printf("Variable Declaration : %s\n",dec->name.c_str());
  printTree(dec->value);
}
void DFSprint(AST* tree){
    switch(tree->type){
      case VALUE_TYPE:{
        printTree(cast(Value*)(tree));
        break;
      }
      case BINARY_EXP:{
        printTree(cast(BinaryExp*)(tree));
        break;
      }
      case VAR_DECLARATION: {
          printTree(cast(VarDec*)(tree));
          break;
      }
    }
}


#endif // AST_CSQ4_VISITOR_H
