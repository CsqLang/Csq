#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    //Tools required for parsing

    /*Exceptions required for parsing and finding out the mistakes earlier.*/

    /*
        Check tokens.
    */
    bool parenthesisPresent(vector<Token> tokens){
        vector<string> strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("(", strtokens) || in(")", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool squareBracPresent(vector<Token> tokens){
        vector<string> strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("[", strtokens) || in("]", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool curlyBracesPresent(vector<Token> tokens){
        vector<string> strtokens;
        bool presence = false;
        for(Token token : tokens)
            strtokens.push_back(token.token);
        if(in("{", strtokens) || in("}", strtokens)){
            presence = true;
        }
        return presence;
    }

    bool isVarDecl(vector<Token> tokens){
        bool state = false;
        if(tokens[0].type == IDENTIFIER && tokens[1].type == ASOPERATOR && tokens[2].type != ASOPERATOR && in(tokens[0].token,Variables) == 0)
            state = true;
        return state;
    }

    bool isVarAssign(vector<Token> tokens){
        bool state = false;
        if(tokens[0].type == IDENTIFIER && tokens[1].type == ASOPERATOR && tokens[2].type != ASOPERATOR && in(tokens[0].token,Variables) == 1)
            state = true;
        return state;
    }       

    bool isBinaryExpr(vector<Token> tokens){
        bool state = 0;
        for(Token token : tokens){
            if(isOperator(token.token))
                state = 1;
        }
        return state;
    }
    //This will be useful to do parsing.
    int current_index = 0;
    //This represents the stream of tokens.
    vector<Token> Tokens;
    //function to traverse the stream of tokens one by one.
    Token next(){
        current_index++;
        return Tokens[current_index-1];
    }

    //function to do parsing and return AST node.
    Node* ParseStatement(vector<Token> tokens){
        Node* node;
        Tokens = tokens;
        if(isVarDecl(tokens)){
            VarDecl varNode;
            varNode.type = VAR_DECLARATION;
            varNode.name = tokens[0].token;
            //Add variable name to stack.
            Variables.push_back(varNode.name);
            /*If this if block is implemented it means it has passed conditions of VarDecl so 
            as tokens[1] there will be '=' so we should work upon values so to do so we could
            do one more check to find the type of values like BinaryExpr or any else.
            */
        }
        return node;
    }

#endif // PARSEr_H_CSQ4
