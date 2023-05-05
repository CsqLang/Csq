#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    //Imports
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"
    #include "typechecker.h"
    //Current director
    string Pcurrent_dir;

    
    //Some alias
    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    typedef Ptr<Node> NodePtr;
    //Indentation map for variables
    map<int, StringStream> variable_stack;
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
    //Variable scope check;
    bool Var_checkIsDefined(int indent_level, string var_name){
        bool state = 0;
        for(int i = 0;i<=indent_level;i++){
            if(in(var_name, variable_stack[i])){
                state = 1;
                break;
            }
        }
        return state;
    }

    //For Testing puropse only --------------------------------
    void print_VarStack(){
        for(int i = 0;i<variable_stack.size();i++){
            printf("%d : ",i);
            for(string v : variable_stack[i]){
                printf("%s, ", v.c_str());
            }
            printf("\n");
        }
    }
    //---------------------------------------------------------

    /*
    Indentation handling shall be done in such a way in which every
    line with certain indentation shall be stored as an object.
    */
    //
    //Define vector for all indentation levels
    vector<Statement> Statements;

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
    bool isVarDecl(TokenStream tokens, int indent_level){
        bool state = 0;
        if(
            tokens[0].type == IDENTIFIER && (tokens[1].token == "=" 
            || tokens[1].token == ":") && !Var_checkIsDefined(1000+indent_level,tokens[0].token))
            state = 1;
        return state;
    }
    bool isVarAssign(TokenStream tokens, int indent_level){
        bool state = 0;
        if(tokens[0].type == IDENTIFIER && tokens[1].token == "=" &&
           Var_checkIsDefined(1000+indent_level,tokens[0].token))
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

    bool isBreakStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "break" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }

    bool isClassDecl(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "class" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }
    bool isGroupDecl(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "group" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }

    bool isImportStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens)
            if(token.token == "import" && token.type == KEYWORD)
            {
                state = true;
                break;
            }
        return state;
    }

    bool isOneliner(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens){
            if(token.token == ";"){state = 1;break;}
        }
        return state;
    }

    bool isReturnStmt(TokenStream tokens){
        bool state = 0;
        for(Token token : tokens){
            if(token.token == "return"){state = 1;break;}
        }
        return state;
    }

    //Errors for the bad code.

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
    Expr ParseExpr(TokenStream tokens, int line){
        // Expr node = TokenStreamToString(tokens);
        Expr node = Expr("");
        for(int i = 0;i < tokens.size(); i++){
            if(tokens[i].type == KEYWORD){
                node.expr += tokens[i].token + " ";
            }
            else if(tokens[i].type == IDENTIFIER){
                if(in(tokens[i].token, AllIdentifiers())){
                    node.expr += tokens[i].token + " ";
                }
                else{
                    error(line, "undefined name " + tokens[i].token + ".");
                }
            }
            else{
                node.expr += tokens[i].token + " ";
            }
        }
        return node;
    }

    Break ParseBreakStmt(TokenStream tokens, int line){
        Break node;
        if(tokens.size()>1){
            error(line, "unexpected token after break statement.");
        }
        return node;
    }

    IfStmt ParseIfStmt(TokenStream tokens, int line){ 
        IfStmt node;
        bool condition = false;
        TokenStream condition_expr;
        for(int i = 0; i<tokens.size(); i++)
            if(tokens[i].token == "if" && tokens[i].type == KEYWORD && condition == 0)
                condition = true;
            else if(condition && tokens[i].token != ":")
                condition_expr.push_back(tokens[i]);
            else if(condition && tokens[i].token == ":")
            {
                condition = false;
                break;
            }
        node.condition = ParseExpr(condition_expr,line);
        if(node.condition.expr == ""){
            error(line, "expected an expression, after keyword if.");
            printf("Hint: add a condition after if keyword.\n");
        }
        if(condition){
            error(line, "the if statement hasn't ended sucessfuly.");
            printf("Hint: add a colon after condition.\n");
        }
        return node;
    }

    ReturnStmt ParseReturnStmt(TokenStream tokens, int line){
        ReturnStmt node;
        TokenStream token_;
        bool v = 0;
        for(Token token : tokens){
            if(token.token == "return" && token.type == KEYWORD && !v){
                v = 1;
            }
            else if(v && token.type == KEYWORD){
                error(line, "invalid use of keyword " + token.token + " in return stmt.");
            }
            else if(v){
                token_.push_back(token);
            }
        }
        node.expr = ParseExpr(token_, line);
        return node;
    }

    ElifStmt ParseElifStmt(TokenStream tokens, int line){
        ElifStmt node;
        bool condition = false;
        TokenStream condition_expr;
        for(int i = 0; i<tokens.size(); i++)
            if(tokens[i].token == "elif" && tokens[i].type == KEYWORD && condition == 0)
                condition = true;
            else if(condition && tokens[i].token != ":")
                condition_expr.push_back(tokens[i]);
            else if(condition && tokens[i].token == ":")
            {
                condition = false;
                break;
            }
        node.condition = ParseExpr(condition_expr,line);
        if(node.condition.expr == ""){
            error(line, "expected an expression, after keyword elif.");
            printf("Hint: add a condition after elif keyword.\n");
        }
        if(condition){
            error(line, "the elif statement hasn't ended sucessfuly.");
            printf("Hint: add a colon after condition.\n");
        }
        return node;
    }

    ElseStmt ParseElseStmt(TokenStream tokens, int line){
        ElseStmt node;
        if(tokens[1].token != ":"){
            error(line, "expected a : after else.");
        }
        return node;
    }


    VarDecl ParseVarDecl(TokenStream tokens,int indent, int line, int num){
        VarDecl node;
        bool type_ = false;
        bool equal_ = false;
        TokenStream value_expr;

        if(tokens[1].token == ":"){
            type_  = 1;
        }

        if(type_){
            bool t_comes = 0;
            bool n_comes = 1;
            bool v_comes = 0;
            for(Token token : tokens){
                if(n_comes){
                    if(token.type != IDENTIFIER){
                        error(line, "expected an identifier.");
                    }
                    else{
                        node.name = token.token;
                        n_comes = 0;
                    }
                }
                else if(!n_comes && !t_comes && token.token == ":"){
                    t_comes = 1;
                }
                else if(t_comes){
                    if(token.token != "=" && token.token != ">="){
                        node.type_ += token.token;
                    }
                    else{
                        t_comes = 0;
                        v_comes = 1;
                        if(token.token == ">="){
                            node.type_ += ">";
                        }
                    }
                }
                else if(v_comes){
                    value_expr.push_back(token);
                }
            }
        }
        else{
            //Infr the type:
            bool t_comes = 0;
            bool n_comes = 1;
            bool v_comes = 0;
            for(Token token : tokens){
                if(n_comes){
                    if(token.type != IDENTIFIER){
                        error(line, "expected an identifier.");
                    }
                    else{
                        node.name = token.token;
                        n_comes = 0;
                    }
                }
                else if(!n_comes && !t_comes && token.token == "="){
                    v_comes = 1;
                }
                else if(v_comes){
                    value_expr.push_back(token);
                }
            }
        }
        MemberVarProperty prop;
        prop.name = node.name;
        if(type_){
            prop.name = node.name;
            prop.type = node.type_;
            node.type_infr = 0;
        }
        else{
            prop.type = "NONE";
            node.type_infr = 1;
        }
        node.value = ParseExpr(value_expr, line);
        variable_stack[1000+indent+num].push_back(node.name);
        variables_prop.push_back(prop);
        return node;
    }

    VarAssign ParseVarAssign(TokenStream tokens, int line){
        VarAssign node;
        TokenStream value_expr;
        bool value = false;
        for(Token token : tokens)
            if(!value && token.type == IDENTIFIER)
                node.name = token.token;
            else if(token.type == ASOPERATOR && !value)
                value = true;
            else if(value)
                value_expr.push_back(token);
        if(value_expr.size() == 0){
            error(line, "expected a value after assignment operator.");
        }
        node.value = ParseExpr(value_expr,line);
        return node;
    }

    WhileLoop ParseWhileLoop(TokenStream tokens,int line){
        WhileLoop node;
        TokenStream condition_expr;
        bool condition = false;
        for(Token token : tokens){
            if(token.token == "while" && token.type == KEYWORD)
                condition = true;
            else if(condition && token.token != ":")
                condition_expr.push_back(token);
            else if(condition && token.token == ":"){
                condition = false;
                break;
            }
        }
        if(condition){
            error(line, "expected a colon after conditon.");
        }
        node.condition = ParseExpr(condition_expr, line);
        return node;
    }

    ForLoop ParseForLoop(TokenStream tokens, int line){
        ForLoop node;
        bool condition = false;
        bool iter = false;
        TokenStream condition_expr;
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
                condition_expr.push_back(token);
            }
            else if(condition && token.token == ":"){
                condition = 0;
                break;
            }
        
        if(condition){
            error(line, "expected an end of condition.");
        }
        else{
            MemberVarProperty prop;
            prop.name = node.iter_name;
            prop.type = "NONE";
            variables_prop.push_back(prop);
            node.condition = ParseExpr(condition_expr,line);
        }
        return node;//Master scope..
    }

    FunctionDecl ParseFuncDecl(TokenStream tokens,int indent_level, int line){
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
            else if(token.token == "->" && param == 0){}
            else if(token.type == IDENTIFIER && param == 0){
                node.return_type = token.token;
                node.return_type_infr = 0;
            }
            else if(token.token == ":"){
                ended = true;
                break;
            }
        }
        if(param){
            error(line, "expected an end of param.");
            printf("Hint: put a ) after params.\n");
        }
        else{
            if(node.name != ""){
                Identifiers.push_back(node.name);
                MethodProperty p;
                p.name = node.name;
                p.type = "NONE";
                p.params = node.params;
                methods_prop.push_back(p);
            }
            if(node.params.size()!= 0){
                for(string param : node.params){
                    if(param != ""){
                        ParseVarDecl(tokenize(param),indent_level+1,line,line);
                    }
                }
            }
        }
        return node;
    }

    ClassDecl ParseClassDecl(TokenStream tokens, int line){
        ClassDecl node;
        bool name, iclass;
        iclass = 0;
        name = iclass;
        for(Token token : tokens)
        {
            if(token.token == ":")
            {break;}
            else{
                if(token.token == "class"){
                    name = 1;
                }
                else if(token.type != IDENTIFIER && name == 1){
                    printf("Error:[%d] At line %d, expected an identifier after class keyword.\n", error_count+1, line);
                    error_count++;
                }
                else if(token.type != IDENTIFIER && iclass == 1){
                    printf("Error:[%d] At line %d, expected an identifier.\n", error_count+1, line);
                    error_count++;
                }
                else if(token.type == IDENTIFIER && name == 1){
                    node.name = token.token;
                    iclass = 1;
                    name = 0;
                }
                else if(token.type == IDENTIFIER && iclass == 1){
                    node.inherit_class = token.token;
                }
            }
        }
        if(node.name != ""){
            Identifiers.push_back(node.name);
            ClassProp prop;
            prop.inheritted_class = node.inherit_class;
            prop.name = node.name;
            Classes.push_back(prop);
        }
        return node;
    }

    //Function to parse group declarations.
    Group ParseGroupStmt(TokenStream tokens, int line){
        Group node;
        bool end = false;
        bool name = false;
        bool over = false;

        for(Token token : tokens){
            if(token.token == "group" && !name && !end){
                name = true;
            }
            else if(name){
                if(token.type != IDENTIFIER){
                    printf("Error:[%d] at line %d, expected an identifier after group keyword.\n", error_count+1, line);
                    error_count++;
                }
                else{
                    node.name = token.token;
                    name = 0;
                    end = 1;
                }
            }
            else if(end){
                if(token.token != ":"){
                    printf("Error:[%d] at line %d, unexpected %s used in group declaration.\n", error_count+1, line, token.token.c_str());
                    error_count++;
                }
                else{
                    end = 0;
                    over = 1;
                }
            }
            else if(over){
                printf("Error:[%d] at line %d, unexpected %s used in group declaration.\n",error_count+1, line, token.token.c_str());
                error_count++;
            }
        }
        if(end){
            printf("Error:[%d] at line %d, group declaration is not closed expected a : .\n",error_count+1, line);
                error_count++;
        }
        else{
            if(node.name != ""){
                Identifiers.push_back(node.name);
            }
        }
        return node;
    }


    /**********************************************************************************************************************************************************************/

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

    Import ParseImportStmt(TokenStream tokens, int line);
    //Defines all imports
    string imported_code;

    //This function will do actual parsing and appends the results into Statement vector which could be futher assembled by ParseStatements function.
    void ParseLines(vector<TokenStream> code_tokens){
        int statement_number = 1;
        Token line_end_token;
        line_end_token.token = "ignore";
        line_end_token.type = KEYWORD;
        int last_indent_level = 0;
        code_tokens.push_back(TokenStream({line_end_token}));
        //Look for each line.
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
            //Now check for token types and parse them seper
            if(isVarDecl(tokens, indent_level)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<VarDecl>(ParseVarDecl(tokens,indent_level, statement_number,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),VAR_DECLARATION,indent_level));
            }
            else if(isVarAssign(tokens, indent_level)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<VarAssign>(ParseVarAssign(tokens, statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),VAR_ASSIGNMENT,indent_level));
            }
            else if(isFunDecl(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<FunctionDecl>(ParseFuncDecl(tokens,indent_level+1, statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),FUNCTION_DECL,indent_level));
            }
            else if(isForStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<ForLoop>(ParseForLoop(tokens, statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),FOR_LOOP,indent_level));
            }
            else if(isWhileStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<WhileLoop>(ParseWhileLoop(tokens, statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),WHILE_LOOP,indent_level));
            }
            else if(isIfStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<IfStmt>(ParseIfStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),IF_STATEMENT,indent_level));
            }
            else if(isElifStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<ElifStmt>(ParseElifStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),ELIF_STATEMENT,indent_level));
            }
            else if(isElseStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                //Now get AST node for the statement.
                auto node_ = make_shared<ElseStmt>(ParseElseStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_);
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),ELSE_STATEMENT,indent_level));
            }
            else if(isBreakStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
               auto node_ = make_shared<Break>(ParseBreakStmt(tokens,statement_number));
               NodePtr node = static_pointer_cast<Node>(node_); 
               Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),BREAK,indent_level));
            }
            else if(isClassDecl(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                auto node_ = make_shared<ClassDecl>(ParseClassDecl(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_); 
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),CLASS_DEFINITION,indent_level));
            }
            else if(isGroupDecl(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                auto node_ = make_shared<Group>(ParseGroupStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_); 
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),GROUP,indent_level));
                Group_stack.push_back(node_->name);
            }
            else if(isReturnStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                auto node_ = make_shared<ReturnStmt>(ParseReturnStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_); 
                Statements.push_back(Statement(statement_number,TokenStreamToString(tokens),visit(node),RETURN_STMT,indent_level));
            }
            else if(isImportStmt(tokens)){
                tokens.pop_back();
                tokens.pop_back();
                tokens.pop_back();
                auto node_ = make_shared<Import>(ParseImportStmt(tokens,statement_number));
                NodePtr node = static_pointer_cast<Node>(node_); 
                imported_code += node_->code + "\n";
            }
            else{
               auto node_ = make_shared<Expr>(ParseExpr(tokens,statement_number));
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

    //Create an instance of group statement.
    string create_group_object(){
        string code;
        string g = Group_stack[0];
        code += g + " " + g + ";\n";
        return code;
    }

    //Returns the last scope present in the given scope vector.
    Scope last_scope(vector<Scope> scope){
        return scope[scope.size()-1];
    }

    //Last parsing stage which will return transpiled code and work with indentations.
    string ParseStatements(){
        //Image of code
        string code, fncode;
        code = imported_code;
        //Some properties for scopes
        Scope scope(0,PROGRAM,0);
        Scope master(0,PROGRAM,0);
        bool class_ = 0;
        //To keep track of open scopes which are not yet closed.
        vector<Scope> scope_stack = {scope};
        //To keep track of last statement which can we used to check whether indentation is required or not.
        Statement last_statement;
        for(Statement statement : Statements){
                while(statement.indent_level != last_scope(scope_stack).indent_level){
                    //Here 1000 is added to encode the indentation level and avoid the conflict with same indents.
                    variable_stack.erase(1000+last_scope(scope_stack).indent_level+statement.number);
                    if(last_scope(scope_stack).of == FUNCTION_DECL || last_scope(scope_stack).of == CLASS_DEFINITION){
                        code += "};\n";
                        scope_stack.pop_back(); 
                        if(last_scope(scope_stack).of == CLASS_DEFINITION){
                            class_ = 0;
                        }
                    }
                    else if(last_scope(scope_stack).of == GROUP){
                        if(Group_stack.size()!=0){
                            code += "};\n" +  create_group_object();
                            scope_stack.pop_back();
                        }
                    }
                    else{
                        code += "}\n";
                        scope_stack.pop_back(); 
                    }
                }
                //Checking the type of current statement and generating code accordingly.
                switch(statement.type)
                {
                    case EXPR_TYPE:{
                        code += statement.statement + ";\n";
                        last_statement = statement;
                        break;
                    }
                    case VAR_DECLARATION:{
                            code += statement.statement + ";\n";
                            last_statement = statement;
                        break;
                    }
                    case VAR_ASSIGNMENT:{
                        code += statement.statement + ";\n";
                        last_statement = statement;
                        break;
                    }
                    case IF_STATEMENT:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\n";
                        last_statement = statement;
                        break;
                    }
                    case ELIF_STATEMENT:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\n";
                        last_statement = statement;
                        break;
                    }
                    case ELSE_STATEMENT:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\n";
                        last_statement = statement;
                        break;
                    }
                    case FOR_LOOP:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\n";
                        last_statement = statement;
                        break;
                    }
                    case WHILE_LOOP:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\n";
                        last_statement = statement;
                        break;
                    }
                    case CLASS_DEFINITION:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\npublic:\n";
                        class_ = 1;
                        last_statement = statement;
                        break;
                    }
                    case RETURN_STMT:{
                        code += statement.statement;
                        last_statement = statement;
                    }
                    case FUNCTION_DECL:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        if(class_ ==1){
                            // ParseFuncDecl(tokenize(statement.raw_statement)).name;
                            replaceAll(statement.statement,"=[&]","");
                            code += statement.statement + "{\n";
                            last_statement = statement;
                        }
                        else{
                            code += statement.statement + "{\n";
                            last_statement = statement;
                        }
                        break;
                    }
                    case BREAK:{
                        code += statement.statement + ";\n";
                        last_statement = statement;
                        break;
                    }
                    case GROUP:{
                        scope_stack.push_back(Scope(statement.indent_level+1, statement.type, 0));
                        code += statement.statement + "{\npublic:\n";
                        last_statement = statement;
                        break;
                    }
                    default:{
                        error(statement.number, "unknow node type " + to_string(statement.type));
                    }
                }
        }
        imported_code = "";
        return code;
    }

    #include "../IR/vm.h"

    Import ParseImportStmt(TokenStream tokens, int line){
        Import node;
        bool path = 0;
        bool error_ = 0;
        //First capture the name and path of the file
        for(Token token : tokens){
            if(token.token == "import" && path == 0){path = 1;}
            else if(token.token == "import" && path == 1){
                error(line, "couldn't use import keyword as path to the module.");
                error_ = 1;
            }
            else if(path && token.type != KEYWORD){
                node.path += token.token;
            }
            else if(path && token.type == KEYWORD){
                error(line, "couldn't use a keyword as path to the module.");
                error_ = 1;
            }
        }
        if(!error_){
            string path_ = Pcurrent_dir + "/" + node.path + ".csq";
            //Read the code in it.
            string read_code = readCode(path_);
            ParseLines(Tokenizer(read_code));
            node.code = ParseStatements();
            Statements = {};
        }
        
        return node;
    }

#endif // PARSEr_H_CSQ4
