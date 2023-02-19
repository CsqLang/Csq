//This file represents the implementation of during Csq4's runtime.
#if !defined(PROGRAM_RUNTIME_STACK_CSQ4)
#define PROGRAM_RUNTIME_STACK_CSQ4
#include "../libs/utils/stringlib.h"
#include "../libs/utils/dict.h"
namespace Stack{
    //This represents the code of functions from different scopes.
    dict<str,str> Function;
    //This represents the imports in the code.
    array<str> Import;
    //This stack represents the names of variables.
    array<str> Variables;
    //This stack represents the garbage values collected
    array<str> GarbageValues;
}
namespace Scope{
    //This dict represents the function's scope
    dict<str,array<str>> Function;
    //This dict represents the variable's scope
    dict<str,array<str>> Variable;
}

#endif // PROGRAM_RUNTIME_STACK_CSQ4
