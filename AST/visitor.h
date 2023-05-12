/*This is the implementation for visitor for AST.*/
#if !defined(VISITOR_H_CSQ4)
#define VISITOR_H_CSQ4

#include "ast.h"

// string VarDecl_visitor(Ptr<VarDecl> node);
// string VarAssign_visitor(Ptr<VarAssign> node);
// string FuncDecl_visitor(Ptr<FunctionDecl> node);
// string IfStmt_visitor(Ptr<IfStmt> node);
// string ElifStmt_visitor(Ptr<ElifStmt> node);
// string ElseStmt_visitor(Ptr<ElseStmt> node);
// string ForLoop_visitor(Ptr<ForLoop> node);
// string WhileLoop_visitor(Ptr<WhileLoop> node);
// string ClassDecl_visitor(Ptr<ClassDecl> node);
// string Block_visitor(Ptr<Block> node);
// string Break_visitor(Ptr<Break> node);
// string ReturnStmt_visitor(Ptr<ReturnStmt> node);

string VarDecl_visitor(VarDecl node);
string VarAssign_visitor(VarAssign node);
string FuncDecl_visitor(FunctionDecl node);
string IfStmt_visitor(IfStmt node);
string Expr_visitor(Expr node);
string ElifStmt_visitor(ElifStmt node);
string ElseStmt_visitor(ElseStmt node);
string ForLoop_visitor(ForLoop node);
string WhileLoop_visitor(WhileLoop node);
string ClassDecl_visitor(ClassDecl node);
string Block_visitor(Block node);
string Break_visitor(Break node);
string ReturnStmt_visitor(ReturnStmt node);

//Visitor for variable declaration and assignment
string VarDecl_visitor(VarDecl node){
    if(node.type_infr){
        return "VAR " + node.name + " = " + node.value.expr;
    }
    else{
        return node.type_ + " " + node.name + " = " + node.value.expr;
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

#endif // VISITOR_H_CSQ4
