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
    UNKNOWN = 13,
};

//This enum field will give even more detail about symbols excluding identifiers, numbrs and keywords
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
    MOD = 28,
}STOKEN;

//Struct for tokens
struct Token{
    string token;
    TokenType type;
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
                return BSLASH;
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


vector<Token> tokenize(string source_code) {
    vector<Token> tokens;
    string current_string, str_input;
    int current_line = 1;
    //Indentation count;
    int IndentCount = 0;
    //Some states
    bool indent_ended = true;
    bool indentation_present = false;
    bool char_start = false;
    bool string_presence = false;
    bool comment = false;
    if(source_code[0] == '#')
        ignore;
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
                tok.token = "\""+str_input+"\"";
                tok.type = STR;
                tokens.push_back(tok);
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
            case GREATER:{
                switch(symbolType(tokens[i+1])){
                    case EQUAL:{
                        Token token;
                        token.token = ">=";
                        token.type = COPERATOR;
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
            default:{
                filtered_Tokens.push_back(tokens[i]);
            }
        }
    }

    return filtered_Tokens;
}

#endif // tokenizer_Csq4
