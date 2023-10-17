#if !defined(ERROR_CSQ4)
#define ERROR_CSQ4


#include "core.h"
//Error counts
int error_c = 0;
/*
This file contains all types of error which can be returned during the execution.
*/
void RuntimeError(string error)
{
    printf("%s\n", error.c_str());
    error_c++;
}


void TypeAssignError(string t1, string t2){
    RuntimeError("invalid assignment between the variables of type '" + t1 + "' and '" + t2 + "'");
}

#endif // ERROR_CSQ4
