#if !defined(BINARYAST_H_CSQ4)
#define BINARYAST_H_CSQ4
#include "ast.h"
#include "valueAST.h"

struct BinaryExp : AST {
    AST_TYPE type = BINARY_EXP;
    Value val1, val2;
    Token opt;
};

BinaryExp addBinaryExp(Value v1, Value v2, Token opt) {
    BinaryExp Exp;
    Exp.val1 = v1;
    Exp.val2 = v2;
    Exp.opt = opt;
    return Exp;
}

BinaryExp parseBinaryExp(vector<Token> tokens, int line) {
    BinaryExp exp;
    int value_flag = 1;
    for(Token token : tokens){
        if(token.type == VALUE || token.type == STR || token.type == IDENTIFIER && value_flag == 1){
            exp.val1 = addValue(token,line);
            value_flag = 2;
        }
        else if(token.type == VALUE || token.type == STR && value_flag == 2){
            exp.val2 = addValue(token,line);
            value_flag = 0;
        }
        else if(token.type == (ASOPERATOR || AROPERATOR || COPERATOR || LOPERATOR)){
            exp.opt = token;
        }
    }
    return exp;
}

AST* addNode(BinaryExp value){
    AST* ast = &value;
    ast->type = BINARY_EXP;
    return ast;
}

#endif // BINARYAST_H_CSQ4
