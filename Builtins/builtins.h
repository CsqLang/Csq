#if !defined(BUILTINS_CSQ4)
#define BUILTINS_CSQ4

/*
    BUILTIN support for CSQ4 provided by the utilities built through C/C++
    ::::::::::::::::::::::::::::CORE UTILITIES::::::::::::::::::::::::::::
    (1) DATATYPES
    (2) INPUT OUTPUT FUNCTIONS
    (3) AND MANY MORE UTILITIES

    Source : @anchor https://www.github.com/CsqLang/Csq4
*/
/*******************************Importing C libraries & Reference counter *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Memory/Reference_Counter.h"



//Basic Datatypes such as int, float, bytes etc..

//Providing int data types

// This class will proivide int8 data type.
class i8{
    public:
        //public member to store data.
        int8_t val;
        i8(){}
        i8(int8_t val){this->val = val;}
        i8(const i8& val){this->val = val.val;}
        //Operators

};

//This class will proivide int32 data type.
class i32{
    public:
        //public member to store data.
        int val;
        i32(){}
        i32(int val){this->val = val;}
        i32(const i32& val){this->val = val.val;}
        //Operators
        SmartPointer<i32> op_add(SmartPointer<i32> v){
            return SmartPointer<i32>(v->val + val);
        }
};

//This function can be used to test a condition
void assert(bool cond, i32 ident){
    if(cond == 1){
        printf("Test passed by %d\n",ident.val);
    }
    else{
        printf("Assertion Error: While testing %d\n",ident.val);
    }
}
#endif // BUILTINS_CSQ4
