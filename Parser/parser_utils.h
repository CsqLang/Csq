#if !defined(parser_Utils_Csq4)
#define parser_Utils_Csq4
#include "../Memory/StackManager.h"
#include "../Grammar/Csq.h"

//Util functions
bool CheckIF(array<str> tokens){
    return in(tokens,"if");
}
bool isIdentifier(str tok){
    return Regex(identifier,tok);
}
bool CheckElse(array<str> tokens){
    return in(tokens,"else");
}
bool CheckElif(array<str> tokens){
    return in(tokens,"elif");
}
bool CheckFor(array<str> tokens){
    return in(tokens,"for");
}
bool CheckWhile(array<str> tokens){
    return in(tokens,"while");
}
bool CheckFunctionDefination(array<str> tokens){
    return in(tokens,"def");
}
bool CheckClassDefination(array<str> tokens){
    return in(tokens,"class");
}

#endif // parser_Utils_Csq4