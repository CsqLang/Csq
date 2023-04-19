#if !defined(TypeChecker_H)
#define TypeChecker_H

#include "../AST/ast.h"
#include "../AST/visitor.h"
#include "parser.h"
#include "../Memory/stack.h"


/*
a:i32 = 384
b:f64 = a //Error
*/

vector<string> CollectTypes(string type){
    vector<string> types;
    
}

void TypeChecker(string op1, string op2, string op1type, string op2type)
{
    //Now it's also possible that a class is allowing different types to be stored so we have to factor them.
    vector<string> op1_type_list,op2_type_list;

}

#endif // TypeChecker_H
