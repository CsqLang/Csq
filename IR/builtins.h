#if !defined(BUILTINS_CSQ4_2)
#define BUILTINS_CSQ4_2
#include "vm.h"

struct i32{
    int data;
    string __str__;
    i32(){data = 0;__str__ = to_string(data);}
    i32(int val){data = val;__str__ = to_string(data);}
    i32(const i32& val){data = val.data;__str__ = to_string(data);}
    i32 operator+(const i32& val){
        return i32(data + val.data);
    }
    i32 operator-(const i32& val){
        return i32(data - val.data);
    }
    i32 operator/(const i32& val){
        return i32(data / val.data);
    }
    i32 operator*(const i32& val){
        return i32(data * val.data);
    }
    bool operator==(const i32& val){
        return data == val.data;
    }
    bool operator!=(const i32& val){
        return data != val.data;
    }
    bool operator>(const i32& val){
        return data > val.data;
    }
    bool operator<(const i32& val){
        return data < val.data;
    }
    bool operator>=(const i32& val){
        return data >= val.data;
    }
    bool operator<=(const i32& val){
        return data <= val.data;
    }
};

struct i64 {
    long long data;
    string __str__;
    i64() { data = 0; __str__ = to_string(data); }
    i64(long long val) { data = val; __str__ = to_string(data); }
    i64(const i64& val) { data = val.data; __str__ = to_string(data); }
    i64 operator+(const i64& val) {
        return i64(data + val.data);
    }
    i64 operator-(const i64& val) {
        return i64(data + val.data);
    }
    i64 operator*(const i64& val) {
        return i64(data + val.data);
    }
    i64 operator/(const i64& val) {
        return i64(data / val.data);
    }
    bool operator==(const i64& val){
        return data == val.data;
    }
    bool operator!=(const i64& val){
        return data != val.data;
    }
    bool operator>(const i64& val){
        return data > val.data;
    }
    bool operator<(const i64& val){
        return data < val.data;
    }
    bool operator>=(const i64& val){
        return data >= val.data;
    }
    bool operator<=(const i64& val){
        return data <= val.data;
    }
};



#endif // BUILTINS_CSQ4_2
