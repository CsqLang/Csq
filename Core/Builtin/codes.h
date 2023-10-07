/*

This file contains IR codes for different CsqAPI's Runtime functions

Why do we need it?
When C++ code is produced it's often big and quite difficult
to understand to remove this complexity here we will be providing
short names which looks elegant.

*/
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include <iostream>

/****************************************/

#define main int main(int argc, char** argv){
#define endmain return 0;}
#define class_memvVar(cname,obj, name) dynamic_pointer_cast<cname>(id(obj).cus_type)->getMember(name);
#define methodId(obj, methodname) __classes__[id(obj).__class__].methods[methodname]
string object(Cell class_){
    return class_.sval;
}
