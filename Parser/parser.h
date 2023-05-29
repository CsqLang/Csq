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

/*
"Now for Csq, now for the coding and the CsqLang"
Implement the parser
*/

string Parser(){
    string code;
    return code;
};


#endif // PARSER_H_CSQ4
