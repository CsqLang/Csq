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
string Break_visitor(Ptr<Break> node);
string ReturnStmt_visitor(Ptr<ReturnStmt> node);

string VarDecl_visitor(VarDecl node);
string VarAssign_visitor(VarAssign node);
string FuncDecl_visitor(FunctionDecl node);
string IfStmt_visitor(IfStmt node);
string ElifStmt_visitor(ElifStmt node);
string ElseStmt_visitor(ElseStmt node);
string ForLoop_visitor(ForLoop node);
string WhileLoop_visitor(WhileLoop node);
string ClassDecl_visitor(ClassDecl node);
string Block_visitor(Block node);
string Break_visitor(Break node);
string ReturnStmt_visitor(ReturnStmt node);

//Visitor for variable declaration and assignment
string VarDecl_visitor(Ptr<VarDecl> node){
    if(node->type_infr){
        return "VAR " + node->name + " = " + node->value.expr + ";";
    }
    else{
        return node->type_ + " " + node->name + " = " + node->value.expr + ";";
    }
}

string VarAssign_visitor(Ptr<VarAssign> node){
    return node->name + " = " + node->value.expr;
}
string Break_visitor(Ptr<Break> node){
    return "BREAK";
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
    string code = "";
    if(node->return_type_infr == 1)
    {
        string params = "";
        if(node->params.size() > 0){
            for(VarDecl param : node->params)
            if(param.type_infr == 0)
                params += param.type_ + " " + param.name + " = " + param.value.expr + ",";
            else
                params += "VAR " + param.name + " = " + param.value.expr + ",";
            params.pop_back();
        }
        
        code += "FUN " + node->name + "=[&](" + params + ")";
    }
    else
    {
        string params;
        if(node->params.size() > 0){
            for(VarDecl param : node->params)
            if(param.type_infr == 0)
                params += param.type_ + " " + param.name + " = " + param.value.expr + ",";
            else
                params += "VAR " + param.name + " = " + param.value.expr + ",";
            params.pop_back();
        }
        code += node->return_type + " " + node->name + "(" + params + ")";
    }
    return code;
}

string Expr_visitor(Ptr<Expr> node){
    return node->expr;
}

string ReturnStmt_visitor(Ptr<ReturnStmt> node){
    // printf("'%s'\n\n",node->expr.expr.c_str());
    return "RETURN " + node->expr.expr + ";\n";
}

string ClassDecl_visitor(Ptr<ClassDecl> node){
    string code;
    code += "CLASS " + node->name + " ";
    if(node->inherit_class != ""){
        code += " : " + node->inherit_class;
    }
    return code;
}

//Visitor for variable declaration and assignment
string VarDecl_visitor(VarDecl node){
    if(node.type_infr){
        return "VAR " + node.name + " = " + node.value.expr + ";";
    }
    else{
        return node.type_ + " " + node.name + " = " + node.value.expr + ";";
    }
}

string VarAssign_visitor(VarAssign node){
    return node.name + " = " + node.value.expr;
}
string Break_visitor(Break node){
    return "BREAK";
}
//Visitor for blocks
string Block_visitor(Block node){
    string code = "{\n";
    for(string statement : node.statements)
        code += statement + ";\n";
    return code + "}\n";
}

//Visitor for If,Elif and Else statements
string IfStmt_visitor(IfStmt node){
    return "IF(" + node.condition.expr + ")\n";
}
string ElifStmt_visitor(ElifStmt node){
    return "ELIF(" + node.condition.expr + ")\n";
}
string ElseStmt_visitor(ElseStmt node){
    return "ELSE\n";
}

//Visitor for ForLoop and WhileLoop statements
string ForLoop_visitor(ForLoop node){
    return "FOR( VAR " + node.iter_name + " : " + node.condition.expr + ")\n";
}
string WhileLoop_visitor(WhileLoop node){
    return "WHILE(" + node.condition.expr + ")\n";
}

//Visitor for Function declarations.
string FuncDecl_visitor(FunctionDecl node){
    string code = "";
    if(node.return_type_infr == 1)
    {
        string params = "";
        if(node.params.size() > 0){
            for(VarDecl param : node.params)
            if(param.type_infr == 0)
                params += param.type_ + " " + param.name + " = " + param.value.expr + ",";
            else
                params += "VAR " + param.name + " = " + param.value.expr + ",";
            params.pop_back();
        }
        
        code += "FUN " + node.name + "=[&](" + params + ")";
    }
    else
    {
        string params;
        if(node.params.size() > 0){
            for(VarDecl param : node.params)
            if(param.type_infr == 0)
                params += param.type_ + " " + param.name + " = " + param.value.expr + ",";
            else
                params += "VAR " + param.name + " = " + param.value.expr + ",";
            params.pop_back();
        }
        code += node.return_type + " " + node.name + "(" + params + ")";
    }
    return code;
}

string Expr_visitor(Expr node){
    return node.expr;
}

string ReturnStmt_visitor(ReturnStmt node){
    return "RETURN " + node.expr.expr + ";\n";
}

string ClassDecl_visitor(ClassDecl node){
    string code;
    code += "CLASS " + node.name + " ";
    if(node.inherit_class != ""){
        code += " : " + node.inherit_class;
    }
    return code;
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
        case BREAK:{
            Ptr<Break> stmt = static_pointer_cast<Break>(node);
            return Break_visitor(stmt);
        }
        case RETURN_STMT:{
            Ptr<ReturnStmt> stmt = static_pointer_cast<ReturnStmt>(node);
            return ReturnStmt_visitor(stmt);
        } 
        case CLASS_DEFINITION:{
            Ptr<ClassDecl> stmt = static_pointer_cast<ClassDecl>(node);
            return ClassDecl_visitor(stmt);
        }
        default:
            Ptr<Expr> stmt = static_pointer_cast<Expr>(node);
            return Expr_visitor(stmt);
    }
}

#endif // VISITOR_H_CSQ4
