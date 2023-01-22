#if !defined(builtins_csq4)
#define builtins_csq4
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Datatypes:
class i32{
    public:
        int32_t val;
        i32(){}
        i32(SmartPointer<int32_t> v){this->val=(*v);}
        i32(SmartPointer<i32> v){this->val =(v->val);}
        i32(const i32& v){this->val =(v.val);}
        i32(const int32_t& v){this->val =v;}
        auto operator+(SmartPointer<i32> v){
            return SmartPointer<i32>(v->val + this->val);
        }
        auto operator-(SmartPointer<i32> v){
            return SmartPointer<i32>(v->val - this->val);
        }
        auto operator*(SmartPointer<i32> v){
            return SmartPointer<i32>(v->val * this->val);
        }
        auto operator/(SmartPointer<i32> v){
            return SmartPointer<i32>(v->val / this->val);
        }
        auto operator=(SmartPointer<i32> v){
            this->val = v->val;
        }
};
class i64{
    public:
        int64_t val;
        i64(){}
        i64(SmartPointer<int64_t> v){this->val=(*v);}
        i64(SmartPointer<i64> v){this->val =(v->val);}
        i64(const i64& v){this->val =(v.val);}
        i64(const int64_t& v){this->val =v;}
        auto operator+(SmartPointer<i64> v){
            return SmartPointer<i64>(v->val + this->val);
        }
        auto operator-(SmartPointer<i64> v){
            return SmartPointer<i64>(v->val - this->val);
        }
        auto operator*(SmartPointer<i64> v){
            return SmartPointer<i64>(v->val * this->val);
        }
        auto operator/(SmartPointer<i64> v){
            return SmartPointer<i64>(v->val / this->val);
        }
        auto operator=(SmartPointer<i64> v){
            this->val = v->val;
        }
};

#endif // builtins_csq4
