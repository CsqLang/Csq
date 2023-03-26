/*This is the implementation for visitor for AST.*/
#if !defined(VISITOR_H_CSQ4)
#define VISITOR_H_CSQ4

#include "ast.h"


string VarDecl_visitor(Ptr<VarDecl> node);
string VarAssign_visitor(Ptr<VarAssign> node);
string FuncDecl_visitor(Ptr<FunctionDecl> node);
string IfStmt_visitor(Ptr<IfStmt> node);
string ElifStmt_visitor(Ptr<ElifStmt> node);
string ElseStmt_visitor(Ptr<ElseStmt> node);
string ForLoop_visitor(Ptr<ForLoop> node);
string WhileLoop_visitor(Ptr<WhileLoop> node);
string ClassDecl_visitor(Ptr<ClassDecl> node);
string Block_visitor(Ptr<Block> node);

//Visitor for variable declaration and assignment
string VarDecl_visitor(Ptr<VarDecl> node){
    return "VAR " + node->name + " = " + node->value.expr;
}
string VarAssign_visitor(Ptr<VarAssign> node){
    return node->name + " = " + node->value.expr;
}

//Visitor for blocks
string Block_visitor(Ptr<Block> node){
    string code = "{\n";
    for(string statement : node->statements)
        code += statement + ";\n";
    return code + "}\n";
}

//Visitor for If,Elif and Else statements
string IfStmt_visitor(Ptr<IfStmt> node){
    return "IF(" + node->condition.expr + ")\n";
}
string ElifStmt_visitor(Ptr<ElifStmt> node){
    return "ELIF(" + node->condition.expr + ")\n";
}
string ElseStmt_visitor(Ptr<ElseStmt> node){
    return "ELSE\n";
}

//Visitor for ForLoop and WhileLoop statements
string ForLoop_visitor(Ptr<ForLoop> node){
    return "FOR( VAR " + node->iter_name + " : " + node->condition.expr + ")\n";
}
string WhileLoop_visitor(Ptr<WhileLoop> node){
    return "WHILE(" + node->condition.expr + ")\n";
}

//Visitor for Function declarations.
string FuncDecl_visitor(Ptr<FunctionDecl> node){
    string params;
    if(node->params.size()>0 && node->params[0]!=""){
        for(string param : node->params){
            params += "ParamType " + param + ", ";
        }
        params.pop_back();
        params.pop_back();
    }
    shared_ptr<Block> block = make_shared<Block>();
    for(string statement : node->body.statements)
        addStatement(block,statement);
    return "template<typename ParamType>\nFUN " + node->name + " ( " + params + ")\n";
}

//Definition for visit function 
string visit(const Ptr<Node>& node) {
    switch (node->type) {
        case VAR_DECLARATION: {
            Ptr<VarDecl> var = static_pointer_cast<VarDecl>(node);
            return VarDecl_visitor(var);
        }
        case VAR_ASSIGNMENT: {
            Ptr<VarAssign> var = static_pointer_cast<VarAssign>(node);
            return VarAssign_visitor(var);
        }
        case BLOCK:{
            Ptr<Block> block = static_pointer_cast<Block>(node);
            return Block_visitor(block);
        }
        case FUNCTION_DECL:{
            Ptr<FunctionDecl> fun = static_pointer_cast<FunctionDecl>(node);
            return FuncDecl_visitor(fun);
        }
        case FOR_LOOP:{
            Ptr<ForLoop> floop = static_pointer_cast<ForLoop>(node);
            return ForLoop_visitor(floop);
        }
        case WHILE_LOOP:{
            Ptr<WhileLoop> stmt = static_pointer_cast<WhileLoop>(node);
            return WhileLoop_visitor(stmt);
        }
        case IF_STATEMENT:{
            Ptr<IfStmt> stmt = static_pointer_cast<IfStmt>(node);
            return IfStmt_visitor(stmt);
        }
        case ELIF_STATEMENT:{
            Ptr<ElifStmt> stmt = static_pointer_cast<ElifStmt>(node);
            return ElifStmt_visitor(stmt);
        }
        case ELSE_STATEMENT:{
            Ptr<ElseStmt> stmt = static_pointer_cast<ElseStmt>(node);
            return ElseStmt_visitor(stmt);
        }
        default:
            Ptr<Expr> stmt = static_pointer_cast<Expr>(node);
            return stmt->expr;
    }
}


#endif // VISITOR_H_CSQ4
