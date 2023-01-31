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
#include "exceptions.h"
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
       
        auto op_add( SmartPointer<f32> v1, SmartPointer<f32> v2){
            return SmartPointer<f32>((v1->val)+(v2->val));
        }
        auto op_sub( SmartPointer<f32> v1, SmartPointer<f32> v2){
            return SmartPointer<f32>((v1->val)-(v2->val));
        }
        auto op_mul( SmartPointer<f32> v1, SmartPointer<f32> v2){
            return SmartPointer<f32>((v1->val)*(v2->val));
        }
        auto op_div( SmartPointer<f32> v1, SmartPointer<f32> v2){
            return SmartPointer<f32>((v1->val)/(v2->val));
        }
        auto op_equal( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( SmartPointer<f32> v1, SmartPointer<f32> v2){
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
       
        auto op_add( SmartPointer<f64> v1, SmartPointer<f64> v2){
            return SmartPointer<f64>((v1->val)+(v2->val));
        }
        auto op_sub( SmartPointer<f64> v1, SmartPointer<f64> v2){
            return SmartPointer<f64>((v1->val)-(v2->val));
        }
        auto op_mul( SmartPointer<f64> v1, SmartPointer<f64> v2){
            return SmartPointer<f64>((v1->val)*(v2->val));
        }
        auto op_div( SmartPointer<f64> v1, SmartPointer<f64> v2){
            return SmartPointer<f64>((v1->val)/(v2->val));
        }
        auto op_equal( SmartPointer<f64> v1, SmartPointer<f64> v2){
            bool state = false;
            if(v1->val == v2->val)
                state = true;
            return state;
        }
        auto op_notEqual( SmartPointer<f64> v1, SmartPointer<f64> v2){
            bool state = false;
            if(v1->val != v2->val)
                state = true;
            return state;
        }
        auto op_lesser( SmartPointer<f64> v1, SmartPointer<f64> v2){
            bool state = false;
            if(v1->val < v2->val)
                state = true;
            return state;
        }
        auto op_greater( SmartPointer<f64> v1, SmartPointer<f64> v2){
            bool state = false;
            if(v1->val > v2->val)
                state = true;
            return state;
        }
        auto op_greaterEqual( SmartPointer<f64> v1, SmartPointer<f64> v2){
            bool state = false;
            if(v1->val >= v2->val)
                state = true;
            return state;
        }
        auto op_lesserEqual( SmartPointer<f32> v1, SmartPointer<f32> v2){
            bool state = false;
            if(v1->val <= v2->val)
                state = true;
            return state;
        }
};


void assert(bool cond, int id_){
    if(cond == 1){
        printf("%d Passed\n",id_);
    }else{
        AssertionFailureException(id_);
    }
}

//Some Definitions
template<typename T>
auto SmartPointer<T>::operator[](int index){
    return this->op_brac(ptr, i32(index));
}

//Getting initializer list
#include <initializer_list>
template<typename T>
class StaticSequence{
    private:
        int current = 0;
    public:
        T* seq;
        int len = 0;
        
        StaticSequence(){}
        StaticSequence(SmartPointer<i32> size){
            seq = new T[size->val];
            len = size->val;
        }
        void push(SmartPointer<T> e){
            if(current+1 > len){
                MemoryOverflowException();
            }
            else{
                seq[current] = *e;
                current++;
            }
        }
        SmartPointer<T> read(SmartPointer<i32> index){
            if(index->val > len-1){
                MemoryOverflowException();
            }
            return seq[index->val];
        }
};

/*
This class is made to allocate memory dynamically and to create series of items.
*/
template<typename T>
class DynamicSequence{
    public:
        T* arr;
        // capacity is the total storage
        int capacity;
        // current is the number of elements
        int current;
        (DynamicSequence)(){
            arr = new T[1];
            capacity = 1;
            current = 0;
        }
        auto update(SmartPointer<i32> index, SmartPointer<T> value){
            arr[index->val] = *value;
        }
        auto push(SmartPointer<T> data){
            // if the number of elements is equal to the
            // capacity, that means we don't have space to
            // accommodate more elements. We need to double the
            // capacity
            if (current == capacity) {
                T* temp = new T[2 * capacity];
    
                // copying old array elements to new array
                for (int i = 0; i < capacity; i++){
                    temp[i] = arr[i];
                }
    
                // deleting previous array
                delete[] arr;
                capacity *= 2;
                arr = temp;
            }
            // Inserting data
            arr[current] = *data;
            current++;
        }
        auto op_brac(SmartPointer<DynamicSequence<T>> s, SmartPointer<i32> index){
            return s->arr[index->val];
        }
        auto erase(SmartPointer<T> e){
            int i;
            for (i=0; i<this->current; i++)
                if (this->arr[i] == *e)
                    break;
            // If element found in array
            if (i < this->current)
            {
                // reduce size of array and move all
                // elements on space ahead
                this->current = this->current - 1;
                for (int j=i; j<this->current; j++)
                    arr[j] = arr[j+1];
            }
        }
        auto pop(){current--;}
        T* begin() { return &this->arr[0];}
        const T* begin() const { return &this->arr[0];}
        T* end() { return &this->arr[this->current]; }
        const T* end() const { return &this->arr[this->current];}
};

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
        array(SmartPointer<i32> size, std::initializer_list<T> list_){
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
        auto op_brac(SmartPointer<array<T>> inst, SmartPointer<i32> index){
            return SmartPointer<T>(inst->arr[index->val]);
        }
        auto add(SmartPointer<T> elem){
            if(current+1 > len.val){
                MemoryOverflowException();
            }
            else{
                arr[current] = *elem;
                current++;
            }
        }
        auto sum(){
            SmartPointer<T> res = T(0);
            for(int i = 0;i<this->current;i++){
                res = res+(SmartPointer<T>(T(arr[i])));
            }
            return SmartPointer<T>(res);
        }
        auto mean(){
            //Converting sum to f64
            f64 sm = f64(double(sum()->val));
            return SmartPointer<f64>((SmartPointer<f64>(sm)/f64(double(len.val))));
        }
        auto min(){
            SmartPointer<T> elem = T(arr[0]);
            for(int i = 0;i<this->current;i++){
                if(arr[i].val < elem->val){
                    elem = arr[i];
                }
            }
            return SmartPointer<T>(elem);
        }
        auto max(){
            SmartPointer<T> elem = T(0);
            for(int i = 0;i<this->current;i++){
                if(arr[i].val > elem->val){
                    elem = arr[i];
                }
            }
            return SmartPointer<T>(elem);
        }
        auto count(SmartPointer<T> elem){
            SmartPointer<i32> count = T(0);
            for(int i = 0;i<this->current;i++){
                if(elem == arr[i]){
                    count = count + i32(1);
                }
            }
            return SmartPointer<i32>(count);
        }
        auto pop(){current--;}
        T* begin() { return &this->arr[0];}
        const T* begin() const { return &this->arr[0];}
        T* end() { return &this->arr[this->current]; }
        const T* end() const { return &this->arr[this->current];}
};

/*
This class is the implementation of strings. To increase security
the string stored are immutable
*/
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
        str(SmartPointer<str> str_){
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
            return SmartPointer<str>(st);
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
            return SmartPointer<str>(st);
        }

        //To Title case
        auto title(){
            char* st = new char[strlen(__str__)+1];
            st = __str__;
            for(int i=0;i<strlen(__str__);i++){
                if(int(st[i]) >= 65 && int(st[i]) <=90){
                    st[i] = char(int(__str__[i])+32);
                }
                else{}
            }
            return SmartPointer<str>(st);
        }
};

#endif // BUILTINS_CSQ4
