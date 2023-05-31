#if !defined(PARSER_H_CSQ4)
#define PARSER_H_CSQ4
#include "../Runtime/core.h"
#include "../AST/ast.h"

bool VarDecl_check(TokenStream tokens){
    /*Syntax : <identifier> | : <type> = <value>
                            | = <value>
    
    */
    bool valid_state = false;
    if(tokens[0].type == IDENTIFIER){
        if(tokens[1].token == ":"){
            valid_state = 1;
            if(tokens[2].type == IDENTIFIER){
                if(tokens[3].token == "="){
                    if(tokens.size() > 4){}
                    else{
                        RuntimeError("expected a value after =");
                        valid_state = 0;
                    }
                }
                else{
                    RuntimeError("expected a '=' after type");
                    valid_state = 0;
                }   
            }
            else{
                RuntimeError("expected an identifier after ':'.");
                valid_state = 0;
            }
        }
        else if(tokens[1].token == "="){
            if(tokens.size() > 2){valid_state = 1;}
            else{
                RuntimeError("expected a value after =");
                valid_state = 0;
            }
        }
        else{
            RuntimeError("invalid identifier.");
            valid_state = 0;
        }
    }
    return valid_state;
}

//For variable reassignment
bool VarAssign_Check(TokenStream tokens){
    bool valid = 0;
    if(tokens[0].type == IDENTIFIER){
        if(!inTable(tokens[0].token)){
            if(tokens[1].token == "="){
                if(tokens.size() > 2){
                    valid = 1;
                }
                else{
                    RuntimeError("expected a value after =");
                    valid = 0;
                }
            }
            else{
                RuntimeError("invalid token '" + tokens[1].token + "' after an identifier.");
                valid = 0;
            }
        }
        else{
            RuntimeError("identifier '" + tokens[0].token +"'' already defined.");
        }
    }
    return valid;
}


//Parsing without reporting any error because when this function is called before it
//VarDecl_check will be called.
VarDeclNode parse_VarDecl(TokenStream tokens){
    VarDeclNode node;
    //Default type:
    node.var_type = "any";
    //Parsing States
    bool name = 1;
    bool equal = 0;
    bool type = 0;
    bool value = 0;

    //
    for(Token token : tokens){
        if(name)
        {
            node.identifier = token.token;
            name = 0;
        }
        else if(!name && !type && !equal && !value){
            if(token.token == ":"){
                type = 1;
            }
            else if(token.token == "="){
                value = 1;
                equal = 1;
            }
        }
        else if(type){
            if(token.token != "="){
                node.var_type += token.token;
            }else{
                type = 0;
            }
        }
        else if(value){
            node.value.tokens.push_back(token);
        }
    }
    return node;
}
//for var reassignment
VarAssignNode parse_VarAssign(TokenStream tokens){
    VarAssignNode node;
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
            node.value.tokens.push_back(token);
        }
    }
    return node;
}

/*
"Now for Csq, now for the coding and the CsqLang"
Implement the parser
*/

string Parser(){
    string code;
    return code;
};


#endif // PARSER_H_CSQ4
