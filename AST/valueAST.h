#if !defined(Value_Struct_Csq4)
#define Value_Struct_Csq4

#include "../Tokenizer/tokenizer.h"
#include "../Parser/exception.h"
#include "ast.h"

//Value for AST
struct Value : AST{
    Token token;
    AST_TYPE type = AST_TYPE::VALUE_TYPE;
};

void BadValueError(int line){
    printf("Error: Bad value error at line %d, wrong value is passed.", line);
    error_count++;
}

Value addValue(Token value,int line){
    Value val;
    if(value.type == VALUE || value.type == STR || value.type == IDENTIFIER){
        val.token = value;
    }
    else
        BadValueError(line);
    return val;
}


#endif // Value_Struct_Csq4
