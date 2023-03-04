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


#endif // tokenizer_Csq4
