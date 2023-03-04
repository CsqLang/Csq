#if !defined(tokenizer_Csq4)
#define tokenizer_Csq4
//Importing grammar and token type
#include "../Grammar/grammar.h"


//Types of token
enum TokenType {
    OPERATOR,
    KEYWORD,
    IDENTIFIER,
};

//Type of line
enum LINE_TYPE{
    CLASS_DEF,
    VARIABLE_DEF,
    FUNCTION_DEF,
    OTHER_STATEMENTS,
};

//Struct for tokens
struct Token{
    string token;
    TokenType type;
};  

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
//Is operator
bool isOperator(string val){
    bool state = false;
    if(in(val, ARITHMETIC_OPERATORS) || in(val,COMPARISON_OPERATORS) || in(val,ASSIGNMENT_OPERATORS)  || in(val,LOGICAL_OPERATORS)){
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
        token.token = val;
        token.type = OPERATOR;
    }
    else if(isIdentifier(val)){
        token.token = val;
        token.type = IDENTIFIER;
    }
    else{
        printf("Unrecognized '%s' at line %d\n",val.c_str(),line);
        exit(0);
    }
    return token;
}


#endif // tokenizer_Csq4
