#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    int error_count = 0;

    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    //Tools required for parsing

    /*Exceptions required for parsing and finding out the mistakes earlier.*/
    void ParenthesisNotClosed(int line){
        printf("At line : %d, parenthesis aren't properly closed.",line);
        error_count++;
    }
    void CurlyBraceNotClosed(int line){
        printf("At line : %d, curly brackets aren't properly closed.",line);
        error_count++;
    }
    void SquareBracNotClosed(int line){
        printf("At line : %d, square brackets aren't properly closed.",line);
        error_count++;
    }
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

    bool isParenClosed(TokenStream tokens){
        bool state = false;
        int lparencount = 0;
        int rparencount = 0;
        for(Token token : tokens){
            if(token.type == SYMBOL && token.token == "(")
                lparencount++;
            else if(token.type == SYMBOL && token.token == ")")
                rparencount++;
            else
                ignore;
        }
        if(lparencount == rparencount)
            state = true;
        return state;
    }

    bool isBracketClosed(TokenStream tokens){
        bool state = false;
        int lbraccount = 0;
        int rbraccount = 0;
        for(Token token : tokens){
            if(token.type == SYMBOL && token.token == "[")
                lbraccount++;
            else if(token.type == SYMBOL && token.token == "]")
                rbraccount++;
            else
                ignore;
        }
        if(lbraccount == rbraccount)
            state = true;
        return state;
    }

    bool isCurlyClosed(TokenStream tokens){
        bool state = false;
        int lcurlycount = 0;
        int rcurlycount = 0;
        for(Token token : tokens){
            if(token.type == SYMBOL && token.token == "{")
                lcurlycount++;
            else if(token.type == SYMBOL && token.token == "}")
                rcurlycount++;
            else
                ignore;
        }
        if(lcurlycount == rcurlycount)
            state = true;
        return state;
    }

    vector<TokenStream> SplitCodelines(string code){
        vector<TokenStream> code_;
        int line = 1;
        string statement = "";
        for(char ch : code){
            if(ch != ';')
                statement.push_back(ch);
            else if(ch == '\n')
                line++;
            else{
                TokenStream tokens;
                for(Token token : tokenize(statement,line)){
                    tokens.push_back(token);
                }
                code_.push_back(tokens);
                statement = "";
            }
        }
        return code_;
    }

#endif // PARSEr_H_CSQ4
