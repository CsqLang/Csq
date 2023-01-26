/*
This file includes some examples of bytecode representation in C code
*/

#include "Instructions.h"

//Defining variables | references
REFERENCE(var,i32,4759);
REFERENCE(var2,i32,var);
//Defining functions
def df(REFERENCE(param,i32,)) LBRACE
  return param;
ENDS

//Calling functions
df(i32(54));
df(var);
//loops
FOR FORREF(i,i32) IN {} LBRACE
ENDS
