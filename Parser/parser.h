#if !defined(PARSER_H_CSQ4)
#define PARSER_H_CSQ4
#include "../Runtime/core.h"
#include "../AST/ast.h"
#include "../AST/visitor.h"

/*
Upper layer syntax checking in which we don't have to do much instead it will roughly match the 
syntax and returns the possible type which could be futher verified.
*/
bool VarDecl_check(TokenStream tokens){
    /*Syntax : <identifier> | :=<value>
    
    */
    bool valid_state = false;
    if(tokens[0].type == IDENTIFIER)
    {
        if(tokens[1].token == ":=")
        {
            if(tokens.size()>2)
            {
                valid_state = 1;
                for(int i = 2;i<tokens.size();i++){
                    if(tokens[i].type == KEYWORD){
                        RuntimeError("syntax error by using keyword '" + tokens[i].token + "' inside a value.");
                        valid_state = 0;
                    }
                    else if(tokens[i].token == "="){
                        RuntimeError("syntax error by using '" + tokens[i].token + "' inside a value.");
                        valid_state = 0;
                    }
                }
            }
            else{
                RuntimeError("expected a value after ':='.");
                valid_state = 0;
            }
        }
    }
    return valid_state;
}

//For variable reassignment
bool VarAssign_Check(TokenStream tokens){
    bool valid = 0;
    if(tokens[0].type == IDENTIFIER)
    {
        if(tokens[1].token == "="){
            if(tokens.size()>2){
                valid = 1;
            }
            else{
                RuntimeError("expected a value after '='.");
                valid = 0;
            }
        }
    }
    return valid;
}

//Function to parse expressions and report the errors.
ExprNode parse_ExprNode(TokenStream tokens){
    ExprNode node;

    for(int i = 0;i<tokens.size();i++)
    {   
        Token token = tokens[i];
        if(token.type == IDENTIFIER)
        {
            //Check is the identifier defined in table?
            if(inTable(token.token))
            {
                Token val;
                if(memory[SymTable[token.token].var.value_address].type == FLOAT){
                    val.token = to_string(memory[SymTable[token.token].var.value_address].fval);
                    val.type = VALUE;
                }
                else{
                    val.token = memory[SymTable[token.token].var.value_address].sval;
                    val.type = STR;
                }
                node.tokens.push_back(val);
            }
            else
            {
                RuntimeError("undefined name '" + token.token + "'.");
            }
        }
        else{
            //Just for now couldn't be used during actual production.
            node.tokens.push_back(token);
        }
    }
    return node;
}

//Parsing without reporting any error because when this function is called before it
//VarDecl_check will be called.
VarDeclNode parse_VarDecl(TokenStream tokens){
    VarDeclNode node;
    //Default type:
    node.var_type = "any";
    //lower level rep for value (in terms of tokens)
    TokenStream valstream;
    //Parsing States
    bool name = 1;
    bool equal = 0;
    bool value = 0;

    //
    for(Token token : tokens){
        if(name)
        {
            node.identifier = token.token;
            name = 0;
        }
        else if(!equal && token.token == ":="){
            value = 1;
            equal = 1;
        }
        else if(equal){
            node.value.tokens.push_back(token);
        }
    }
    
    return node;
}
//for var reassignment
VarAssignNode parse_VarAssign(TokenStream tokens){
    VarAssignNode node;
    //States
    bool name = 1;
    bool val = 0;
    
    for(Token token : tokens){
        if(name){
            node.identifier = token.token;
            name = 0;
            
        }
        else if(!val && token.token == "="){
            val = 1;
        }
        else if(val){
            node.value.tokens.push_back(token);
        }
    }
    return node;
}

PrintNode parse_PrintStatement(TokenStream tokens){
    PrintNode node;
    for(int i = 1;i<tokens.size();i++){
        node.value.tokens.push_back(tokens[i]);
        
    }
    return node;
}

IfStmtNode parse_IfStmt(TokenStream tokens){
    IfStmtNode node;
    //states
    bool condition = 0;
    // bool end = 0;
    for(Token token : tokens){
        if(token.token == "if")
            condition = 1;
        else
            node.condition.tokens.push_back(token);
    }
    return node;
}

bool isVarDecl(TokenStream tokens){
    if(tokens[0].type == IDENTIFIER && tokens[1].token == ":="){
        return 1;
    }return 0;
}

bool isPrintStmt(TokenStream tokens){
    if(tokens[0].token == "print"){
        return 1;
    }return 0;
}

bool isVarAssign(TokenStream tokens){
    if(tokens[0].type == IDENTIFIER && tokens[1].token == "="){
        return 1;
    }return 0;
}

bool isIfStmt(TokenStream tokens){
    if(tokens[0].token == "if"){
        return 1;
    }
    return 0;
}

bool isElifStmt(TokenStream tokens){
    if(tokens[0].token == "elif"){
        return 1;
    }
    return 0;
}

bool isElseStmt(TokenStream tokens){
    if(tokens[0].token == "else"){
        return 1;
    }
    return 0;
}

bool isWhileStmt(TokenStream tokens){
    if(tokens[0].token == "while"){
        return 1;
    }
    return 0;
}

struct CodeBlock{
    vector<ASTNode> nodes;
};

/*
Implement the parser
*/



CodeBlock Parser(vector<TokenStream> code){
    CodeBlock block;
    int error_c = 0;
    int child_indent = 0;
    //Iterate and parse
    for(int i=0;i<code.size();i++)
    {
        TokenStream line = code[i];
        if(isVarDecl(line)){
            //First error check to check validity.
            bool valid = VarDecl_check(line);
            if(valid){
                VarDeclNode node = parse_VarDecl(line);
                //Visit on the spot
                block.nodes.push_back(*((ASTNode*)(&node)));
            }
        }
        else if(isVarAssign(line)){
            bool valid = VarAssign_Check(line);
            if(valid){
                VarAssignNode node = parse_VarAssign(line);
                //Visit on the spot
                block.nodes.push_back(*((ASTNode*)(&node)));
            }
        }
        else if(isPrintStmt(line)){
            PrintNode node = parse_PrintStatement(line);
            block.nodes.push_back(*((ASTNode*)(&node)));
        }
        else if(isIfStmt(line)){
            int current_indent = getIndentLevel(line);
            child_indent++;
            //Now parse and check whether to eval it or not here eval means visiting it's body
            IfStmtNode node = parse_IfStmt(line);
            //After all necessary data we are going to parse the body by looking at the indent level
            block.nodes.push_back(*((ASTNode*)(&node)));
        }
        else{}
    }
    return block;
};

//This is the final stage to produce C++ code in which we read the inputs from the Parser function in the form of Nodes
string Compile(CodeBlock nodes)
{
    string res;
    for(int i=0;i<nodes.nodes.size();i++){
        ASTNode node = nodes.nodes[i];
        switch(node.type){
            case VAR_DECL:{
                break;
            }
            case VAR_ASSIGN:{
                break;
            }
            case PRINT:{
                break;
            }
            case IF_STMT:{
                IfStmtNode _node = *((IfStmtNode*)(&node));
                if(eval(_node.condition.tokens) == 1){
                    res += visit(&_node.body) + "\n";
                    //No need to eval other statements like elif and else
                    if(nodes.nodes[i+1].type == ELIF_STMT){
                        i++;
                        if(nodes.nodes[i+1].type == ELSE_STMT){
                            i++;
                        }
                    }
                }
                else{
                    //move on to next node since current one is false
                    
                }
                break;
            }
            case ELIF_STMT:{

            }
        }
    }
    return res;
}
#endif // PARSER_H_CSQ4
