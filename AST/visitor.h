/*This is the implementation for visitor for AST.*/
#if !defined(VISITOR_H_CSQ4)
#define VISITOR_H_CSQ4

#include "../Runtime/core.h"

string visit_ExprNode(ExprNode node){
    string result;
    for(Token token : node.tokens){
        result += token.token;
    }
    return result;
}

Cell visit_Call(CallNode node){
    // fun(3,56)

    for(Token arg : node.params){
        
    }
    return Cell();
}

string visit_VarDecl(VarDeclNode node){
    //This will also include the processing of the runtime variables
    allocateVar(
        node.identifier,
        node.var_type,
        node.value.tokens
    );
    //Basically we have returned "" because there is no need to generate any C/C++ var instead that is added to the virtual memory
    // thanks to allocateVar function.
    return "";
}

string visit_VarAssign(VarAssignNode node){
    //It's processing is also not lengthy since we already implemented functions in the runtime core
    assignVar(
        node.identifier,
        node.value.tokens
    );
    return "";
}



#endif // VISITOR_H_CSQ4
