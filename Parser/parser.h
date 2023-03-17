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
                decl->value.expr += tokens[i].token;
            node = decl;
            vector<string> Varstacktemp = Variables;
            Varstacktemp.push_back(decl->name);
            Variables = Varstacktemp;
        }
        else if(isVarAssign(tokens)) {
            shared_ptr<VarAssign> decl = make_shared<VarAssign>(); // initialize the shared_ptr
            decl->name = tokens[0].token;
            for (int i = 2; i < tokens.size(); i++)
                decl->value.expr += tokens[i].token;
            node = decl;
        }
        else if(isForStmt(tokens)){
            shared_ptr<ForLoop> decl = make_shared<ForLoop>();
            decl->iter_name = tokens[1].token;
            bool body_status = false;
            vector<string> statements;
            string statement;
            for(Token token : tokens)
                if(token.token != ":" && body_status != true)
                    decl->condition.expr += token.token;
                else if(token.token == ":" && body_status == false)
                    body_status = true;
                else if(body_status == true && token.token != ";")
                   statement += token.token;
                else if(body_status == true && token.token == ";"){
                    statements.push_back(statement);
                    statement = "";
                }
                else if(body_status == true && token.token == "endfor")
                    body_status = false;
            //After storing the statement into vector we need to do one more parsing so that it will not create enough conflict.
            for(string stmt : statements){
                //First tokenize the gathered statement.
                TokenStream tokens_ = tokenize(stmt,-1);
                shared_ptr<Node> node_returned = static_pointer_cast<Node>(ParseStatement(tokens_));;
                decl->body.statements.push_back(visit(node_returned));
            }
            node = decl;
        }
        
        return node;
    }

    

#endif // PARSEr_H_CSQ4
