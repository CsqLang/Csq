#if !defined(PARSER_H_CSQ4)
#define PARSER_H_CSQ4
#include "../Runtime/core.h"
#include "../AST/ast.h"
#include "../AST/visitor.h"



/*
Upper layer syntax checking in which we don't have to do much instead it will roughly match the 
syntax and returns the possible type which could be futher verified.
*/
bool VarDecl_check(TokenStream tokens){
    /*Syntax : <identifier> | :=<value>
    
    */
    bool valid_state = false;
    if(tokens[0].type == IDENTIFIER)
    {
        if(tokens[1].token == ":=")
        {
            if(tokens.size()>2)
            {
                valid_state = 1;
                for(int i = 2;i<tokens.size();i++){
                    if(tokens[i].type == KEYWORD){
                        RuntimeError("syntax error by using keyword '" + tokens[i].token + "' inside a value.");
                        valid_state = 0;
                    }
                    else if(tokens[i].token == "="){
                        RuntimeError("syntax error by using '" + tokens[i].token + "' inside a value.");
                        valid_state = 0;
                    }
                }
            }
            else{
                RuntimeError("expected a value after ':='.");
                valid_state = 0;
            }
        }
    }
    return valid_state;
}

//For variable reassignment
bool VarAssign_Check(TokenStream tokens){
    bool valid = 0;
    if(tokens[0].type == IDENTIFIER)
    {
        if(tokens[1].token == "="){
            if(tokens.size()>2){
                valid = 1;
            }
            else{
                RuntimeError("expected a value after '='.");
                valid = 0;
            }
        }
    }
    return valid;
}

//Function to parse expressions and report the errors.
ExprNode parse_ExprNode(TokenStream tokens){
    ExprNode node;

    for(int i = 0;i<tokens.size();i++)
    {   
        Token token = tokens[i];
        if(token.type == IDENTIFIER)
        {
            //Check is the identifier defined in table?
            if(inTable(token.token))
            {
                Token val;
                if(memory[SymTable[token.token].var.value_address].type == FLOAT){
                    val.token = to_string(memory[SymTable[token.token].var.value_address].fval);
                    val.type = VALUE;
                }
                else{
                    val.token = memory[SymTable[token.token].var.value_address].sval;
                    val.type = STR;
                }
                node.tokens.push_back(val);
            }
            else
            {
                RuntimeError("undefined name '" + token.token + "'.");
            }
        }
        else if(token.type == VALUE){
            if(tokens.size() != i+1){
                if(tokens[i+1].token == "."){
                    Token val;
                    val.type = VALUE;
                    val.token = token.token + "." + tokens[i+2].token;
                    node.tokens.push_back(val);
                    i = i+2;
                }
                else{
                    node.tokens.push_back(token);    
                }
            }
            else{
                node.tokens.push_back(token);   
            }
        }
        else{
            //Just for now couldn't be used during actual production.
            node.tokens.push_back(token);
        }
    }
    return node;
}

//Parsing without reporting any error because when this function is called before it
//VarDecl_check will be called.
VarDeclNode parse_VarDecl(TokenStream tokens){
    VarDeclNode node;
    //Default type:
    node.var_type = "any";
    //lower level rep for value (in terms of tokens)
    TokenStream valstream;
    //Parsing States
    bool name = 1;
    bool equal = 0;
    bool value = 0;

    //
    for(Token token : tokens){
        if(name)
        {
            node.identifier = token.token;
            name = 0;
        }
        else if(!equal && token.token == ":="){
            value = 1;
            equal = 1;
        }
        else if(equal){
            valstream.push_back(token);
        }
    }

    node.value = parse_ExprNode(valstream);
    
    return node;
}
//for var reassignment
VarAssignNode parse_VarAssign(TokenStream tokens){
    VarAssignNode node;
    TokenStream valstream;
    //States
    bool name = 1;
    bool val = 0;
    
    for(Token token : tokens){
        if(name){
            node.identifier = token.token;
            name = 0;
            
        }
        else if(!val && token.token == "="){
            val = 1;
        }
        else if(val){
            valstream.push_back(token);
        }
    }
    node.value = parse_ExprNode(valstream);
    return node;
}

PrintNode parse_PrintStatement(TokenStream tokens){
    PrintNode node;
    for(int i = 1;i<tokens.size();i++){
        node.value.tokens.push_back(tokens[i]);
        
    }
    return node;
}

IfStmtNode parse_IfStmt(TokenStream tokens){
    IfStmtNode node;
    //states
    bool condition = 0;
    // bool end = 0;
    for(Token token : tokens){
        if(token.token == "if")
            condition = 1;
        else
            if(token.token != ":")
                node.condition.tokens.push_back(token);
            else
                break;
    }
    return node;
}
ElifStmtNode parse_ElifStmt(TokenStream tokens){
    ElifStmtNode node;
    //states
    bool condition = 0;
    // bool end = 0;
    for(Token token : tokens){
        if(token.token == "elif")
            condition = 1;
        else
            if(token.token != ":")
                node.condition.tokens.push_back(token);
            else
                break;
    }
    return node;
}
ElseStmtNode parse_ElseStmt(TokenStream tokens){
    ElseStmtNode node;
    return node;
}

ForStmtNode parse_ForStmt(TokenStream tokens){
    ForStmtNode node;

    // node.

    return node;
}

WhileStmtNode parse_WhileStmt(TokenStream tokens){
    WhileStmtNode node;

    for(int i = 1;i<tokens.size();i++)
        if(!(tokens[i].token == ":"))
            node.condition.tokens.push_back(tokens[i]);
        else
            break;

    return node;
}

bool isVarDecl(TokenStream tokens){
    if(tokens[0].type == IDENTIFIER && tokens[1].token == ":="){
        return 1;
    }return 0;
}

bool isPrintStmt(TokenStream tokens){
    if(tokens[0].token == "print"){
        return 1;
    }return 0;
}

bool isTypeStmt(TokenStream tokens){
    if(tokens[0].token == "type"){
        return 1;
    }return 0;
}


bool isVarAssign(TokenStream tokens){
    if(tokens[0].type == IDENTIFIER && tokens[1].token == "="){
        return 1;
    }return 0;
}

bool isIfStmt(TokenStream tokens){
    if(tokens[0].token == "if"){
        return 1;
    }
    return 0;
}

bool isElifStmt(TokenStream tokens){
    if(tokens[0].token == "elif"){
        return 1;
    }
    return 0;
}

bool isElseStmt(TokenStream tokens){
    if(tokens[0].token == "else"){
        return 1;
    }
    return 0;
}

bool isWhileStmt(TokenStream tokens){
    if(tokens[0].token == "while"){
        return 1;
    }
    return 0;
}

NodeType StatementType(TokenStream tokens){
    NodeType type;
    
    if(isVarDecl(tokens)){
        type = VAR_DECL;
    }
    else if(isVarAssign(tokens)){
        type = VAR_ASSIGN;
    }
    else if(isIfStmt(tokens)){
        type = IF_STMT;
    }
    else if(isPrintStmt(tokens)){
        type = PRINT;
    }
    else if(isElifStmt(tokens)){
        type = ELIF_STMT;
    }
    else if(isElseStmt(tokens)){
        type = ELSE_STMT;
    }
    else if(isWhileStmt(tokens)){
        type = WHILE_STMT;
    }
    else{
        type = EXPR;
    }
    return type;
}

struct CodeBlock{
    vector<ASTNode> nodes;
};

TokenStream removeIndent(TokenStream tokens){
    TokenStream tok;
    for(Token token: tokens){
        if(token.type == INDENT){}
        else{
            tok.push_back(token);
        }
    }return tok;
}

//Scope for the statements
struct Scope{
    int indent_level;
    bool ended;
    NodeType of;
    Scope(){}
    Scope(int level, NodeType of_, bool ended_){
        indent_level = level;
        of = of_;
        ended = ended_;
    };
};


 //Returns the last scope present in the given scope vector.
Scope last_scope(vector<Scope> scope){
    return scope[scope.size()-1];
}


string Compile(vector<TokenStream> code)
{
    //Resulting code
    string codeString = "";

    //Scope properties
    int line_no = 1;
    Scope scope(0,UNKNOWN_NODE,0);
    vector<Scope> scope_stack = {scope};


    //States
    bool class_ = 0;
    int last_indent = 0;    
    //Last statement type
    NodeType last_statement = UNKNOWN_NODE;
    for(TokenStream line : code)
    {
        //Get the current scope by finding indents
        int indent_level = getIndentLevel(line);
     
        //Work with the indentation levels
        while(indent_level != last_scope(scope_stack).indent_level){
            if(last_scope(scope_stack).of == FUN_DECL){
                codeString += "};\n";
                scope_stack.pop_back(); 
   
            }
            else{
                codeString += "}\n";
                //Pop the previous scope since it's now closed.
                scope_stack.pop_back(); 
            }
        }

        //Removing all indentation from the stream
        line = removeIndent(line);

        switch(StatementType(line)){
            case VAR_DECL:{
                VarDeclNode node = parse_VarDecl(line);
                codeString += visit_VarDecl(node);
                break;
            }
            case VAR_ASSIGN:{
                VarAssignNode node = parse_VarAssign(line);
                codeString += visit_VarAssign(node);
                break;
            }
            case IF_STMT:{
                
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                IfStmtNode node = parse_IfStmt(line);
                codeString += visit_IfNode(node) + "\n";
                break;
            }
            case ELIF_STMT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                ElifStmtNode node = parse_ElifStmt(line);
                codeString += visit_ElifNode(node) + "\n";
                break;
            }
            case ELSE_STMT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                ElseStmtNode node = parse_ElseStmt(line);
                codeString += visit_ElseNode(node) + "\n";
                break;
            }
            case PRINT:{
                PrintNode node = parse_PrintStatement(line);
                codeString += visit_PrintNode(node) + "\n";
                break;
            }

            case WHILE_STMT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                WhileStmtNode node = parse_WhileStmt(line);
                codeString += visit_WhileNode(node) + "\n";
                break;
            }
   
        }
        line_no++;
    }
    return codeString;
}

#endif // PARSER_H_CSQ4
