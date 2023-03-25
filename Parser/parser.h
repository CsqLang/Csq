#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    //Imports
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    //Total count of errors.
    int error_count = 0;
    //Some alias
    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    typedef Ptr<Node> NodePtr;
    //Tools required for parsing

    //Program node to store all the childs
    typedef struct : Node{
        vector<Block> statements;
        void addChild(Block child){
            statements.push_back(child);
        }
    }Program;
    //Root for all nodes.
    Program root;


    //Scope for the statements
    struct Scope{
        int indent_level;
        Block body;
        Scope(){}
        Scope(int level, Block body_){
            indent_level = level;
            body = body_;
        };
    };

    //Struct to store infos about statements
    struct Statement{
        int indent_level;
        int statement_number;
        string statement;
        Statement(){}
        Statement(int statement_num, string statement_, int indent_level_){
            statement_number = statement_num;
            statement = statement_;
            indent_level = indent_level_;
        }
    };

    //Getting current indentation level.
    int getIndentLevel(TokenStream tokens){
        int indent_level = 0;
        if(tokens[0].type != INDENT)
            return indent_level;
        else{
            for(Token token : tokens){
                if(token.type == INDENT)
                    indent_level++;
                else
                    break; 
            }
            return indent_level;
        }
    }

    vector<TokenStream> Tokenizer(string code){
        code += "\n";
        vector<TokenStream> lines;
        string current = "";
        for(char ch : code){
            if(ch != '\n')
                current.push_back(ch);
            else{
                lines.push_back(tokenize(current));
                current = "";
            }
        }
        return lines;
    }
    //We can't directly use TokenStream as body of block so for that we use string.
    string TokenStreamToString(TokenStream tokens){
        string result;
        for(Token token : tokens){
            if(token.type == STR)
                result += "\"" + token.token + "\" ";
            else
                result += token.token + " ";
        }
        return result;
    }


    bool isIfStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "if" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isElifStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "elif" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isElseStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "else" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isFunDecl(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "def" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isVarDecl(TokenStream tokens){
        bool state = 0;
        if(tokens[0].type == IDENTIFIER && tokens[1].token == "=")
            state = 1;
        return state;
    }
    bool isWhileStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "while" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isForStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "for" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
/*
In this field the actual parsing will be done
and the process is that the functions will parse and generate AST node 
which will be used by scope defining functions to get desired results.
*/
    ForLoop ParseForLoop(TokenStream tokens);//(Defined)
    WhileLoop ParseWhileLoop(TokenStream tokens);//(Defined)
    VarDecl ParseVarDecl(TokenStream tokens);//(Defined)
    VarAssign ParseVarAssign(TokenStream tokens);//(Defined)
    FunctionDecl ParseFuncDecl(TokenStream tokens);//(Undefined)
    IfStmt ParseIfStmt(TokenStream tokens); //(Defined)
    ElifStmt ParseElifStmt(TokenStream tokens); //(Defined)
    ElseStmt ParseElseStmt(TokenStream tokens); //(Defined)

    IfStmt ParseIfStmt(TokenStream tokens){ 
        IfStmt node;
        bool condition = false;

        for(int i = 0; i<tokens.size(); i++)
            if(tokens[i].token == "if" && tokens[i].type == KEYWORD && condition == 0)
                condition = true;
            else if(condition && tokens[i].token != ":")
                node.condition.expr += tokens[i].token;
            else if(condition && tokens[i].token == ":")
            {
                condition = false;
                break;
            }
        if(node.condition.expr == ""){
            printf("Error:[%d] expected an expression, after keyword if.\n",error_count+1);
            printf("Hint:[%d] add a condition after if keyword.\n",error_count+1);
            error_count++;
        }
        if(condition){
            printf("Error:[%d] the if statement hasn't ended sucessfuly.\nHint:[%d] add a colon after condition.\n",error_count+1, error_count+1);
            error_count++;
        }
        return node;
    }

    ElifStmt ParseElifStmt(TokenStream tokens){
        ElifStmt node;
        bool condition = false;
        for(int i = 0; i<tokens.size(); i++)
            if(tokens[i].token == "elif" && tokens[i].type == KEYWORD && condition == 0)
                condition = true;
            else if(condition && tokens[i].token != ":")
                node.condition.expr += tokens[i].token;
            else if(condition && tokens[i].token == ":")
            {
                condition = false;
                break;
            }
        if(node.condition.expr == ""){
            printf("Error:[%d] expected an expression, after keyword elif.\n",error_count+1);
            printf("Hint:[%d] add a condition after elif keyword.\n",error_count+1);
            error_count++;
        }
        if(condition){
            printf("Error:[%d] the elif statement hasn't ended sucessfuly.\nHint:[%d] add a colon after condition.\n",error_count+1, error_count+1);
            error_count++;
        }
        return node;
    }

    ElseStmt ParseElseStmt(TokenStream tokens){
        ElseStmt node;
        if(tokens[1].token != ":"){
            printf("Error:[%d] expected a : after else.\n",error_count+1);
            error_count++;
        }
        return node;
    }

    VarDecl ParseVarDecl(TokenStream tokens){
        VarDecl node;
        bool value = false;
        for(Token token : tokens)
            if(!value && token.type == IDENTIFIER)
                node.name = token.token;
            else if(token.type == ASOPERATOR && !value)
                value = true;
            else if(value)
                node.value.expr += token.token + " ";
        if(node.value.expr == ""){
            printf("Error:[%d] expected a value after assignment operator.\n",error_count+1);
            error_count++;
        }
        return node;
    }

    VarAssign ParseVarAssign(TokenStream tokens){
        VarAssign node;
        bool value = false;
        for(Token token : tokens)
            if(!value && token.type == IDENTIFIER)
                node.name = token.token;
            else if(token.type == ASOPERATOR && !value)
                value = true;
            else if(value)
                node.value.expr += token.token + " ";
        if(node.value.expr == ""){
            printf("Error:[%d] expected a value after assignment operator.\n",error_count+1);
            error_count++;
        }
        return node;
    }

    WhileLoop ParseWhileLoop(TokenStream tokens){
        WhileLoop node;
        bool condition = false;
        for(Token token : tokens){
            if(token.token == "while" && token.type == KEYWORD)
                condition = true;
            else if(condition && token.token != ":")
                node.condition.expr += token.token + " ";
            else if(condition && token.token == ":"){
                condition = false;
                break;
            }
        }
        if(condition){
            printf("Error:[%d] expected a colon after conditon.\n",error_count+1);
            error_count++;
        }
        return node;
    }

    ForLoop ParseForLoop(TokenStream tokens){
        ForLoop node;
        bool condition = false;
        bool iter = false;
        for(Token token : tokens)
            if(token.token == "for" && !condition)
                iter = true;
            else if(iter && token.token != "in" && !condition)
                node.iter_name += token.token;
            else if(iter && token.token == "in" && !condition){
                iter = false;
                condition = true;
            }
            else if(condition && token.token != ":"){
                node.condition.expr += token.token + " ";
            }
            else if(condition && token.token == ":"){
                condition = 0;
                break;
            }
        if(condition){
            printf("Error:[%d] expected an end of condition.", error_count+1);
            error_count++;
        }
        return node;
    }

    FunctionDecl ParseFuncDecl(TokenStream tokens){
        FunctionDecl node;
        bool param = false;
        bool name = false;
        bool ended = false;
        string param_;
        for(Token token : tokens){
            if(token.token == "def" && !name && !param){
                name = 1;
            }
            else if(name && token.token != "(" && !param){
                node.name += token.token + " ";
            }
            else if(name && token.token == "(" && !param){
                name = 0;
                param = 1;
            }
            else if(param && token.token != "," && token.token != ")"){
                param_ += token.token;
            }
            else if(param && token.token == ","){
                node.params.push_back(param_);
                param_ = "";
            }
            else if(param && token.token == ")"){
                param = 0;
                node.params.push_back(param_);
                param_ = "";
            }
            else if(token.token == ":"){
                ended = true;
                break;
            }
        }
        if(param){
            printf("Error:[%d] expected an end of param.\nHint: put a ) after params.\n", error_count+1);
            error_count++;
        }
        if(!ended){
            printf("Error:[%d] expected an end for function.\nHint: put a : at the end.\n", error_count+1);
            error_count++;
        }
        return node;
    }

    //Function to parse scope of the particular indent_level;
    vector<Statement> ParseScope(vector<TokenStream> raw_tokens, string id = ""){
        vector<Statement> statements;
        int statNum = 1;
        for(TokenStream tokenStream : raw_tokens){
            statements.push_back(Statement(statNum, TokenStreamToString(tokenStream),getIndentLevel(tokenStream)));
            statNum++;
        }
        return statements;
    }

    //This function is gonna return the deepest indent level.
    int DeepestIndentLevel(vector<TokenStream> tokens)
    {
        int indent_level = 0;
        for(TokenStream tokenStream : tokens)
        {
            if(getIndentLevel(tokenStream) > indent_level){
                indent_level = getIndentLevel(tokenStream);
            }
            else{}
        }
        return indent_level;
    }

    /*
    Indentation handling shall be done in such a way in which every
    line with certain indentation shall be stored as an object.
    */
    //Define vector for all indentation levels
    vector<Statement> Statements;

    //Ultimate parsing statement.
    void Parse(TokenStream tokens);
    void Parse(TokenStream tokens){
        if(isVarDecl(tokens)){
            int indent_level = getIndentLevel(tokens);
            //Now remove all indent tokens present since we now know the indent level.
            TokenStream tokens_;
            for(Token token : tokens)
                if(token.type == INDENT)
                    ignore;
                else
                    tokens_.push_back(token);
            tokens = tokens_;
        }
    }

#endif // PARSEr_H_CSQ4
