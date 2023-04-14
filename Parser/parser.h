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
        bool ended;
        NODE_TYPE of;
        Scope(){}
        Scope(int level, NODE_TYPE of_, bool ended_){
            indent_level = level;
            of = of_;
            ended = ended_;

        };
    };

    struct ScopeSet{
        int indent_level;
        vector<Scope> scopes;
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
                lines.push_back(tokenize(current + ";ignore;"));
                current = "";
            }
        }
        return lines;
    }
    void replaceAll(string& str, const string& oldStr, const string& newStr) {
        size_t pos = 0;
        while ((pos = str.find(oldStr, pos)) != string::npos) {
            str.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
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
        return node;//Master scope..
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
            // if(last_indent_level-1 == indent_level)
            // {
            //     Statements.push_back(Statement(statement_number,"ignore","ignore",EXPR_TYPE,indent_level));
            // }
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
            last_indent_level = indent_level;
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

    //Seeking for last open scope

    Scope last_open_scope(vector<Scope> scope_stack){
        Scope last;
        for(Scope scope : scope_stack){
            if(scope.ended == 0){
                last = scope;
            }
        }
        return last;
    }

    Scope last_scope(vector<Scope> scope){
        return scope[scope.size()-1];
    }

    //This function is expecting that the Statements vector is already filled by the ParseLines function.

    /*
    for i in range(345):
     for j in range(i):
      print(j)
     print("--------------------------------")

    Statements:
    (for i in range(345):, 0)
    (for j in range(i):, 1)
    (print(j),2)
    (print("--------------------------------"),1)
    */
    string ParseStatements(){
        //Image of code
        string code, fncode;
        //Some properties for scopes
        Scope scope(0,PROGRAM,0);
        Scope master(0,PROGRAM,0);
        //To keep track of open scopes which are not yet closed.
        vector<Scope> scope_stack = {scope};
        //To keep track of last statement which can we used to check whether indentation is required or not.
        Statement last_statement;
        /*
        Reminder for tomorrow : To parse statements with scope handling use the facility to keep track of
        open scopes stored in scope_stack;
        [1,2,3,4]
        scope_required = 3
        pop()
        
        */
        for(Statement statement : Statements){
            //If the user has used wrong type of indentation
            if(notBlockStatement(last_statement.type)){
                unexpected_indent(statement.number,last_statement.raw_statement);
            }

            while(statement.indent_level != last_scope(scope_stack).indent_level){
                code += "}\n";
                scope_stack.pop_back();
            }


            switch(statement.type)
            {
                case EXPR_TYPE:{
                    code += statement.statement + ";\n";
                    break;
                }
                case VAR_DECLARATION:{
                    code += statement.statement + ";\n";
                    break;
                }
                case VAR_ASSIGNMENT:{
                    code += statement.statement + ";\n";
                    break;
                }
                case IF_STATEMENT:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
                case ELIF_STATEMENT:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
                case ELSE_STATEMENT:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
                case FOR_LOOP:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
                case WHILE_LOOP:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
                case FUNCTION_DECL:{
                    scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                    code += statement.statement + "{\n";
                    break;
                }
            }
        }
        return code;
    }
#endif // PARSEr_H_CSQ4
