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
            if(token.token != ":")
                node.condition.tokens.push_back(token);
            else
                break;
    }
    return node;
}
ElifStmtNode parse_ElifStmt(TokenStream tokens){
    ElifStmtNode node;
    //states
    bool condition = 0;
    // bool end = 0;
    for(Token token : tokens){
        if(token.token == "elif")
            condition = 1;
        else
            if(token.token != ":")
                node.condition.tokens.push_back(token);
            else
                break;
    }
    return node;
}
ElseStmtNode parse_ElseStmt(TokenStream tokens){
    ElseStmtNode node;
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

bool isTypeStmt(TokenStream tokens){
    if(tokens[0].token == "type"){
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

//Parse by single statement. it will not parse block based expressions.
pair<ASTNode*, NodeType> parse(TokenStream line){
    if(isVarDecl(line)){
        bool valid = VarDecl_check(line);
        if (valid) {
            VarDeclNode* node = new VarDeclNode(parse_VarDecl(line));
            pair<ASTNode*, NodeType> _res;
            _res.first = node;
            _res.second = VAR_DECL;
            return _res;
        }
    }
    else if(isVarAssign(line)){
        bool valid = VarAssign_Check(line);
        if (valid) {
            VarAssignNode* node = new VarAssignNode(parse_VarAssign(line));
            pair<ASTNode*, NodeType> _res;
            _res.first = node;
            _res.second = VAR_ASSIGN;
            return _res;
        }
    }
    else{
        PrintNode* node = new PrintNode(parse_PrintStatement(line));
        pair<ASTNode*, NodeType> _res;
        _res.first = node;
        _res.second = PRINT;
        return _res;
    }return pair<ASTNode*, NodeType>(new UnknownNode(), UNKNOWN_NODE);
}

TokenStream removeIndent(TokenStream tokens){
    TokenStream tok;
    for(Token token: tokens){
        if(token.type == INDENT){}
        else{
            tok.push_back(token);
        }
    }return tok;
}

// Forward declaration of the Parser function
vector<pair<ASTNode*, NodeType>> Parser(const vector<TokenStream>& code, int startIndex, int targetIndent);

auto Parser(const vector<TokenStream>& code) {
    vector<pair<ASTNode*, NodeType>> block;
    int error_c = 0;
    NodeType block_type;
    int block_indent;
    IfStmtNode if_block;
    ElseStmtNode else_block;
    ElifStmtNode elif_block;

    for (int i = 0; i < code.size(); i++) {
        TokenStream line = code[i];
        int indent = getIndentLevel(line);
        
        // Skip lines that are only INDENT tokens
        if (line.size() == 1 && line[0].type == INDENT) {
            continue;
        }

        if (isVarDecl(line)) {
            // Handle variable declaration
            bool valid = VarDecl_check(line);
            if (valid) {
                VarDeclNode* node = new VarDeclNode(parse_VarDecl(line));
                pair<ASTNode*, NodeType> _res;
                _res.first = node;
                _res.second = VAR_DECL;
                block.push_back(_res);
            }
        }
        else if (isVarAssign(line)) {
            // Handle variable assignment
            bool valid = VarAssign_Check(line);
            if (valid) {
                VarAssignNode* node = new VarAssignNode(parse_VarAssign(line));
                pair<ASTNode*, NodeType> _res;
                _res.first = node;
                _res.second = VAR_ASSIGN;
                block.push_back(_res);
            }
        }
        else if (isPrintStmt(line)) {
            // Handle print statement
            bool valid = 1;
            if (valid) {
                PrintNode* node = new PrintNode(parse_PrintStatement(line));
                pair<ASTNode*, NodeType> _res;
                _res.first = node;
                _res.second = PRINT;
                block.push_back(_res);
            }
        }
        else if (isIfStmt(line)) {
            // Handle if statement
            IfStmtNode* node = new IfStmtNode(parse_IfStmt(line));
            bool ended = false;
            int child_indent = indent + 1;
            TokenStream line_;
            while (!ended) {
                i = i + 1;
                if (i >= code.size()) {
                    ended = true;  // Exit the loop if end of code is reached
                    break;
                }
                line_ = code[i];
                int line_indent = getIndentLevel(line_);
                line_ = removeIndent(line_);
                if (line_indent == child_indent) {
                    ASTNode* parsedNode = parse(line_).first;
                    node->body.statements.push_back(parsedNode);
                }
                else if (line_indent > child_indent) {
                    // Handle statements at the same indentation level
                    std::vector<ASTNode*> innerStatements;
                    while (line_indent == child_indent) {
                        ASTNode* innerNode = parse(line_).first;
                        innerStatements.push_back(innerNode);
                        i = i + 1;
                        if (i >= code.size()) {
                            ended = true;  // Exit the loop if end of code is reached
                            break;
                        }
                        line_ = code[i];
                        line_indent = getIndentLevel(line_);
                        line_ = removeIndent(line_);
                    }
                    // Create a block node and assign the inner statements
                    BlockNode* blockNode = new BlockNode();
                    blockNode->statements = innerStatements;
                    // Set the block node as the body of the if statement
                    node->body.statements.push_back(blockNode);
                    // Adjust the index to reprocess the current line
                    i = i - 1;
                }
                else {
                    ended = true;  // Exit the loop if indentation level is lower
                    i = i - 1;  // Adjust the index to reprocess the current line
                }
            }
            // Then push back to block
            block.push_back(std::make_pair(node, IF_STMT));
        }
        else if (isElifStmt(line)) {
            // Handle elif statement
            ElifStmtNode* node = new ElifStmtNode(parse_ElifStmt(line));
            bool ended = false;
            int child_indent = indent + 1;
            TokenStream line_;
            while (!ended) {
                i = i + 1;
                if (i >= code.size()) {
                    ended = true;  // Exit the loop if end of code is reached
                    break;
                }
                line_ = code[i];
                int line_indent = getIndentLevel(line_);
                line_ = removeIndent(line_);
                if (line_indent == child_indent) {
                    ASTNode* parsedNode = parse(line_).first;
                    node->body.statements.push_back(parsedNode);
                }
                else if (line_indent > child_indent) {
                    // Handle statements at the same indentation level
                    std::vector<ASTNode*> innerStatements;
                    while (line_indent == child_indent) {
                        ASTNode* innerNode = parse(line_).first;
                        innerStatements.push_back(innerNode);
                        i = i + 1;
                        if (i >= code.size()) {
                            ended = true;  // Exit the loop if end of code is reached
                            break;
                        }
                        line_ = code[i];
                        line_indent = getIndentLevel(line_);
                        line_ = removeIndent(line_);
                    }
                    // Create a block node and assign the inner statements
                    BlockNode* blockNode = new BlockNode();
                    blockNode->statements = innerStatements;
                    // Set the block node as the body of the elif statement
                    node->body.statements.push_back(blockNode);
                    // Adjust the index to reprocess the current line
                    i = i - 1;
                }
                else {
                    ended = true;  // Exit the loop if indentation level is lower
                    i = i - 1;  // Adjust the index to reprocess the current line
                }
            }
            // Then push back to block
            block.push_back(std::make_pair(node, ELIF_STMT));
        }
        else if (isElseStmt(line)) {
            // Handle if statement
            ElseStmtNode* node = new ElseStmtNode(parse_ElseStmt(line));
            bool ended = false;
            int child_indent = indent + 1;
            TokenStream line_;
            while (!ended) {
                i = i + 1;
                if (i >= code.size()) {
                    ended = true;  // Exit the loop if end of code is reached
                    break;
                }
                line_ = code[i];
                int line_indent = getIndentLevel(line_);
                line_ = removeIndent(line_);
                if (line_indent == child_indent) {
                    ASTNode* parsedNode = parse(line_).first;
                    node->body.statements.push_back(parsedNode);
                }
                else if (line_indent > child_indent) {
                    // Handle statements at the same indentation level
                    std::vector<ASTNode*> innerStatements;
                    while (line_indent == child_indent) {
                        ASTNode* innerNode = parse(line_).first;
                        innerStatements.push_back(innerNode);
                        i = i + 1;
                        if (i >= code.size()) {
                            ended = true;  // Exit the loop if end of code is reached
                            break;
                        }
                        line_ = code[i];
                        line_indent = getIndentLevel(line_);
                        line_ = removeIndent(line_);
                    }
                    // Create a block node and assign the inner statements
                    BlockNode* blockNode = new BlockNode();
                    blockNode->statements = innerStatements;
                    // Set the block node as the body of the if statement
                    node->body.statements.push_back(blockNode);
                    // Adjust the index to reprocess the current line
                    i = i - 1;
                }
                else {
                    ended = true;  // Exit the loop if indentation level is lower
                    i = i - 1;  // Adjust the index to reprocess the current line
                }
            }
            // Then push back to block
            block.push_back(std::make_pair(node, ELSE_STMT));
        }
    }

    return block;
}

vector<pair<ASTNode*, NodeType>> Parser(const vector<TokenStream>& code, int startIndex, int targetIndent) {
    vector<TokenStream> block;
    for (int i = startIndex + 1; i < code.size(); i++) {
        TokenStream line = code[i];
        int indent = getIndentLevel(line);
        if (indent == targetIndent) {
            block.push_back(line);
        }
        else if (indent < targetIndent) {
            break;
        }
    }
    return Parser(block);
}


// /*
// We are saying this is the function which compiles the nodes but in the hood it behaves much like the
// JIT.
// */
string Compile(vector<pair<ASTNode*, NodeType>> nodes) {
    string code;

    for (int i = 0; i < nodes.size(); i++) {
        int type = nodes[i].second;
        ASTNode* _node = nodes[i].first;

        switch (type) {
            case VAR_DECL: {
                VarDeclNode* node = static_cast<VarDeclNode*>(_node);
                code += "allocateVar(\"" + node->identifier + "\", \"" + node->var_type + "\", " + visit_ExprNode(node->value) + ");\n";
                break;
            }
            case VAR_ASSIGN: {
                VarAssignNode* node = static_cast<VarAssignNode*>(_node);
                code += "assignVar(\"" + node->identifier + "\", " + visit_ExprNode(node->value) + ");\n";
                break;
            }
            case PRINT: {
                PrintNode* node = static_cast<PrintNode*>(_node);
                code += "print(" + visit_ExprNode(node->value) + ");\n";
                break;
            }
            case IF_STMT:{
                IfStmtNode* node = static_cast<IfStmtNode*>(_node);
                code += visit(node);
                break;
            }

            case ELIF_STMT:{
                ElifStmtNode* node = static_cast<ElifStmtNode*>(_node);
                code += visit(node);
                break;
            }

            case ELSE_STMT:{
                ElseStmtNode* node = static_cast<ElseStmtNode*>(_node);
                code += visit(node);
                break;
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < nodes.size(); i++) {
        delete nodes[i].first;
    }

    return code;
}

#endif // PARSER_H_CSQ4
