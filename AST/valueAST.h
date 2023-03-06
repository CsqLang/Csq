#if !defined(Value_Struct_Csq4)
#define Value_Struct_Csq4

#include "../Tokenizer/tokenizer.h"
#include "../Parser/exception.h"

struct Value {
    string value;
    TokenType type;
};

void BadValueError(int line){
    printf("Error: Bad value error at line %d, wrong value is passed.", line);
    error_count++;
}

Value addValue(Token value,int line){
    Value val;
    if(value.type == VALUE || value.type == STR || value.type == IDENTIFIER){
        val.value = value.token;
        val.type = value.type;
    }
    else
        BadValueError(line);
    return val;
}


#endif // Value_Struct_Csq4
