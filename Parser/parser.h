#if !defined(PARSER_CSQ4)
#define PARSER_CSQ4

#include "symbol_table.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//Tokenizer for each line seperation
vector<TokenStream> Tokenizer(string code){
    code += "\n";
    vector<TokenStream> lines;
    string current = "";
    for(char ch : code){
        if(ch != '\n')
            current.push_back(ch);
        else{
            lines.push_back(tokenize(current + ";ignore;"));
            current = "";
        }
    }
    return lines;
}
//All different types of function for parsing down different statements.

Expr ParseExpr(TokenStream tokens, int line, int indent_level, int parent){
    Expr node;

    for(int i = 0;i<tokens.size();i++)
    {
        if(tokens[i].type == IDENTIFIER)
        {
            if(tokens[i+1].token == ".")
            {
                if(tokens[i+2].type == IDENTIFIER)
                {
                    if(MemberPresent(tokens[i].token,tokens[i+2].token,indent_level,parent)){
                        node.expr += tokens[i].token + "." + tokens[i+2].token;
                        i+=2;
                    }
                }
                else{error(line,"expected an identifier.");}
            }  
            else
            {
                node.expr += tokens[i].token + " ";
            }
        }   
        else if(tokens[i].token != ".")
        {
            node.expr += tokens[i].token + " ";
        }
    }

    return node;
}
// All through both ParseExpr and ParseRValue returns same thing but this one is made for variable parsing 
Expr ParseRValue(TokenStream tokens,string lType, int line, int indent_level, int parent){
    Expr node;

    for(int i = 0;i<tokens.size();i++)
    {
        if(tokens[i].type == IDENTIFIER)
        {
            if(isIdentifierDefined(tokens[i].token,(parent*1000)+indent_level)){
                if(tokens[i+1].token == ".")
                {
                    if(tokens[i+2].type == IDENTIFIER)
                    {
                        if(lType == "NONE"){
                            node.expr += tokens[i].token + "." + tokens[i+2].token;
                            i+=2;
                        }
                        else if(MemberPresent(tokens[i].token,tokens[i+2].token,indent_level,parent)){
                            node.expr += tokens[i].token + "." + tokens[i+2].token;
                            i+=2;
                        }
                    }
                    else{error(line,"expected an identifier.");}
                }  
                else
                {
                    node.expr += tokens[i].token + " ";
                }
            }
            else{
                error(line,"undefined identifier '" + tokens[i].token + "'.");
            }
        }   
        else if(tokens[i].token != ".")
        {
            node.expr += tokens[i].token + " ";
        }
    }

    return node;
}

VarDecl ParseVarDecl(TokenStream tokens, int line, int indent_level, int parent){
    VarDecl node;
    TokenStream val_expr;
    //Default type:
    node.type_ = "NONE";
    node.type_infr = 1;
    /*
        Grammar for VarDecl:
        <identifier> : <type> = <value>
        or
        <identifier> = <value>
    */
    //States
    bool name = 1;
    bool type = 0;
    bool value = 0;
    bool error_c = 0;
    
    //Parse:
    for(Token token : tokens){
        if(name){
            //In previous parser code we were using a condition to check whether first token is identifier or not but we don't 
            //need it since it's done by isVarDecl function during checking.
            node.name = token.token;
            name = 0;
        }
        else if(token.token == ":"){
            if(type){
                error(line,"invalid use of : token as a type.");
            }
            else{
                type = 1;
                node.type_ = "";
                node.type_infr = 0;
            }
        }
        else if(type && token.token != "="){
            if(token.token == "<" || token.token == ">" || token.type == IDENTIFIER){
                node.type_ += token.token;
            }
            else{
                error(line,"invalid use of " + token.token + "token as a type.");
            }
        }
        else if(token.token == "="){
            if(type){
                type = 0;
                value = 1;
            }
            else if(value){
                error(line,"invalid use of = as rvalue, did you mean == ?");
            }
        }
        else{
            val_expr.push_back(token);
        }
    }
    //Type checking
    if(node.type_ != "NONE"){
        if(!table.isPresent((parent*1000)+indent_level,node.type_,ST_CLASS)){
            error(line, "undefined type '"+node.type_+"'.");
        }
        else{
            node.value = ParseRValue(val_expr,node.type_,line,indent_level,parent);
        }
    }
    else{
        node.value = ParseRValue(val_expr,"NONE",line,indent_level,parent);
    }
    //Add it to symbol table:

    if(error_c == 0){
        Variable var;
        var.name = node.name;
        var.type = node.type_;
        table.addVariable(parent,indent_level,var);

    }
    return node;
}

VarAssign ParseVarAssign(TokenStream tokens,int line,int parent, int indent){
    VarAssign node;
    TokenStream val_expr;
    Variable var = table.getVariable(tokens[0].token,(parent*1000)+indent);
    //States
    bool name = 1;
    bool value = 0;
    bool error_c = 0;
    for(Token token : tokens){
        if(name){
            if(token.type == IDENTIFIER){
                node.name = token.token;
                name = 0;
            }
            else{
                error(line, "expected an identifier");
                error_c = 1;
            }
        }
        else if(token.token == "=" && !name && !value){
            value = 1;
        }
        else if(value){
            val_expr.push_back(token);
        }
    }
    if(!error_c){
        node.value = ParseRValue(val_expr,var.type,line,indent,parent);
    }
    else{}
    return node;
}
//As Rvalue parser this also returns Expr node but will work particularly for conditions.
Expr ParseCondition(TokenStream tokens, int line, int indent_level, int parent){
    Expr node;
    for(Token token : tokens)
    {
        if(token.type == IDENTIFIER)
        {
            if(isIdentifierDefined(token.token,(parent*1000)+indent_level)){
                node.expr += token.token + " ";
            }
            else{
                error(line,"undefined identifier '" + token.token + "'.");
            }
        }
        else{
            if(token.type != ASOPERATOR){
                node.expr += token.token + " ";
            }
            else{
                error(line,"couldn't use assignment operator as condition.");
            }
        }
    }
    return node;
}

IfStmt ParseIfStmt(TokenStream tokens, int indent, int parent, int line){
    IfStmt node;
    TokenStream condition_expr;
    //States
    bool condition = 0;
    bool end = 0;

    for(Token token : tokens)
    {
        if(token.token == "if")
        {
            if(!condition && !end)
                condition = 1;
            else if(condition)
                error(line, "invalid use of if keyword in condtion.");
            else if(end)
                error(line, "invalid use of if keyword after if statement ends.\nHint:For another if stmt write from newline.");
        }
        else if(token.token == ":"){
            if(condition){
                condition = 0;
                node.condition = ParseCondition(condition_expr,line,indent,parent);
                end = 1;
            }
            else{
                error(line,"unexpected token ':'.");
            }
        }
        else if(condition)
        {
            condition_expr.push_back(token);
        }
    }

    return node;
}

//////////////////////////////////////////////////////////////////
bool isVarDecl(TokenStream tokens, int current_scope){
    bool state = 0;
    if(tokens[0].type == IDENTIFIER && (tokens[1].token == ":" || tokens[1].token == "=") && !table.isVariablePresent(tokens[0].token,current_scope))
     state = 1;
    return state;
}
bool isVarAssign(TokenStream tokens, int current_scope){
    bool state = 0;
    if(tokens[0].type == IDENTIFIER && (tokens[1].token == "=") && table.isVariablePresent(tokens[0].token,current_scope))
     state = 1;
    return state;
}

bool isIfStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "if")
        state = 1;
    return state;
}

bool isElifStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "elif")
        state = 1;
    return state;
}

bool isElseStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "else")
        state = 1;
    return state;
}

NODE_TYPE StatementType(TokenStream tokens, int en_scope){
    NODE_TYPE type;
    
    if(isVarDecl(tokens,en_scope)){
        type = VAR_DECLARATION;
    }
    else if(isVarAssign(tokens,en_scope)){
        type = VAR_ASSIGNMENT;
    }
    else{
        type = EXPR_TYPE;
    }
    return type;
}
int getIndentLevel(TokenStream tokens){
    int indent = 0;
    for(Token token : tokens){
        if(token.type == INDENT)
            indent++;
    }return indent;
}
//Remove all the indentation.
TokenStream removeIndent(TokenStream tokens){
    TokenStream newTokens;
    bool indent = 0;
    if(tokens[0].type == INDENT){
        indent = 1;
    }
    for(Token token : tokens){
        if(token.type == INDENT ){
            
        }
        else if(indent && token.type != INDENT){
            indent = 0;
            newTokens.push_back(token);
        }
        else if(!indent){
            newTokens.push_back(token);
        }
    }
    return newTokens;
}

//Parser
string Parse(vector<TokenStream> code)
{
    //Load the C written builtins
    load_builtins_to_table();
    //Resulting code
    string codeString = "";
    //Scope managers
    int scope = 0;
    int parent = 1;
    int line_no = 1;
    //////////////////////////////
    for(TokenStream line : code)
    {
        //Get the current scope by finding indents
        scope = getIndentLevel(line);
        //Removing all indentation from the stream
        line = removeIndent(line);

        //The encoding of scope will be helping to distinguish between different scopes 
        //Process : (<parent> * 1000) + <current_scope>
        int en_scope = (parent*1000)+scope;
        switch(StatementType(line,en_scope)){
            case VAR_DECLARATION:
            {
                VarDecl node = ParseVarDecl(line,line_no,scope,parent);
                codeString += VarDecl_visitor(node)+"\n";
                line_no++;
                break;
            }
            case VAR_ASSIGNMENT:{
                
                VarAssign node = ParseVarAssign(line,line_no,scope,parent);
                codeString += VarAssign_visitor(node)+"\n";
                line_no++;
            }
            case IF_STATEMENT:{
                
            }
            case EXPR_TYPE:
            {
                Expr node = ParseExpr(line,line_no,scope,parent);
                codeString += Expr_visitor(node)+"\n";
                line_no++;
                break;
            }
        }
    }
    return codeString;
}

#endif // PARSER_CSQ4
