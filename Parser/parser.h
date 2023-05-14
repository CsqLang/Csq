#if !defined(PARSER_CSQ4)
#define PARSER_CSQ4

#include "symbol_table.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//Scope for the statements
struct Scope{
    int indent_level;
    bool ended;
    NODE_TYPE of;
    Scope(){}
    Scope(int level, NODE_TYPE of_, bool ended_){
        indent_level = level;
        of = of_;
        ended = ended_;
    };
};
 //Returns the last scope present in the given scope vector.
Scope last_scope(vector<Scope> scope){
    return scope[scope.size()-1];
}

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

///////////////////////
//Testing kit
#define printsize(vect) printf("%ld\n",vect.size())
#define printi(x) printf("%d\n",x)


//Parsing functions

Expr ParseExpr(TokenStream tokens, int line){
    Expr node;
    for(Token token : tokens){
        if(token.type == IDENTIFIER){
            if(!table.isIdentifierDefined(token.token)){
                error(line,"undefined identifier '" + token.token + "'.");
            }
            else{
                node.expr += token.token + " ";
            }
        }
        else{
            node.expr += token.token + " ";
        }
    }        
    return node;
}

Expr ParseRValue(TokenStream tokens, int line){
    Expr node;
    Token last;
    for(Token token : tokens){
        if(token.type == IDENTIFIER){
            //Check is it defined?
            if(table.isIdentifierDefined(token.token))
            {
                node.expr += token.token + " ";
            }
            else{
                error(line,"undefined identifier '" + token.token + "' used.");
            }
            last = token;
        }
        else{
            if(last.token == token.token){
                error(line, "invalid syntax '" + last.token + " " + token.token + ".");
            }
            else{
                node.expr += token.token + " ";
            }
            last = token;
        }
    }
    return node;
}

VarDecl ParseVarDecl(TokenStream tokens, int line){
    VarDecl node;
    TokenStream val_expr;
    node.type_ = "NONE";
    //States
    bool name = 1;
    bool type = 0;
    bool value = 0;
    bool error_c = 0;
    for(Token token : tokens){
        if(name)
        {
            if(token.type == IDENTIFIER)
            {
                node.name = token.token;
                name = 0;
            }
            else{
                error(line,"expected an identifier but got '" + token.token + "'.");
                error_c = 1;
                name = 0;
            }
        }
        else if(!name && !value && !type)
        {
            if(token.token == ":"){
                type = 1;
                node.type_ = "";
                node.type_infr = 0;
            }
            else if(token.token == ":="){
                value = 1;
            }
            else{
                error(line,"invalid syntax : '" + node.name + " " + token.token + "'.");
                error_c = 1;
                type = 0;
                value = 1;
            }
        }
        else if(type && token.token != "="){
            if(token.type == IDENTIFIER)
            {
                node.type_ += token.token;
            }
            else if(token.token == ">" || token.token == "<"){
                node.type_ += token.token;
            }
            else{
                error(line,"invalid token '"+token.token + "' used as a type.");
                error_c = 1;
            }
        }
        else if(token.token == "=" && type){
            type = 0;
            if(table.isClassDefined(node.type_))
            {
                value = 1;
            }
            else
            {
                error(line,"undefined type '" + node.type_ + "'.");
                error_c = 1;
            }
        }
        else if(value){
            val_expr.push_back(token);
        }
    }

    node.value = ParseRValue(val_expr,line);
    Variable var;
    var.name = node.name;
    var.type = node.type_;
    table.addVariable(node.name, var);
    if(node.type_ == "NONE"){
        node.type_infr = 1;
    }
    else{
        node.type_infr = 0;
    }
    return node;
}

VarAssign ParseVarAssign(TokenStream tokens, int line){
    VarAssign node;
    bool name = 1;
    bool value = 0;
    TokenStream val_expr;

    for(Token token : tokens){
        if(name){
            if(token.type == IDENTIFIER){
                node.name = token.token;
                name = 0;
            }
            else{
                error(line,"expected an identifier.");
            }
        }
        else if(!value && !name && token.token == "="){
            value = 1;
        }
        else if(value){
            val_expr.push_back(token);
        }
    }
    node.value = ParseRValue(val_expr,line);
    return node;
}

Expr ParseCondition(TokenStream tokens, int line){
    Expr node;
    for(Token token : tokens){
        if(token.type == IDENTIFIER){
            //Check is it defined?
            if(table.isIdentifierDefined(token.token))
            {
                node.expr += token.token + " ";
            }
            else{
                error(line,"undefined identifier '" + token.token + "' used.");
            }
        }
        else{
            if(token.token != ":=")
            {
                node.expr += token.token + " ";
            }
            else{
                error(line,"invalid assignment operator := in condition.");
            }
        }
    }
    return node;
}

IfStmt ParseIfStmt(TokenStream tokens, int line){
    IfStmt node;
    TokenStream condition_expr;
    bool condition = 0;
    bool end = 0;
    //
    for(Token token : tokens){
        if(!condition && !end && token.token == "if"){
                condition = 1;
        }
        else if(condition && token.token != ":"){
            condition_expr.push_back(token);
        }
        else if(condition && token.token == ":"){
            end = 1;
            condition = 0;
            node.condition = ParseCondition(condition_expr,line);
        }
        else if(end){
            error(line,"invalid token after the end of if stmt '" + token.token + "'.");
        }
    }
    //
    return node;
}

ElifStmt ParseElifStmt(TokenStream tokens, int line){
    ElifStmt node;
    TokenStream condition_expr;
    bool condition = 0;
    bool end = 0;
    //
    for(Token token : tokens){
        if(!condition && !end && token.token == "elif"){
                condition = 1;
        }
        else if(condition && token.token != ":"){
            condition_expr.push_back(token);
        }
        else if(condition && token.token == ":"){
            end = 1;
            condition = 0;
            node.condition = ParseCondition(condition_expr,line);
        }
        else if(end){
            error(line,"invalid token after the end of elif stmt '" + token.token + "'.");
        }
    }
    //
    return node;
}

ElseStmt ParseElseStmt(TokenStream tokens, int line){
    ElseStmt node;
    if(tokens[1].token != ":"){
        error(line, "expected a : after else.");
    }
    return node;
}

ForLoop ParseForLoop(TokenStream tokens, int line){
    ForLoop node;
    TokenStream expr;
    //States
    bool iter = 0;
    bool expr_ = 0;
    bool end = 0;

    //Parse
    for(Token token : tokens){
        if(token.token == "for"){
            if(!iter && !expr_ && !end){
                iter = 1;
            }
            else{
                error(line,"invalid use of for keyword.");
            }
        }
        else if(iter){
            if(token.type == IDENTIFIER){
                node.iter_name += token.token;
                Variable var;
                var.name = node.iter_name;
                table.addVariable(var.name,var);
                iter = 0;
            }
            else{
                error(line,"expected an identifier.");
            }
        }
        else if(token.token == "in"){
            if(!expr_ && !end){
                expr_ = 1;
            }
            else{
                error(line,"invalid use of in keyword.");
            }
        }
        else if(expr_ && token.token != ":"){
            expr.push_back(token);
        }
        else if(token.token == ":" && expr_){
            node.condition = ParseExpr(expr,line);
            break;
        }   
    }
    return node;
}

WhileLoop ParseWhileLoop(TokenStream tokens, int line){
    WhileLoop node;
    TokenStream condition;
    //States
    bool condition_ = 0;
    bool end = 0;

    for(Token token : tokens){
        if(token.token == "while")
        {
            if(condition_ || end){error(line,"unexpected while keyword inside the while statement");}
            else{
                condition_ = 1;
            }
        }
        else if(condition_ && token.token != ":"){
            condition.push_back(token);
        }   
        else if(condition_ && token.token == ":"){
            end = 1;
            node.condition = ParseCondition(condition,line);
        }
        else if(end){
            error(line, "invalid token '" + token.token + "' after end of");
        }
    }
    return node;
}

FunctionDecl ParseFunction(TokenStream tokens, int line){
    FunctionDecl node;
    //States
    bool name = 0;
    bool param = 0;
    bool type;
    bool end = 0;
    node.return_type_infr = 1;
    TokenStream param_;
    for(Token token : tokens)
    {
        if(token.token == "def"){
            if(!name && !param && !end){
                name = 1;
            }
            else{
                error(line,"invalid def keyword in function.");
            }
        }
        else if(name && token.token != "("){
            if(token.type == IDENTIFIER){
                node.name = token.token;
                name = 0;
            }
            else{
                error(line,"expected an identifier.");
            }
        }
        else if(!name && token.token == "(" && !param){
            param = 1;
        }
        else if(param){
            if(token.token != "," && token.token != ")"){
                param_.push_back(token);
            }
            else if(token.token == ","){
                node.params.push_back(ParseVarDecl(param_,line));
            }
            else if(token.token == ")"){
                if(param_.size()>0){
                    node.params.push_back(ParseVarDecl(param_,line));
                    param = 0;
                }
                else{param = 0;}
            }
        }
        else if(!end && !param && !type && token.token == ":"){
            end=  1;
            break;
        }
        else if(!param && token.token == "->"){
            type = 1;
            node.return_type_infr = 0;
        }
        else if(type && token.token != ":")
        {
            if(token.type == IDENTIFIER || token.token == "<" || token.token == ">"){
                node.return_type += token.token;
            }
            else{
                error(line,"expected a valid token for type.");
            }
        }
    }

    Function fun;
    fun.name = node.name;
    table.fnStack.push_back(node.name);
    table.addFunction(fun.name,fun);
    return node;
}

ClassDecl ParseClass(TokenStream tokens, int line){
    ClassDecl node;
    //States
    bool name = 0;
    bool inherit_class = 0;
    bool end = 0;

    for(Token token : tokens)
    {
        if(token.token == "class")
        {
            if(!name && !end){
                name  = 1;
            }
            else{
                error(line,"invalid class keyword.");
            }
        }
        else if(name && token.token != ":"){
            if(token.type == IDENTIFIER)
            {
                if(!table.isIdentifierDefined(token.token)){
                    node.name = token.token;
                    name = 0;
                }
                else{
                    error(line, "'" + token.token + "' is already defined use another name.");
                }
            }
            else{
                error(line,"expected an identifier.");
            }
        }
        else if(name && token.token == ":"){
            end = 1;
            break;
        }
    }
    Class c;
    c.name = node.name;
    table.addClass(node.name, c);
    return node;
}

//These functions will be checking which type of the statement is and returns it's nodetype.
bool isVarDecl(TokenStream tokens){
    bool state = 0;
    if(tokens[1].token == ":=" ||( tokens[1].token == ":" && tokens[0].token != "else")){
        state = 1;
    }
    return state;
}

bool isVarAssign(TokenStream tokens){
    bool state = 0;
    if(tokens[1].token == "="){
        state = 1;
    }
    return state;
}

bool isForLoop(TokenStream tokens){
    if(tokens[0].token == "for"){
        return 1;
    }
    else{
        return 0;
    }
}

bool isWhileLoop(TokenStream tokens){
    if(tokens[0].token == "while"){
        return 1;
    }
    else{
        return 0;
    }
}

bool isFunctionDef(TokenStream tokens){
    if(tokens[0].token == "def"){
        return 1;
    }
    else{
        return 0;
    }
}

bool isClass(TokenStream tokens){
    if(tokens[0].token == "class"){
        return 1;
    }
    else{
        return 0;
    }
}

bool isIfStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "if"){
        state = 1;
    }
    return state;
}

bool isElifStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "elif"){
        state = 1;
    }
    return state;
}
bool isElseStmt(TokenStream tokens){
    bool state = 0;
    if(tokens[0].token == "else"){
        state = 1;
    }
    return state;
}

NODE_TYPE StatementType(TokenStream tokens){
    NODE_TYPE type;
    
    if(isVarDecl(tokens)){
        type = VAR_DECLARATION;
    }
    else if(isVarAssign(tokens)){
        type = VAR_ASSIGNMENT;
    }
    else if(isIfStmt(tokens)){
        type = IF_STATEMENT;
    }
    else if(isElifStmt(tokens)){
        type = ELIF_STATEMENT;
    }
    else if(isElseStmt(tokens)){
        type = ELSE_STATEMENT;
    }
    else if(isForLoop(tokens)){
        type = FOR_LOOP;
    }
    else if(isWhileLoop(tokens)){
        type = WHILE_LOOP;
    }
    else if(isFunctionDef(tokens)){
        type = FUNCTION_DECL;
    }
    else if(isClass(tokens)){
        type = CLASS_DEFINITION;
    }
    else{
        type = EXPR_TYPE;
    }
    return type;
}
bool isBlockStatement(NODE_TYPE type){
    bool state = 0;
    if(
        type == IF_STATEMENT || type == ELSE_STATEMENT || type == ELIF_STATEMENT ||
        type == FUNCTION_DECL || type == CLASS_DEFINITION || type == FOR_LOOP || type == WHILE_LOOP
    ){state = 1;}
    return state;
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
    load_builtins();

    //Add a ignore statement at last so that indentations can work correctly
    code.push_back(TokenStream({tokenize(string("ignore") + ";ignore;")}));

    //Resulting code
    string codeString = "";

    //Scope properties
    int line_no = 1;
    Scope scope(0,PROGRAM,0);
    vector<Scope> scope_stack = {scope};


    //States
    bool class_ = 0;
    int last_indent = 0;    
    //Last statement type
    NODE_TYPE last_statement = PROGRAM;
    for(TokenStream line : code)
    {
        //Get the current scope by finding indents
        int indent_level = getIndentLevel(line);
     
        //Work with the indentation levels
        while(indent_level != last_scope(scope_stack).indent_level){
            if(last_scope(scope_stack).of == FUNCTION_DECL || last_scope(scope_stack).of == CLASS_DEFINITION){
                codeString += "};\n";
                scope_stack.pop_back(); 
                if(last_scope(scope_stack).of == CLASS_DEFINITION){
                    class_ = 0;
                }
            }
            else{
                codeString += "}\n";
                //Pop the previous scope since it's now closed.
                scope_stack.pop_back(); 
            }
        }

        //Removing all indentation from the stream
        line = removeIndent(line);

        line.pop_back();
        line.pop_back();
        line.pop_back();
        //The encoding of scope will be helping to distinguish between different scopes 
        //Process : (<parent> * 1000) + <current_scope>
        switch(StatementType(line)){
            case VAR_DECLARATION:{
                VarDecl node = ParseVarDecl(line,line_no);
                codeString += VarDecl_visitor(node) + ";\n";
                break;
            }
            case VAR_ASSIGNMENT:{
                VarAssign node = ParseVarAssign(line,line_no);
                codeString += VarAssign_visitor(node) + ";\n";
                break;
            }
            case IF_STATEMENT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                IfStmt node = ParseIfStmt(line,line_no);
                codeString += IfStmt_visitor(node) + "{\n";
                break;
            }
            case ELIF_STATEMENT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                ElifStmt node = ParseElifStmt(line,line_no);
                codeString += ElifStmt_visitor(node) + "{\n";
                break;
            }
            case ELSE_STATEMENT:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                ElseStmt node = ParseElseStmt(line,line_no);
                codeString += ElseStmt_visitor(node) + "{\n";
                break;
            }
            case FOR_LOOP:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                ForLoop node = ParseForLoop(line,line_no);
                codeString += ForLoop_visitor(node) + "{\n";
                break;
            }
            case WHILE_LOOP:{
                scope_stack.push_back(Scope(indent_level+1, StatementType(line), 0));
                WhileLoop node = ParseWhileLoop(line, line_no);
                codeString += WhileLoop_visitor(node) + "{\n";
                break;
            }
            case FUNCTION_DECL:{
                scope_stack.push_back(Scope(indent_level+1, FUNCTION_DECL, 0));
                FunctionDecl node = ParseFunction(line,line_no);
                codeString += FuncDecl_visitor(node) + "{\n";
                break;
            }
            case CLASS_DEFINITION:{
                scope_stack.push_back(Scope(indent_level+1, CLASS_DEFINITION, 0));
                ClassDecl node = ParseClass(line,line_no);
                codeString += ClassDecl_visitor(node) + "{\npublic:\n";
                break;
            }
            case EXPR_TYPE:{
                Expr node = ParseExpr(line,line_no);
                codeString +=node.expr + ";\n";
                break;
            }
        }
        line_no++;
    }
    return codeString;
}


#endif // PARSER_CSQ4
