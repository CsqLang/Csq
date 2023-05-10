#if !defined(PARSER_CSQ4)
#define PARSER_CSQ4

#include "../AST/ast.h"
#include <map>

//Parent directory:
string Pcurrent_dir;

typedef vector<Token> TokenStream;
typedef vector<Token> StringStream;
typedef shared_ptr<Node> NodePtr;
//Abstract type for all variables
struct Variable{
    string name;
    string type;
};
//Abstract type for all functions
struct Function{
    string name;
    string type;
    vector<Variable> params;
};

//Abstract type for all classes defined some predefined are int, float and str
struct Class{
    string name;
    string inherit_class;
    vector<Variable> variables;
    vector<Function> methods;
};


//Symbol table type
enum SymbolType{
    ST_FUNCTION,
    ST_VARIABLE,
    ST_CLASS,
};

//Symbol table
struct SymbolTable{
    map<int,map<string,Variable>> variables;
    map<int,map<string,Class>> classes;
    map<int,map<string,Function>> functions;

    //Helper functions
    void addVariable(int parent, int current_scope, Variable variable){
        variables[(1000*parent) + current_scope][variable.name] = variable;
    }
    void addFunction(int parent, int current_scope, Function function){
        functions[(1000*parent) + current_scope][function.name] = function;
    }
    void addClass(int parent, int current_scope, Class class_){
        classes[(1000*parent) + current_scope][class_.name] = class_;
    }
    //Checking certain symbol in the symbol table
    /*
    Now the main problem appears, when there are two different scopes with same indent level
    so there will be a conflict between their members so to solve it we could do encoding :
    scope1 : function fn level = 1
    symbol table key : 1001
    scope2 : function fn2 level = 1
    symbol table key : 2001

    */
    bool isPresent(int current_scope, string symbol, SymbolType type){
        if(type == ST_VARIABLE)
        {
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Variable> var : variables[i]){
                    if(var.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
        else if(type == ST_FUNCTION)
        {
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Function> fun : functions[i]){
                    if(fun.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
        else{
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Class> c : classes[i]){
                    if(c.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
    }
    Variable getVariable(string name, int current_index){
        return variables[current_index][name];
    }
    Class getClass(string name, int current_index){
        return classes[current_index][name];
    }
    bool isClassPresent(string name, int current_scope){
        bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Class> c : classes[i]){
                    if(c.first == name){
                        state = 1;
                        break;
                    }
                }
            }
        return state;
    }
    bool isVariablePresent(string name, int current_scope){
        bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Variable> var : variables[i]){
                    if(var.first == name){
                        state = 1;
                        break;
                    }
                }
            }
        return state;
    }
};SymbolTable table;

bool isIdentifierDefined(string identifier, int current_scope){
    bool state = false;

    if(table.isPresent(current_scope, identifier,ST_VARIABLE)){
        state = true;
    }
    else if(table.isPresent(current_scope, identifier,ST_FUNCTION)){
        state = true;
    }
    else if(table.isPresent(current_scope, identifier,ST_CLASS)){
        state = true;
    }
    return state;
}
bool MemberPresent(string var_name,string member, int indent_level, int parent){
    bool state = 0;
    Class class_ = table.getClass(table.getVariable(var_name, (parent*1000)+indent_level).type,(parent*1000)+indent_level);
    for(Function fn : class_.methods){
        if(fn.name == member){
            state = 1;
        }
    }
    for(Variable var : class_.variables){
        if(var.name == member){
            state = 1;
        }
    }
    return state;
}
bool MemberPresentOf(string type,string member, int indent_level, int parent){
    bool state = 0;
    Class class_ = table.getClass(type, (parent*1000)+indent_level);
    for(Function fn : class_.methods){
        if(fn.name == member){
            state = 1;
        }
    }
    for(Variable var : class_.variables){
        if(var.name == member){
            state = 1;
        }
    }
    return state;
}

//This function will load builtins since they are defined in C headerfile not in direct Csq module.
void load_builtins_to_table(){
    Function print;
    print.name = "print";
    print.type = "void";
    table.addFunction(1,0,print);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//Tokenizer for each line seperation
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
//All different types of function for parsing down different statements.

Expr ParseExpr(TokenStream tokens, int line, int indent_level, int parent){
    Expr node;

    for(int i = 0;i<tokens.size();i++)
    {
        if(tokens[i].type == IDENTIFIER)
        {
            if(tokens[i+1].token == ".")
            {
                if(tokens[i+2].type == IDENTIFIER)
                {
                    if(MemberPresent(tokens[i].token,tokens[i+2].token,indent_level,parent)){
                        node.expr += tokens[i].token + "." + tokens[i+2].token;
                        i+=2;
                    }
                }
                else{error(line,"expected an identifier.");}
            }  
            else
            {
                node.expr += tokens[i].token + " ";
            }
        }   
        else if(tokens[i].token != ".")
        {
            node.expr += tokens[i].token + " ";
        }
    }

    return node;
}
// All through both ParseExpr and ParseRValue returns same thing but this one is made for variable parsing 
Expr ParseRValue(TokenStream tokens,string lType, int line, int indent_level, int parent){
    Expr node;

    for(int i = 0;i<tokens.size();i++)
    {
        if(tokens[i].type == IDENTIFIER)
        {
            if(tokens[i+1].token == ".")
            {
                if(tokens[i+2].type == IDENTIFIER)
                {
                    if(lType == "NONE"){
                        node.expr += tokens[i].token + "." + tokens[i+2].token;
                        i+=2;
                    }
                    else if(MemberPresent(tokens[i].token,tokens[i+2].token,indent_level,parent)){
                        node.expr += tokens[i].token + "." + tokens[i+2].token;
                        i+=2;
                    }
                }
                else{error(line,"expected an identifier.");}
            }  
            else
            {
                node.expr += tokens[i].token + " ";
            }
        }   
        else if(tokens[i].token != ".")
        {
            node.expr += tokens[i].token + " ";
        }
    }

    return node;
}

VarDecl ParseVarDecl(TokenStream tokens, int line, int indent_level, int parent){
    VarDecl node;
    TokenStream val_expr;
    //Default type:
    node.type_ = "NONE";
    node.type_infr = 1;
    /*
        Grammar for VarDecl:
        <identifier> : <type> = <value>
        or
        <identifier> = <value>
    */
    //States
    bool name = 1;
    bool type = 0;
    bool value = 0;
    bool error_c = 0;
    
    //Parse:
    for(Token token : tokens){
        if(name){
            //In previous parser code we were using a condition to check whether first token is identifier or not but we don't 
            //need it since it's done by isVarDecl function during checking.
            node.name = token.token;
            name = 0;
        }
        else if(token.token == ":"){
            if(type){
                error(line,"invalid use of : token as a type.");
            }
            else{
                type = 1;
                node.type_ = "";
                node.type_infr = 0;
            }
        }
        else if(type && token.token != "="){
            if(token.token == "<" || token.token == ">" || token.type == IDENTIFIER){
                node.type_ += token.token;
            }
            else{
                error(line,"invalid use of " + token.token + "token as a type.");
            }
        }
        else if(token.token == "="){
            if(type){
                type = 0;
                value = 1;
            }
            else if(value){
                error(line,"invalid use of = as rvalue, did you mean == ?");
            }
        }
        else{
            node.value.expr += (token.token);
        }
    }
    //Type checking
    if(node.type_ != "NONE"){
        if(!table.isPresent((parent*1000)+indent_level,node.type_,ST_CLASS)){
            error(line, "undefined type '"+node.type_+"'.");
        }
    }
    //Add it to symbol table:

    if(error_c == 0){
        Variable var;
        var.name = node.name;
        var.type = node.type_;
        table.addVariable(parent,indent_level,var);

    }
    return node;
}

VarAssign ParseVarAssign(TokenStream tokens,int line,int parent, int indent){
    VarAssign node;
    TokenStream val_expr;
    //States
    bool name = 1;
    bool value = 0;
    bool error_c = 0;
    for(Token token : tokens){
        if(name){
            if(token.type == IDENTIFIER){
                node.name = token.token;
                name = 0;
                value = 1;
            }
            else{
                error(line, "expected an identifier");
                error_c = 1;
            }
        }
        else if(value){
            node.value.expr += token.token;
        }
    }
    // if(!error_c){
    //     node.value = ParseExpr(val_expr, line, indent, parent);
    // }
    // else{}
    return node;
}

//////////////////////////////////////////////////////////////////
bool isVarDecl(TokenStream tokens, int current_scope){
    bool state = 0;
    if(tokens[0].type == IDENTIFIER && (tokens[1].token == ":" || tokens[1].token == "=") && !table.isVariablePresent(tokens[0].token,current_scope))
     state = 1;
    return state;
}
bool isVarAssign(TokenStream tokens, int current_scope){
    bool state = 0;
    if(tokens[0].type == IDENTIFIER && (tokens[1].token == "=") && table.isVariablePresent(tokens[0].token,current_scope))
     state = 1;
    return state;
}



NODE_TYPE StatementType(TokenStream tokens, int en_scope){
    NODE_TYPE type;
    
    if(isVarDecl(tokens,en_scope)){
        type = VAR_DECLARATION;
    }
    else if(isVarAssign(tokens,en_scope)){
        type = VAR_ASSIGNMENT;
    }
    else{
        type = EXPR_TYPE;
    }
    return type;
}
int getIndentLevel(TokenStream tokens){
    int indent = 0;
    for(Token token : tokens){
        if(token.type == INDENT)
            indent++;
    }return indent;
}
TokenStream removeIndent(TokenStream tokens){
    TokenStream newTokens;
    bool indent = 0;
    if(tokens[0].type == INDENT){
        indent = 1;
    }
    for(Token token : tokens){
        if(token.type == INDENT ){
            
        }
        else if(indent && token.type != INDENT){
            indent = 0;
            newTokens.push_back(token);
        }
        else if(!indent){
            newTokens.push_back(token);
        }
    }
    return newTokens;
}


string Parse(vector<TokenStream> code)
{
    //Load the C written builtins
    load_builtins_to_table();
    //Resulting code
    string codeString = "";
    //Scope managers
    int scope = 0;
    int parent = 1;
    int line_no = 1;
    //////////////////////////////
    for(TokenStream line : code)
    {

        //Get the current scope by finding indents
        scope = getIndentLevel(line);
        //Removing all indentation from the stream
        line = removeIndent(line);

        //The encoding of scope will be helping to distinguish between different scopes 
        //Process : (<parent> * 1000) + <current_scope>
        int en_scope = (parent*1000)+scope;
        switch(StatementType(line,en_scope)){
            case VAR_DECLARATION:
            {
                VarDecl node = ParseVarDecl(line,line_no,scope,parent);
                codeString += VarDecl_visitor(node)+"\n";
                line_no++;
                break;
            }
            case EXPR_TYPE:
            {
                Expr node = ParseExpr(line,line_no,scope,parent);
                codeString += Expr_visitor(node)+"\n";
                line_no++;
                break;
            }
        }
    }

    return codeString;
}

#endif // PARSER_CSQ4
