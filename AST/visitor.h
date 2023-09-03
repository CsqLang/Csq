/*This is the implementation for visitor for AST.*/
#if !defined(VISITOR_H_CSQ4)
#define VISITOR_H_CSQ4

#include "../Runtime/core.h"

//
string visit(ASTNode* node);

string visit_ExprNode(ExprNode node){
    string result;
    for(Token token : node.tokens){
        if(token.type == IDENTIFIER){
            result += "id(\"" + token.token + "\")";
        }

        else if(token.type == VALUE){
            result += "f_val(" + token.token + ")";
        }
        else if(token.type == STR){
            token.token.pop_back();
            string tok;
            for(int i = 1; i<token.token.size();i++){
                tok.push_back(token.token[i]);
            }
            result += "s_val(\"" + tok + "\")";
        }
        else{
            result += token.token;
        }
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
    // traverseTokenStream(node.value.tokens);
    return "allocateVar(\"" + node.identifier + "\", \"" + node.var_type + "\", " + visit_ExprNode(node.value) + ");\n";
    return "";
}

string visit_VarAssign(VarAssignNode node){
    // traverseTokenStream(node.value.tokens);
    return "assignVar(\"" + node.identifier + "\", " + visit_ExprNode(node.value) + ");\n";;
}



string visit_PrintNode(PrintNode node){
    string code = "print(";
    code += visit_ExprNode(node.value);
    code += ");";
    return code;
}

string visit_IfNode(IfStmtNode node){
    string code = "if(_cond_(" + visit_ExprNode(node.condition) + ")){\n";
    return code;
}

string visit_ElifNode(ElifStmtNode node){
    string code = "else if(_cond_(" + visit_ExprNode(node.condition) + ")){\n";
    
    return code;
}

string visit_ElseNode(ElseStmtNode node){
    string code = "else{\n";
  
    return code;
}

string visit_WhileNode(WhileStmtNode node){
    string code = "while(_cond_(" + visit_ExprNode(node.condition) + ")){\n";
 
    return code;
}

string visit_CollectionUpdateNode(CollectionUpdateNode node){
    return "assignVar(\"" + node.source + "\", " + visit_ExprNode(node.index) + ".fval, " + visit_ExprNode(node.value) + ");\n";
}

string visit_FunDeclNode(FunDeclNode node){
    string inst = "auto " + node.identifier + "=[&](";
    for(string param : node.parameters)
        if(param != ""){
            inst += "Cell " + param + ",";
        }
    if(inst[inst.size()-1] != '('){
        inst.pop_back();
    }
    inst += "){\n";
    for(string param : node.parameters)
        if(param != ""){
            inst += "allocateVar(\"" + param + "\", \"" + "any" + "\", " + param  + ");\n";
        }
    return inst;
}

string visit_ReturnNode(ReturnNode node){
    return "return " + visit_ExprNode(node.value) + ";\n";
}

string visit_ForNode(ForStmtNode node){
    string res = "allocateVar(\"" + node.iter_name + "\");\n";
    res += "_for_(\"" + node.iter_name+ "\"," + visit_ExprNode(node.condition) + ")\n";
    return res;
}

string curr_path;



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
        case IF_STMT:{
            IfStmtNode stmt = *((IfStmtNode*)node);
            return visit_IfNode(stmt);
        }
        case ELIF_STMT:{
            ElifStmtNode stmt = *((ElifStmtNode*)node);
            return visit_ElifNode(stmt);
        }
        case ELSE_STMT:{
            ElseStmtNode stmt = *((ElseStmtNode*)node);
            return visit_ElseNode(stmt);
        }
        case WHILE_STMT:{
            WhileStmtNode stmt = *((WhileStmtNode*)node);
            return visit_WhileNode(stmt);
        }
        case BLOCK:{
            BlockNode block = *((BlockNode*)node);
            string res_;
            for(ASTNode* node : block.statements){
                res_ += visit(node) + "\n";
            }
            return res_;
        }
    }return "";
}

#endif // VISITOR_H_CSQ4
