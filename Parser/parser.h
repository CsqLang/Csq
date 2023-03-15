#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    //Tools required for parsing

    /*Exceptions required for parsing and finding out the mistakes earlier.*/

    /*
        Check tokens.
    */
    bool parenthesisPresent(TokenStream tokens){
        StringStream strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("(", strtokens) || in(")", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool squareBracPresent(TokenStream tokens){
        StringStream strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("[", strtokens) || in("]", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool curlyBracesPresent(TokenStream tokens){
        StringStream strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("{", strtokens) || in("}", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool isVarDecl(TokenStream tokens){
        bool state = false;
        if(tokens[0].type == IDENTIFIER && tokens[1].type == ASOPERATOR && tokens[2].type != ASOPERATOR && in(tokens[0].token,Variables) == 0)
            state = true;
        return state;
    }

    bool isVarAssign(TokenStream tokens){
        bool state = false;
        if(tokens[0].type == IDENTIFIER && tokens[1].type == ASOPERATOR && tokens[2].type != ASOPERATOR && in(tokens[0].token,Variables) == 1)
            state = true;
        return state;
    }       
#endif // PARSEr_H_CSQ4
