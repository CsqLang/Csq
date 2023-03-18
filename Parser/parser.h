#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    int error_count = 0;

    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    typedef Ptr<Node> NodePtr;
    //Tools required for parsing

    /*Exceptions required for parsing and finding out the mistakes earlier.*/
    void ParenthesisNotClosed(int line){
        printf("At line : %d, parenthesis aren't properly closed.\n",line);
        error_count++;
    }
    void CurlyBraceNotClosed(int line){
        printf("At line : %d, curly brackets aren't properly closed.\n",line);
        error_count++;
    }
    void SquareBracNotClosed(int line){
        printf("At line : %d, square brackets aren't properly closed.\n",line);
        error_count++;
    }

    void ExpectedInAfterFor(){
        printf("Error : Expected a 'in' keyword after iterator name in for loop.\n");
        error_count++;
    }

    void StopCompilation(){
        printf("Couldn't compile due to %d previous errors.\n",error_count);
    }

    void CsqErrorGuard(){
        if(error_count > 0){
            StopCompilation();
            exit(0);
        }
    }

    //Different types of tokens including symbols and keywords
    typedef enum{
        LBRACE,
        RBRACE,
        LPAREN,
        RPAREN,
        LBRACK,
        RBRACK,
        PERCENT,
        EQUAL,
        TILDE,
        COMMA,
        GREATER,
        LESSER,
        SEMI,
        COLAN,
        PLUS,
        MINUS,
        STAR,
        BSLASH,
        HASHTAG,
        AMPER,
        POWER,
        IMPORT,
    }PTOKEN;

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
        if(tokens[1].type == ASOPERATOR && (tokens[2].type != ASOPERATOR) && (in(tokens[0].token,Variables) == 1))
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

    bool isFunDecl(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "def")
                state = true;
        return state;
    }

    bool isForStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "for")
                state = true;
        return state;
    }

    bool isWhileStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "while")
                state = true;
        return state;
    }

    bool isIfStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "if")
                state = true;
        return state;
    }


    bool isElifStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "elif")
                state = true;
        return state;
    }


    bool isElseStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "else")
                state = true;
        return state;
    }

    bool isClassDef(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "class")
                state = true;
        return state;
    }

    bool isImportStmt(TokenStream tokens){
        bool state = false;
        for(Token token : tokens)
            if(token.type == KEYWORD && token.token == "import")
                state = true;
        return state;
    }
    string varn;

    NodePtr ParseStatement(TokenStream tokens) {
        NodePtr node = make_shared<Node>();
        if (isVarDecl(tokens)) {
            shared_ptr<VarDecl> decl = make_shared<VarDecl>(); // initialize the shared_ptr
            decl->name = tokens[0].token;
            for (int i = 2; i < tokens.size(); i++)
                if(tokens[i].token != ";")
                    if(tokens[i].type == STR)
                        decl->value.expr += "\"" + tokens[i].token + "\"";
                    else
                        decl->value.expr += tokens[i].token;
                else
                    break;
            node = decl;
            vector<string> Varstacktemp = Variables;
            Varstacktemp.push_back(decl->name);
            Variables = Varstacktemp;
        }
        else if(isVarAssign(tokens)) {
            shared_ptr<VarAssign> decl = make_shared<VarAssign>(); // initialize the shared_ptr
            decl->name = tokens[0].token;
            for (int i = 2; i < tokens.size(); i++)
                if(tokens[i].token != ";")
                    decl->value.expr += tokens[i].token;
                else
                    break;
            node = decl;
        }
        else if(isForStmt(tokens)){
            shared_ptr<ForLoop> decl = make_shared<ForLoop>();
            vector<TokenStream> statements;
            bool body_state = false;
            decl->iter_name = tokens[1].token;
            
            if(tokens[2].token != "in")
                ExpectedInAfterFor();
            else{
                TokenStream statement;
                for(int i = 3;i<tokens.size();i++){
                    if(tokens[i].token != ":" && body_state == 0)
                        decl->condition.expr += tokens[i].token + " ";
                    else if(tokens[i].token == ":" && body_state == 0)
                        body_state = true;
                    else if(body_state == 1 && tokens[i].token != "endfor")
                        statement.push_back(tokens[i]);
                    else if(body_state == 1 && tokens[i].token == ";"){
                        printf("%s ",tokens[i].token.c_str());
                        statement.push_back(tokens[i]);
                        statements.push_back(statement);
                        statement.clear();
                    }
                    else if(body_state == 1 && tokens[i].token == "endfor"){
                        break;
                    }
                }
                node = decl;
            }
        }

        else{
            shared_ptr<Expr> decl = make_shared<Expr>();
            for(Token token : tokens){
                if(token.token != ";")
                    decl->expr += token.token;
                else
                    break;
            }
            node= decl;
        }

        return node;
    }

#endif // PARSEr_H_CSQ4
