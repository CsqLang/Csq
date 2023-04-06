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
};

#endif // BUILTINS_CSQ4_2
