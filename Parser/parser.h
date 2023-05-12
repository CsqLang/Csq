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


//Parsing functions

Expr ParseExpr(TokenStream tokens, int line){
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
    //States
    bool name = 1;
    bool type = 0;
    bool value = 0;

    for(Token token : tokens){
        if(name)
        {
            if(token.type == IDENTIFIER)
            {
                node.name = token.token;
                name = 0;
            }
            else{
                error(line,"expected an identifier as the name for the variable.");
                name = 0;
            }
        }
        else if(!name && !value && !type)
        {
            if(token.token == ":"){
                type = 1;
            }
            else if(token.token == ":="){
                value = 1;
            }
            else{
                error(line,"invalid syntax : '" + node.name + " " + token.token + "'.");
            }
        }
        else if(type){
            if(token.type == IDENTIFIER)
            {
                //Check whether the type is present in the symbol table or not.
                
            }
        }
    }

    return node;
}

//These functions will be checking which type of the statement is and returns it's nodetype.
bool isVarDecl(TokenStream tokens){
    bool state = 0;
    if(tokens[1].token == ":=" || tokens[1].token == ":"){
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

NODE_TYPE StatementType(TokenStream tokens){
    NODE_TYPE type;
    
    if(isVarDecl(tokens)){
        type = VAR_DECLARATION;
    }
    else if(isVarAssign(tokens)){
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

string Parse(vector<TokenStream> code)
{
    //Load the C written builtins
    load_builtins();
    //Resulting code
    string codeString = "";
    //Scope managers
    int scope = 0;
    int line_no = 1;
    int prev_scope = -1;
    bool is_last_line_if_statement = false;
    //////////////////////////////
    for(TokenStream line : code)
    {
        //Get the current scope by finding indents
        int indent_level = getIndentLevel(line);
        
        //Removing all indentation from the stream
        line = removeIndent(line);

        //The encoding of scope will be helping to distinguish between different scopes 
        //Process : (<parent> * 1000) + <current_scope>
        switch(StatementType(line)){
            
        }
    }
    return codeString;
}


#endif // PARSER_CSQ4
