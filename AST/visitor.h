/*This is the implementation for visitor for AST.*/
#if !defined(VISITOR_H_CSQ4)
#define VISITOR_H_CSQ4

#include "../Runtime/core.h"

//
string visit(ASTNode* node);

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
    // allocateVar(node.identifier,node.var_type,node.value.tokens);
    //Embedding the function to string to convert it into C/C++ format so that they could execute it.
    string code = "allocateVar(\"" + node.identifier + "\",\"" + node.var_type  + "\",\""+ tokenS_to_string(node.value.tokens) +"\");";
    //Basically we have returned "" because there is no need to generate any C/C++ var instead that is added to the virtual memory
    // thanks to allocateVar function.
    return code;
}

string visit_VarAssign(VarAssignNode node){
    //It's processing is also not lengthy since we already implemented functions in the runtime core
    // assignVar(
    //     node.identifier,
    //     node.value.tokens
    // );
    string code = "assignVar(\"" + node.identifier + "\",\"" + tokenS_to_string(node.value.tokens) +"\");";
    return code;
}

string visit_PrintNode(PrintNode node){
    string code = "print(" + visit_ExprNode(node.value) + ");";
    return code;
}

string visit_IfNode(IfStmtNode node){
    string code = "if(" + visit_ExprNode(node.condition) + "){\n";
    for(ASTNode* stmt : node.body.statements){
        code += visit(stmt) + "\n";
    }
    return code;
}

string visit(ASTNode* node){
    switch(node->type){
        case VAR_DECL:{
            VarDeclNode decl = *((VarDeclNode*)node);
            return visit_VarDecl(decl);
        }
        case VAR_ASSIGN:{
            VarAssignNode decl = *((VarAssignNode*)node);
            return visit_VarAssign(decl);
        }
        case PRINT:{
            PrintNode prt = *((PrintNode*)node);
            return visit_PrintNode(prt);
        }
    }return "";
}

#endif // VISITOR_H_CSQ4
