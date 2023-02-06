// /*
//     BUILTIN support for CSQ4 provided by the utilities built through C/C++
//     ::::::::::::::::::::::::::::CORE UTILITIES::::::::::::::::::::::::::::
//     (1) DATATYPES
//     (2) INPUT OUTPUT FUNCTIONS
//     (3) AND MANY MORE UTILITIES

//     Source : @anchor https://www.github.com/CsqLang/Csq4
// */
#if !defined(builtins_h)
#define builtins_h
// /*******************************Importing C libraries & Reference counter *********************************/
#include "exceptions.h"
#include "../Memory/Reference_Counter.h"
//Basic Datatypes such as int, float, bytes etc..

//Providing int data types

class i32{
    public:
        int val;
        i32(int n){
            val = n;
        }
        i32(const i32& n){
            val = n.val;
        }
        i32(){}
        auto op_add(ref<i32> v, ref<i32> v2){
            ref<i32> __val = new i32(v->val + v2->val);
            return __val;
        }
        auto op_sub(ref<i32> v, ref<i32> v2){
            ref<i32> __val = new i32(v->val - v2->val);
            return __val;
        }
        auto op_div(ref<i32> v, ref<i32> v2){
            ref<i32> __val = new i32(v->val / v2->val);
            return __val;
        }
        auto op_mul(ref<i32> v, ref<i32> v2){
            ref<i32> __val = new i32(v->val * v2->val);
            return __val;
        }
};

#endif
