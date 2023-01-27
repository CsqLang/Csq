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

class i32{
    public:
        int32_t val;
        i32(int n){
            val = n;
        }
        i32(const i32& n){
            val = n.val;
        }
        i32(){}
       
        auto op_add( SmartPointer<i32> v1, SmartPointer<i32> v2){
            return SmartPointer<i32>((v1->val)+(v2->val));
        }
        auto op_sub( SmartPointer<i32> v1, SmartPointer<i32> v2){
            return SmartPointer<i32>((v1->val)-(v2->val));
        }
        auto op_mul( SmartPointer<i32> v1, SmartPointer<i32> v2){
            return SmartPointer<i32>((v1->val)*(v2->val));
        }
        auto op_div( SmartPointer<i32> v1, SmartPointer<i32> v2){
            return SmartPointer<i32>((v1->val)/(v2->val));
        }
        auto op_mod( SmartPointer<i32> v1, SmartPointer<i32> v2){
            return SmartPointer<i32>((v1->val)%(v2->val));
        }
        auto op_equal( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( SmartPointer<i32> v1, SmartPointer<i32> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};

class i64{
    public:
        int64_t val;
        i64(long int n){
            val = n;
        }
        i64(const i64& n){
            val = n.val;
        }
        i64(){}
       
        auto op_add( SmartPointer<i64> v1, SmartPointer<i64> v2){
            return SmartPointer<i64>((v1->val)+(v2->val));
        }
        auto op_sub( SmartPointer<i64> v1, SmartPointer<i64> v2){
            return SmartPointer<i64>((v1->val)-(v2->val));
        }
        auto op_mul( SmartPointer<i64> v1, SmartPointer<i64> v2){
            return SmartPointer<i64>((v1->val)*(v2->val));
        }
        auto op_div( SmartPointer<i64> v1, SmartPointer<i64> v2){
            return SmartPointer<i64>((v1->val)/(v2->val));
        }
        auto op_mod( SmartPointer<i64> v1, SmartPointer<i64> v2){
            return SmartPointer<i64>((v1->val)%(v2->val));
        }
        auto op_equal( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( SmartPointer<i64> v1, SmartPointer<i64> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};



#endif // BUILTINS_CSQ4
