#if !defined(TYPE_H_PARSER_CSQ4)
#define TYPE_H_PARSER_CSQ4
#include "../Grammar/Csq.h"
#include "../Memory/Stack.h"
bool isFunctionCall(str name){
    return in(Stack::Function.keys,name);
}

#endif // TYPE_H_PARSER_CSQ4
