/*
C/C++ codes to express objects
*/
#if !defined(OBJRUNTIME_CSQ4)
#define OBJRUNTIME_CSQ4
#include "../AST/ast.h"

//Struct for runtime variables
struct Variable
{
    string name;
    string type;
    // string value; instead of directly storing the value it should store address of the value.
    int value_address;
    Variable(){}
    Variable(string name_, string type_, int value_)
    {
        name = name_;
        type = type_;
        value_address = value_;
    }
};




#endif // OBJRUNTIME_CSQ4