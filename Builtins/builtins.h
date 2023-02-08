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
#include <stdio.h>
#include <string.h>
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
        auto op_equal( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( ref<i32> v1, ref<i32> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};

class i64{
    public:
        long int val;
        i64(long int n){
            val = n;
        }
        i64(const i64& n){
            val = n.val;
        }
        i64(){}
        auto op_add(ref<i64> v, ref<i64> v2){
            ref<i64> __val = new i64(v->val + v2->val);
            return __val;
        }
        auto op_sub(ref<i64> v, ref<i64> v2){
            ref<i64> __val = new i64(v->val - v2->val);
            return __val;
        }
        auto op_div(ref<i64> v, ref<i64> v2){
            ref<i64> __val = new i64(v->val / v2->val);
            return __val;
        }
        auto op_mul(ref<i64> v, ref<i64> v2){
            ref<i64> __val = new i64(v->val * v2->val);
            return __val;
        }
        auto op_equal( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( ref<i64> v1, ref<i64> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};

class i128{
    public:
        long long int val;
        i128(long long int n){
            val = n;
        }
        i128(const i128& n){
            val = n.val;
        }
        i128(){}
        auto op_add(ref<i128> v, ref<i128> v2){
            ref<i128> __val = new i128(v->val + v2->val);
            return __val;
        }
        auto op_sub(ref<i128> v, ref<i128> v2){
            ref<i128> __val = new i128(v->val - v2->val);
            return __val;
        }
        auto op_div(ref<i128> v, ref<i128> v2){
            ref<i128> __val = new i128(v->val / v2->val);
            return __val;
        }
        auto op_mul(ref<i128> v, ref<i128> v2){
            ref<i128> __val = new i128(v->val * v2->val);
            return __val;
        }
        auto op_equal( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( ref<i128> v1, ref<i128> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};
//FLoat types

class f32{
    public:
        double val;
        f32(double n){
            val = n;
        }
        f32(const f32& n){
            val = n.val;
        }
        f32(){}
       
        auto op_add( ref<f32> v1, ref<f32> v2){
            return ref<f32>((v1->val)+(v2->val));
        }
        auto op_sub( ref<f32> v1, ref<f32> v2){
            return ref<f32>((v1->val)-(v2->val));
        }
        auto op_mul( ref<f32> v1, ref<f32> v2){
            return ref<f32>((v1->val)*(v2->val));
        }
        auto op_div( ref<f32> v1, ref<f32> v2){
            return ref<f32>((v1->val)/(v2->val));
        }
        auto op_equal( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};

class f64{
    public:
        double val;
        f64(double n){
            val = n;
        }
        f64(const f64& n){
            val = n.val;
        }
        f64(){}
       
        auto op_add( ref<f64> v1, ref<f64> v2){
            return ref<f64>((v1->val)+(v2->val));
        }
        auto op_sub( ref<f64> v1, ref<f64> v2){
            return ref<f64>((v1->val)-(v2->val));
        }
        auto op_mul( ref<f64> v1, ref<f64> v2){
            return ref<f64>((v1->val)*(v2->val));
        }
        auto op_div( ref<f64> v1, ref<f64> v2){
            return ref<f64>((v1->val)/(v2->val));
        }
        auto op_equal( ref<f64> v1, ref<f64> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( ref<f64> v1, ref<f64> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( ref<f64> v1, ref<f64> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( ref<f64> v1, ref<f64> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( ref<f64> v1, ref<f64> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( ref<f32> v1, ref<f32> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};

//Defination for [] operator
template<typename T>
auto ref<T>::operator[](int index){
    return ref<T>(this->op_brac(ptr, new i32(index)));
}

//String class
class str{
    public:
        char* __str__;
        str(){}
        str(const char* __str){
            this->__str__ = new char[strlen(__str) + 1];
            // this->__str = __str;
            for(int i = 0;i<strlen(__str);i++){
                this->__str__[i] = __str[i];
            }
        }
        str(ref<str> str_){
            this->__str__ = new char[strlen(str_->__str__) + 1];
            __str__ = str_->__str__;
        }
        
        //Touppercase
        auto upper(){
            char* st = new char[strlen(__str__)+1];
            st = __str__;
            for(int i=0;i<strlen(__str__);i++){
                if(int(st[i]) >= 97 && int(st[i]) <=122){
                    st[i] = char(int(__str__[i])-32);
                }
                else{}
            }
            return ref<str>(st);
        }

        //Tolowercase
        auto lower(){
            char* st = new char[strlen(__str__)+1];
            st = __str__;
            for(int i=0;i<strlen(__str__);i++){
                if(int(st[i]) >= 65 && int(st[i]) <=90){
                    st[i] = char(int(__str__[i])+32);
                }
                else{}
            }
            return ref<str>(st);
        }
        //Length of the string
        auto len(){
            return ref<i32>(strlen(__str__));
        }
        // toint32
        auto toi32(){
            int i = atoi(__str__);
            return ref<i32>(i);
        }
        //tof32
        auto tof64(){
            return ref<f64>(atof(__str__));
        }

        //Operators
        auto op_add(ref<str> self, ref<str> arg){
            char* s = strcat(self->__str__,arg->__str__);
            return ref<str>(s);
        }
};

#include <initializer_list>
/*
This is the class which stores elements in the allocated memory.
*/
template<typename T>
class array{
    private:
        int current;
    public:
        T* arr;
        
        i32 len=(0);
        array(){}
        array(ref<i32> size, std::initializer_list<T> list_){
            arr = new T[size->val];
            int i = 0;
            if(size->val < list_.size()){
                MemoryOverflowException();
            }
            len = *size;
            for(auto e : list_){
                arr[i] = e;
                i++;
            }
            current = i;
        }
        auto op_brac(ref<array<T>> inst, ref<i32> index){
            return (inst->arr[index->val]);
        }
        auto add(ref<T> elem){
            if(current+1 > len.val){
                MemoryOverflowException();
            }
            else{
                arr[current] = *elem;
                current++;
            }
        }
        auto read(ref<i32> ind){
            if(ind->val+1 > this->current){
                IndexError();
            }
            return ref<T>(arr[ind->val]);
        }
        auto read(int ind){
            if(ind+1 > this->current){
                IndexError();
            }
            return ref<T>(arr[ind]);
        }
        auto sum(){
            ref<T> res = T(0);
            for(int i = 0;i<this->current;i++){
                res = res+(ref<T>(T(arr[i])));
            }
            return ref<T>(res);
        }
        auto mean(){
            double sm = double(sum()->val);
            int len = this->len.val;
            f64 mean_ = sm/len;
            return ref<f64>(new f64(mean_));
        }
        auto min(){
            ref<T> elem = T(arr[0]);
            for(int i = 0;i<this->current;i++){
                if(arr[i].val < elem->val){
                    elem = arr[i];
                }
            }
            return ref<T>(elem);
        }
        auto max(){
            ref<T> elem = T(0);
            for(int i = 0;i<this->current;i++){
                if(arr[i].val > elem->val){
                    elem = arr[i];
                }
            }
            return ref<T>(elem);
        }
        auto count(ref<T> elem){
            ref<i32> count = T(0);
            for(int i = 0;i<this->current;i++){
                if(elem == arr[i]){
                    count = count + i32(1);
                }
            }
            return ref<i32>(count);
        }
        auto pop(){current--;}
        T* begin() { return &this->arr[0];}
        const T* begin() const { return &this->arr[0];}
        T* end() { return &this->arr[this->current]; }
        const T* end() const { return &this->arr[this->current];}
};


auto tostr(ref<str> str_){
    return ref<str>(new str(str_->__str__));
}
auto tostr(ref<f32> f32_){
    str s;
    sprintf(s.__str__,"%f",f32_->val);
    return ref<str>((s));
}
auto tostr(ref<f64> f64_){
    str s;
    sprintf(s.__str__,"%lf",f64_->val);
    return ref<str>((s));
}
auto tostr(ref<i32> i32_){
    str s;
    sprintf(s.__str__,"%d",i32_->val);
    return ref<str>((s));
}

//Overloading the tostr function to print arrays
auto tostr(ref<array<str>> arr_str){
    ref<str> s = new str("{ ");
    for(auto e : *arr_str){
        s = s + e;
    }return s;
}
template<typename T>
void print(T arg1){
    printf("%s\n",tostr(*arg1)->__str__);
}
template<typename T, typename... Args>
void print(T arg1,Args... more){
    printf("%s\n",tostr(*arg1)->__str__);
    print(more...);
}
#endif
