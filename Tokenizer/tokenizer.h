/*
----------------------------------------------The tokenizer for Csq4---------------------------------------------------
*/
#if !defined(tokenizer_Csq4)
#define tokenizer_Csq4
//Importing grammar and token type
#include "../Grammar/grammar.h"
#define ignore

#define MAX_INDENT_LEVEL 500

//Types of token
enum TokenType {
    KEYWORD = 1,
    IDENTIFIER = 2,
    STR = 3,
    VALUE = 4,
    SYMBOL = 5,
    AROPERATOR = 6,
    ASOPERATOR = 7,
    COPERATOR = 8,
    LOPERATOR = 9,
    COMMENT =10,
    INDENT = 11,
    NEWLINE = 12,
    ACCESS_OPERATOR = 13,
    UNKNOWN = 14,
    BLANK = 15,
};

//This enum field will give even more detail about symbols excluding identifiers, numbers and keywords
typedef enum{
    LBRACE = 1,
    RBRACE = 2,
    LPAREN = 3,
    RPAREN = 4,
    LBRACK = 5,
    RBRACK = 6,
    PERCENT = 7,
    EQUAL = 8,
    TILDE = 9,
    COMMA = 10,
    GREATER = 11,
    LESSER = 12,
    SEMI = 13,
    COLAN = 14,
    PLUS = 15,
    MINUS = 16,
    STAR = 17,
    BSLASH = 18,
    HASHTAG = 19,
    AMPER = 20,
    VBAR = 21,
    NOT = 22,
    HAT = 23,
    NOTSYMBOL = 24,
    DOT = 25,
    OR = 26,
    AND = 27,
    MOD = 28, // %
    FSLASH = 29, 
    WALRUS = 30, // :=
}STOKEN;

//Struct for tokens
struct Token{
    string token;
    TokenType type;
    Token(){}
    Token(string tok, TokenType type_){
        token = tok;
        type = type_;
    }
};  

//This function will be returning an object to Token struct.
Token addToken(TokenType type, string value){
    Token token;
    token.token = value;
    token.type = type;
    return token;
}

//This function will return a bool state which will decide whether an item is present in vector or not.
bool in(string item, vector<string> ls){
    bool state = false;
    for(auto item_ : ls)
        if(item == item_){
            state = true;
            break;
        }
    return state;
}

//Checking is it an identifier
bool isIdentifier(string val) {
    regex identifier_regex(IDENTIFIERS);
    return regex_match(val, identifier_regex);
}
bool isInt(string val){
    regex int_regex(INTEGER);
    return regex_match(val, int_regex);
}
bool isDecimal(string val){
    regex Decimal_regex(DECIMAL);
    return regex_match(val, Decimal_regex);
}

bool isValue(string val){
    bool state = false;
    if(isDecimal(val) || isInt(val)){
        state = true;
    }
    return state;
}

bool isComment(string val){
    bool state = val == "#";
    return state;
}
//Is operator
bool isLogicalOperator(string val){
    bool state = false;
    if(in(val,LOGICAL_OPERATORS)){
        state = true;
    }
    return state;
}
bool isAssignmentOperator(string val){
    bool state = false;
    if(in(val,ASSIGNMENT_OPERATORS)){
        state = true;
    }
    return state;
}
bool isComparisonOperator(string val){
    bool state = false;
    if(in(val,COMPARISON_OPERATORS)){
        state = true;
    }
    return state;
}
bool isArithmeticOperator(string val){
    bool state = false;
    if(in(val, ARITHMETIC_OPERATORS)){
        state = true;
    }
    return state;
}

bool isOperator(string val){
    bool state = false;
    if(isArithmeticOperator(val) || isLogicalOperator(val) || isAssignmentOperator(val) || isComparisonOperator(val)){
        state = true;
    }
    return state;
}

bool isSymbol(string val){
    bool state = false;
    if(in(val,SYMBOLS)){
        state = true;
    }
    return state;
}

bool isSymbolLaterals(string val){
    bool state = false;
    if(isSymbol(val) || isOperator(val)){
        state = true;
    }
    return state;
}

bool isKeyword(string val){
    bool state = false;
    if(in(val, KEYWORDS_TABLE)){
        state = true;
    }
    return state;
}




//This is the checking section which will take a token and then check it's type.
Token check(string val,int line){
    Token token;
    if(isKeyword(val)){
        token.token = val;
        token.type = KEYWORD;
    }
    else if(isOperator(val)){
        if(isArithmeticOperator(val)){
            token.token = val;
            token.type = AROPERATOR;
        }
        else if(isLogicalOperator(val)){
            token.token = val;
            token.type = LOPERATOR;
        }
        else if(isAssignmentOperator(val)){
            token.token = val;
            token.type = ASOPERATOR;
        }
        else if(isComparisonOperator(val)){
            token.token = val;
            token.type = COPERATOR;
        }
    }
    else if(isValue(val)){
        token.token = val;
        token.type = VALUE;
    }
    else if(isIdentifier(val)){
        token.token = val;
        token.type = IDENTIFIER;
    }
    else if(isSymbol(val)){
        token.token = val;
        token.type = SYMBOL;
    }
    else{
        token.token = val;
        token.type = UNKNOWN;
    }
    return token;
}

//This function will return a brief info about the symbols.
STOKEN symbolType(Token token){
    switch(token.type){
        case ASOPERATOR:{
            if(token.token == "=")
                return EQUAL;
        }
        case AROPERATOR:{
            if(token.token == "+")
                return PLUS;
            else if(token.token == "-")
                return MINUS;
            else if(token.token == "*")
                return STAR;
            else if(token.token == "/")
                return FSLASH;
            else if(token.token == "%")
                return MOD;
            else if(token.token == "^")
                return HAT;
        }
        case SYMBOL:{
            if(token.token == "!")
                return NOT;
            else if(token.token == "|")
                return VBAR;
            else if(token.token == "&")
                return AMPER;
            else if(token.token == "{")
                return LBRACE;
            else if(token.token == "}")
                return RBRACE;
            else if(token.token == "(")
                return LPAREN;
            else if(token.token == ")")
                return RPAREN;
            else if(token.token == "[")
                return LBRACK;
            else if(token.token == "]")
                return RBRACK;
            else if(token.token == ".")
                return DOT;
            else if(token.token == ",")
                return COMMA;
            else if(token.token == ":")
                return COLAN;
            else if(token.token == ";")
                return SEMI;
            else if(token.token == "~")
                return TILDE;
        }
        case LOPERATOR:{
            if(token.token == "or")
                return OR;
            else if(token.token == "and")
                return AND;
            else if(token.token == "not")
                return NOT;
        }
        case COPERATOR:{
            if(token.token == ">")
                return GREATER;
            else if(token.token == "<")
                return LESSER;
            
        }
        default:{
            return NOTSYMBOL;
        }
    }
}

int TokenizerLine = 1;
//Total count of errors.
int error_count = 0;

void error(int line, string msg){
    printf("Error [%d]: at line %d, %s\n",error_count+1, line, msg.c_str());
    error_count++;
}


//This function will be checking the count of tokens 
int TokenCount(vector<Token> tokens, Token token)
{
    int count = 0;
    for(Token t : tokens){
        if(t.token == token.token && t.type)
         count++;
    }
    return count;
}



vector<Token> tokenize(string source_code) {
    vector<Token> tokens;
    string current_string, str_input, code_;

    
    int current_line = 1;
    //Indentation count;
    int IndentCount = 0;
    //Some states
    bool indent_ended = true;
    bool indentation_present = false;
    bool char_start = false;
    bool string_presence = false;
    bool comment = false;
    if(source_code[0] == '#'){
        Token t;
        t.token = "ignore";
        t.type = KEYWORD;
        tokens = {t};
    }
    else{
        //Checking for indentation.
        //This string will store the code without indentations.
        if(source_code[0] == ' '){
            indentation_present = true;
            string temp_source;
            for(int i = 0;i<source_code.length();i++){
                if(source_code[i] == ' ' && char_start == false){
                    Token indent;
                    indent.token = ' ';
                    IndentCount++;
                    indent.type = INDENT;
                    tokens.push_back(indent);
                    indent_ended = false; 
                }
                else if(source_code[i] != ' ' && char_start == false && indent_ended == false){
                    indent_ended = true;
                    temp_source.push_back(source_code[i]);
                    char_start = true;
                }
                else if(char_start == 1)
                    temp_source.push_back(source_code[i]);
            }
            source_code = temp_source;
        }
        for (int i = 0; i < source_code.length(); i++) {
            char c = source_code[i];
            if ((c == ' ' || c == '\n' || c == '\t' || isSymbolLaterals(string(1, c))) && string_presence == false) { // if whitespace or symbol character, handle separately
                if (c == '\n') {
                    current_line++;
                    Token newline;
                    newline.token = "\n";
                    newline.type = NEWLINE;
                    tokens.push_back(newline);
                }
                if (current_string.length() > 0) { // if non-empty string, check if it matches any operator, keyword, or value
                    Token token = check(current_string, current_line);
                    tokens.push_back(token);
                    current_string = "";
                }
                if (isSymbolLaterals(string(1, c))) { // handle symbol
                    tokens.push_back(check(string(1,c),current_line));
                }
            }
            else if((c == '"' || c == '\'') && string_presence == false){
                string_presence = true;
            }
            else if((c == '"' || c == '\'') && string_presence == true){
                Token tok;
                tok.token = "'"+str_input+"'";
                // tok.token = ""+str_input+"";
                tok.type = STR;
                tokens.push_back(tok);
                str_input = "";
                string_presence = false;
            }
            else if((c != '"' || c != '\'') && string_presence == true){
                str_input.push_back(c);
            }
            else { // if non-whitespace or symbol character, append to current string
                current_string += c;
            }
        }

        if (current_string.length() > 0) { // process the last string
            Token token = check(current_string, current_line);
            tokens.push_back(token);
        }

        if (string_presence) { // handle unclosed string literal
            printf("Error: unclosed string literal at line %d\n", current_line);
            exit(1);
        }
    }

    vector<Token> filtered_Tokens;
    for(int i = 0;i<tokens.size();i++){
        switch(symbolType(tokens[i])){
            case NOT:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "!=";
                        token.type = COPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
                
            }
            case EQUAL:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "==";
                        token.type = COPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case PLUS:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "+=";
                        token.type = ASOPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case MINUS:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "-=";
                        token.type = ASOPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                    case GREATER:{
                        Token token;
                        token.token = "->";
                        token.type = ASOPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case STAR:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "*=";
                        token.type = ASOPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case FSLASH:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "/=";
                        token.type = ASOPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            
            case LESSER:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = "<=";
                        token.type = COPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case AMPER:{
                switch(symbolType(tokens[i+1])){
                    case AMPER:{
                        Token token;
                        token.token = "&&";
                        token.type = COPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case VBAR:{
                switch(symbolType(tokens[i+1])){
                    case VBAR:{
                        Token token;
                        token.token = "||";
                        token.type = COPERATOR;
                        filtered_Tokens.push_back(token);
                        i = i + 2;
                    }
                }
            }
            case COLAN:{
                if(i != tokens.size()-1){
                    switch(symbolType(tokens[i+1])){
                        case EQUAL:{
                            Token token;
                            token.token = ":=";
                            token.type = ASOPERATOR;
                            filtered_Tokens.push_back(token);
                            i = i + 2;
                        }
                    
                    }
                }
                else{
                    Token token;
                    token.token = ":";
                    token.type = SYMBOL;
                    filtered_Tokens.push_back(token);
                }
            }
            default:{
                filtered_Tokens.push_back(tokens[i]);
            }
        }
    }

    //Tokens for syntax check.
    Token SY_Lparen, SY_Rparen, SY_Lbrac, SY_Rbrac, SY_Lbrace, SY_Rbrace;
    SY_Lparen.token = "(";
    SY_Lparen.type = SYMBOL;
    SY_Rparen.token = ")";
    SY_Rparen.type = SYMBOL;
    SY_Lbrac.token = "[";
    SY_Lbrac.type = SYMBOL;
    SY_Rbrac.token = "]";
    SY_Rbrac.type = SYMBOL;
    SY_Lbrace.token = "{";
    SY_Lbrace.type = SYMBOL;
    SY_Rbrace.token = "}";
    SY_Rbrace.type = SYMBOL;
    if(TokenCount(filtered_Tokens, SY_Lparen) != TokenCount(filtered_Tokens, SY_Rparen)){
        printf("Error[%d]: At line %d, parenthesis aren't correctly closed.\n",error_count, TokenizerLine);
        error_count++;
    }
    else if(TokenCount(filtered_Tokens, SY_Lbrace) != TokenCount(filtered_Tokens, SY_Rbrace)){
        printf("Error[%d]: At line %d, square brackets aren't correctly closed.\n",error_count, TokenizerLine);
        error_count++;
    }
    else if(TokenCount(filtered_Tokens, SY_Lbrace) != TokenCount(filtered_Tokens, SY_Rbrace)){
        printf("Error[%d]: At line %d, curly braces aren't correctly closed.\n",error_count, TokenizerLine);
        error_count++;
    }
    TokenizerLine++;
    // vector<Token> tokens__;
    // for(int i =0;i<filtered_Tokens.size();i++){
    //     if(filtered_Tokens[i].type == VALUE){
    //         if(filtered_Tokens[i+1].token == "."){
    //             if(filtered_Tokens[i+2].type == VALUE){
    //                 // Token __ctoken;
    //                 // __ctoken.type = VALUE;
    //                 // __ctoken.token = filtered_Tokens[i].token + "." + filtered_Tokens[i+2].token;
    //                 // tokens__.push_back(__ctoken);
    //             }
    //             else{
    //                 printf("Error: unexpected a value after .");
    //                 // exit(0);
    //             }
                
    //         }
    //         else{
    //             tokens__.push_back(filtered_Tokens[i]);
    //         }
    //     }
    //     else{
    //         tokens__.push_back(filtered_Tokens[i]);
    //     }
    // }

    return filtered_Tokens;
}

Token create(TokenType type, string token){
    Token tok;
    tok.type = type;
    tok.token = token;
    return tok;
}

//Function to convert stream of tokens into string without changing.
string tokenS_to_string(vector<Token> tokens){
    string s;
    for(Token token : tokens){
        if(token.type == VALUE || token.token == "."){
            s += token.token;
        }
        else{
            s += token.token + " ";
        }
    }
    return s;
}

//This function will tell us the number of indent present in the tokenstream
int getIndentLevel(vector<Token> tokens){
    int indent_ = 0;
    for(Token token : tokens){
        if(token.type == INDENT)
            indent_++;
        else
            break;
    }return indent_;
}

void traverseTokenStreams(vector<vector<Token>> tokens){
    for(vector<Token> line : tokens){
        printf("%ld : ", line.size());
        for(Token token : line){
            printf("'%s',",token.token.c_str());
        }
        printf("\n");
    }
}

void traverseTokenStream(vector<Token> line){
    for(Token token : line){
        printf("'%s',",token.token.c_str());
    }
    printf("\n");
}

#endif // tokenizer_Csq4
