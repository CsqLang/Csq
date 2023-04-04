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
        NODE_TYPE of;
        Scope(){}
        Scope(int level, NODE_TYPE of_){
            indent_level = level;
            of = of_;
        };
    };

    //Struct to store infos about statements
    struct Statement{
        int indent_level;
        int number;
        string statement;
        string raw_statement;
        NODE_TYPE type;
        Statement(){}
        Statement(int statement_num,string raw, string statement_, NODE_TYPE type_, int indent_level_){
            number = statement_num;
            statement = statement_;
            raw_statement = raw;
            indent_level = indent_level_;
            type = type_;
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
        if(tokens[0].type == IDENTIFIER && tokens[1].token == "=" && !in(tokens[0].token,Variables))
            state = 1;
        return state;
    }
    bool isVarAssign(TokenStream tokens){
        bool state = 0;
        if(tokens[0].type == IDENTIFIER && tokens[1].token == "=" && in(tokens[0].token,Variables))
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


    //Errors for the bad code.

    void error(int line, string msg){
        printf("Error [%d]: at line %d, %s\n",error_count+1, line, msg.c_str());
        error_count++;
    }

    void unexpected_indent(int line, string last_stmt_type){
        error(line, "unexpected indent after " + last_stmt_type);
    }

    void expected_indent(int line, string last_stmt_type){
        error(line, "expected an indent after " + last_stmt_type);
    }
    void unrecognized_statement(int line, string stmt){
        error(line, "unrecognized statement '" + stmt + "'.");
    }
    void function_insideIfstmt(int line){
        error(line, "function is defined inside IfStmt which is not allowed.");
    }
    void function_insideElif(int line){
        error(line, "function is defined inside ElifStmt which is not allowed.");
    }
    void function_insideElse(int line){
        error(line, "function is defined inside ElseStmt which is not allowed.");
    }
    void function_insideFunction(int line){
        error(line, "function is defined inside another function which is not allowed.");
    }
    void function_insideWhile(int line){
        error(line, "function is defined inside WhileLoop which is not allowed.");
    }
    void function_insideFor(int line){
        error(line, "function is defined inside another ForLoop which is not allowed.");
    }
    
    void noStorageClass(int line, string stmt, Scope scope){
        if(scope.of == CLASS_DEFINITION){
            error(line, "no storage class for the '" + stmt + "' inside a class.");
        }
    }
    void elifUsedWithoutIf(int line){
        error(line, "elif defined without any if statement before.");
    }
    void elseUsedWithoutIf(int line){
        error(line, "else defined without any if or elif statement before.");
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

    Expr ParseExpr(TokenStream tokens){
        Expr node;
        node.expr = TokenStreamToString(tokens);
        return node;
    }

    VarDecl ParseVarDecl(TokenStream tokens){
        VarDecl node;
        bool value = false;
        
        vector<string> Variables_ = Variables;
        Variables_.push_back(tokens[0].token);
        Variables = Variables_;
        Variables_.empty();
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
                node.name += token.token;
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
        return node;
    }

    // //Function to parse scope of the particular indent_level;
    // vector<Statement> ParseScope(vector<TokenStream> raw_tokens, string id = ""){
    //     vector<Statement> statements;
    //     int statNum = 1;
    //     for(TokenStream tokenStream : raw_tokens){
    //         statements.push_back(Statement(statNum, TokenStreamToString(tokenStream),getIndentLevel(tokenStream)));
    //         statNum++;
    //     }
    //     return statements;
    // }

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
    void ParseLines(TokenStream tokens);
    void ParseLines(vector<TokenStream> code_tokens){
        int statement_number = 1;
        Token line_end_token;
        line_end_token.token = "ignore";
        line_end_token.type = KEYWORD;
        int last_indent_level = 0;
        code_tokens.push_back(TokenStream({line_end_token}));
        for(TokenStream tokens : code_tokens){
            int indent_level = getIndentLevel(tokens);
            //Now remove all indent tokens present since we now know the indent level.
            TokenStream tokens_;
            for(Token token : tokens)
                if(token.type == INDENT)
                    ignore;
                else
                    tokens_.push_back(token);
                tokens = tokens_;
            if(isVarDecl(tokens)){
                
                //Now get AST node for the statement.
                auto node_ = make_shared<VarDecl>(ParseVarDecl(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),VAR_DECLARATION,indent_level));
            }
            else if(isVarAssign(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<VarAssign>(ParseVarAssign(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),VAR_ASSIGNMENT,indent_level));
            }
            else if(isFunDecl(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<FunctionDecl>(ParseFuncDecl(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),FUNCTION_DECL,indent_level));
            }
            else if(isForStmt(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<ForLoop>(ParseForLoop(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),FOR_LOOP,indent_level));
            }
            else if(isWhileStmt(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<WhileLoop>(ParseWhileLoop(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),WHILE_LOOP,indent_level));
            }
            else if(isIfStmt(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<IfStmt>(ParseIfStmt(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),IF_STATEMENT,indent_level));
            }
            else if(isElifStmt(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<ElifStmt>(ParseElifStmt(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),ELIF_STATEMENT,indent_level));
            }
            else if(isElseStmt(tokens)){
                //Now get AST node for the statement.
                auto node_ = make_shared<ElseStmt>(ParseElseStmt(tokens));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),ELSE_STATEMENT,indent_level));
            }
            else{
               auto node_ = make_shared<Expr>(ParseExpr(tokens));
               NodePtr node = static_pointer_cast<Node>(node_); 
               Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),EXPR_TYPE,indent_level));
            }
            statement_number++;
        }
        
    }

    bool notBlockStatement(NODE_TYPE type){
        bool state = 1;
        if
        (type == FOR_LOOP || type == WHILE_LOOP || type == IF_STATEMENT || type == ELIF_STATEMENT ||
         type == ELSE_STATEMENT || type == FUNCTION_DECL || type == CLASS_DEFINITION
        ){
            state = 0;
        }
        return state;
    }
    
    bool isBlockStatement(NODE_TYPE type){
        bool state = 0;
        if
        (type == FOR_LOOP || type == WHILE_LOOP || type == IF_STATEMENT || type == ELIF_STATEMENT ||
         type == ELSE_STATEMENT || type == FUNCTION_DECL || type == CLASS_DEFINITION
        ){
            state = 1;
        }
        return state;
    }


    //Traverse and print the statements with their properties.
    void PrintStatements(){
        for(Statement statement : Statements){
            printf("line : %d indent : %d type : %d (%s)\n",statement.number,statement.indent_level, statement.type, statement.statement.c_str());
        }
    }
    //This function is expecting that the Statements vector is already filled by the ParseLines function.
    string ParseStatements(){
        string code,fncode;
        int max_line_indent = 0;
        int last_indent = 0;
        bool fnstate = 0;
        NODE_TYPE last_stmt_type;
        string last_stmt;
        //This will be storing which keyword is used throughout the code.
        vector<string> keyword_log;
        Scope scope(0,PROGRAM);
        Scope master_scope(0,PROGRAM);
        Scope last_master_scope(0,PROGRAM);
        //State 0.5: get the max indent of the statements.
        for(Statement statement : Statements)
            if(statement.indent_level > max_line_indent)
                max_line_indent = statement.indent_level;
            else
                ignore;
        //Stage 1: Parse.
        //Traverse the statements
        for(Statement statement : Statements){
            //When indent levels are same as the scope.indent_level the statement is to be added.
            if(scope.indent_level == statement.indent_level && master_scope.of != FUNCTION_DECL){
                //The statement can also have certain types of node so we need to check via switch.
                switch(statement.type){
                    case EXPR_TYPE:{
                        code += statement.statement;
                        code += "\n";
                        break;                                        
                    }
                    case VAR_DECLARATION:{
                        code += statement.statement;
                        code += "\n";
                        break;                                    
                    }
                    case VAR_ASSIGNMENT:{
                        code += statement.statement;
                        code += "\n";
                        break;                                
                    }
                    case IF_STATEMENT:{
                        if(scope.of == CLASS_DEFINITION){
                            noStorageClass(statement.number, statement.raw_statement, scope);
                        }
                        else{
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level + 1;
                            scope.of = IF_STATEMENT;
                            keyword_log.push_back("if");
                        }
                        break;                                
                    }
                    case ELIF_STATEMENT:{
                        if(in("if",keyword_log)){
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELIF_STATEMENT;
                            keyword_log.push_back("elif");
                        }
                        else{
                            elifUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case ELSE_STATEMENT:{
                        if(in("elif",keyword_log) || in("if",keyword_log)){
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELSE_STATEMENT;
                            keyword_log.push_back("else");
                        }
                        else{
                            elseUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case FUNCTION_DECL:{
                        //First check that the function is defined in a correct place or not?
                        switch(scope.of){
                            case FUNCTION_DECL:{
                                function_insideFunction(statement.number);
                                break;
                            }
                            case IF_STATEMENT:{
                                function_insideIfstmt(statement.number);
                                break;
                            }
                            case ELIF_STATEMENT:{
                                function_insideElif(statement.number);
                                break;
                            }
                            case ELSE_STATEMENT:{
                                function_insideElse(statement.number);
                                break;
                            }
                            case FOR_LOOP:{
                                function_insideFor(statement.number);
                                break;
                            }
                            case WHILE_LOOP:{
                                function_insideWhile(statement.number);
                                break;
                            }
                            default:{
                                scope.indent_level = statement.indent_level+1;
                                scope.of = FUNCTION_DECL;
                                master_scope = scope;
                                fncode += statement.statement + "{\n";
                                fnstate = 1;
                                break;
                            }
                        }
                        break;                                
                    }
                    case WHILE_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = WHILE_LOOP;
                        code += statement.statement + "{\n";
                        break;                                
                    }
                    case FOR_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = FOR_LOOP;
                        code += statement.statement + "{\n";
                        break;                                
                    }
                    default:{
                        unrecognized_statement(statement.number, statement.raw_statement);
                        break;
                    }
                }
            }
            else if(scope.indent_level != statement.indent_level && master_scope.of != FUNCTION_DECL){
                //The decreased level = scope.indent_level - statement.indent_level
                int dlevel = scope.indent_level - statement.indent_level;
                for(int lvl = 1; lvl <= dlevel; lvl++){
                    code += "\n}\n";
                }
                //Now we again have to check which type of statement
                switch(statement.type){
                    case EXPR_TYPE:{
                        code += statement.statement;
                        code += "\n";
                        break;                                        
                    }
                    case VAR_DECLARATION:{
                        code += statement.statement;
                        code += "\n";
                        break;                                    
                    }
                    case VAR_ASSIGNMENT:{
                        code += statement.statement;
                        code += "\n";
                        break;                                
                    }
                    case IF_STATEMENT:{
                        if(scope.of == CLASS_DEFINITION){
                            noStorageClass(statement.number, statement.raw_statement, scope);
                        }
                        else{
                            code += statement.statement;
                            code += "{";
                            scope.indent_level = statement.indent_level + 1;
                            scope.of = IF_STATEMENT;
                            keyword_log.push_back("if");
                        }
                        break;                                
                    }
                    case ELIF_STATEMENT:{
                        if(in("if",keyword_log)){
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELIF_STATEMENT;
                            keyword_log.push_back("elif");
                        }
                        else{
                            elifUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case ELSE_STATEMENT:{
                        if(in("elif",keyword_log) || in("if",keyword_log)){
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELSE_STATEMENT;
                            keyword_log.push_back("else");
                        }
                        else{
                            elseUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case FUNCTION_DECL:{
                        //First check that the function is defined in a correct place or not?
                        switch(scope.of){
                            case FUNCTION_DECL:{
                                function_insideFunction(statement.number);
                                break;
                            }
                            case IF_STATEMENT:{
                                function_insideIfstmt(statement.number);
                                break;
                            }
                            case ELIF_STATEMENT:{
                                function_insideElif(statement.number);
                                break;
                            }
                            case ELSE_STATEMENT:{
                                function_insideElse(statement.number);
                                break;
                            }
                            case FOR_LOOP:{
                                function_insideFor(statement.number);
                                break;
                            }
                            case WHILE_LOOP:{
                                function_insideWhile(statement.number);
                                break;
                            }
                            default:{
                                scope.indent_level = statement.indent_level+1;
                                scope.of = FUNCTION_DECL;
                                code += statement.statement + "{\n";
                                fnstate = 1;
                                break;
                            }
                        }
                        break;                                
                    }
                    case WHILE_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = WHILE_LOOP;
                        code += statement.statement + "{\n";
                        break;                                
                    }
                    case FOR_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = FOR_LOOP;
                        code += statement.statement + "{\n";
                        break;                                
                    }
                    default:{
                        unrecognized_statement(statement.number, statement.raw_statement);
                        break;
                    }
                }
            }

            //This section contains the statements required to parse functions

            else if(scope.indent_level == statement.indent_level && master_scope.of == FUNCTION_DECL){
                //The statement can also have certain types of node so we need to check via switch.
                switch(statement.type){
                    case EXPR_TYPE:{
                        fncode += statement.statement;
                        fncode += "\n";
                        break;                                        
                    }
                    case VAR_DECLARATION:{
                        fncode += statement.statement;
                        fncode += "\n";
                        break;                                    
                    }
                    case VAR_ASSIGNMENT:{
                        fncode += statement.statement;
                        fncode += "\n";
                        break;                                
                    }
                    case IF_STATEMENT:{
                        printf("Counter else");
                        if(scope.of == CLASS_DEFINITION){noStorageClass(statement.number, statement.raw_statement, scope);}
                        else{
                            fncode += statement.statement;
                            fncode += "{\n";
                            scope.indent_level = statement.indent_level + 1;
                            scope.of = IF_STATEMENT;
                            keyword_log.push_back("if");
                        }
                        break;                                
                    }
                    case ELIF_STATEMENT:{
                        printf("Counter else");
                        if(in("if",keyword_log)){
                            code += statement.statement;
                            code += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELIF_STATEMENT;
                            keyword_log.push_back("elif");
                        }
                        else{
                            elifUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case ELSE_STATEMENT:{
                        printf("Counter else");
                        if(in("elif",keyword_log) || in("if",keyword_log)){
                            fncode += statement.statement;
                            fncode += "{\n";
                            scope.indent_level = statement.indent_level+1;
                            scope.of = ELSE_STATEMENT;
                            keyword_log.push_back("else");
                        }
                        else{
                            elseUsedWithoutIf(statement.number);
                        }
                        break;                                
                    }
                    case FUNCTION_DECL:{
                        function_insideFunction(statement.number);
                        break;                                
                    }
                    case WHILE_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = WHILE_LOOP;
                        fncode += statement.statement + "{\n";
                        break;                                
                    }
                    case FOR_LOOP:{
                        scope.indent_level = statement.indent_level+1;
                        scope.of = FOR_LOOP;
                        fncode += statement.statement + "{\n";
                        break;                                
                    }
                    default:{
                        unrecognized_statement(statement.number, statement.raw_statement);
                        break;
                    }
                }
            }
            else if(scope.indent_level != statement.indent_level && master_scope.of == FUNCTION_DECL){
                int change_indent = scope.indent_level-statement.indent_level;
                scope.indent_level = scope.indent_level-change_indent;
                for(int i = 0;i<change_indent;i++)
                    fncode += "}\n";
                printf("%d\n",scope.indent_level);
                if(scope.indent_level == master_scope.indent_level-1){
                    vector<string> functionstack1 = Functions;
                    functionstack1.push_back(fncode);
                    master_scope = last_master_scope;
                    last_master_scope.indent_level = scope.indent_level-1;
                    last_master_scope.of = FUNCTION_DECL;
                    Functions = functionstack1;
                    printf("%s\n",fncode.c_str());
                    fncode = "";
                }
            }

        }
        return code;
    }

#endif // PARSEr_H_CSQ4
