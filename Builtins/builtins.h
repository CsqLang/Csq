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
class i16{
    public:
        int16_t val;
        i16(){}
        i16(SmartPointer<int16_t> v){this->val=(*v);}
        i16(SmartPointer<i16> v){this->val =(v->val);}
        i16(const i16& v){this->val =(v.val);}
        i16(const int16_t& v){this->val =v;}
        auto operator+(SmartPointer<i16> v){
            return SmartPointer<i16>(v->val + this->val);
        }
        auto operator-(SmartPointer<i16> v){
            return SmartPointer<i16>(v->val - this->val);
        }
        auto operator*(SmartPointer<i16> v){
            return SmartPointer<i16>(v->val * this->val);
        }
        auto operator/(SmartPointer<i16> v){
            return SmartPointer<i16>(v->val / this->val);
        }
        auto operator=(SmartPointer<i16> v){
            this->val = v->val;
        }
};
class i8{
    public:
        int8_t val;
        i8(){}
        i8(SmartPointer<int8_t> v){this->val=(*v);}
        i8(SmartPointer<i8> v){this->val =(v->val);}
        i8(const i8& v){this->val =(v.val);}
        i8(const int8_t& v){this->val =v;}
        auto operator+(SmartPointer<i8> v){
            return SmartPointer<i8>(v->val + this->val);
        }
        auto operator-(SmartPointer<i8> v){
            return SmartPointer<i8>(v->val - this->val);
        }
        auto operator*(SmartPointer<i8> v){
            return SmartPointer<i8>(v->val * this->val);
        }
        auto operator/(SmartPointer<i8> v){
            return SmartPointer<i8>(v->val / this->val);
        }
        auto operator=(SmartPointer<i8> v){
            this->val = v->val;
        }
};

#endif // builtins_csq4
