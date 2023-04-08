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

struct f64 {
    double data;
    string __str__;
    f64() { data = 0; __str__ = to_string(data); }
    f64(double val) { data = val; __str__ = to_string(data); }
    f64(const f64& val) { data = val.data; __str__ = to_string(data); }
    f64 operator+(const f64& val) {
        return f64(data + val.data);
    }
    f64 operator-(const f64& val) {
        return f64(data + val.data);
    }
    f64 operator*(const f64& val) {
        return f64(data + val.data);
    }
    f64 operator/(const f64& val) {
        return f64(data / val.data);
    }
    bool operator==(const f64& val){
        return data == val.data;
    }
    bool operator!=(const f64& val){
        return data != val.data;
    }
    bool operator>(const f64& val){
        return data > val.data;
    }
    bool operator<(const f64& val){
        return data < val.data;
    }
    bool operator>=(const f64& val){
        return data >= val.data;
    }
    bool operator<=(const f64& val){
        return data <= val.data;
    }
};

struct str{
    string __str__;
    str(){__str__ = "";}
    str(const char* str_){__str__ = str_;}
    str(string str_){__str__ = str_;}
    str(const str& str_){__str__ = str_.__str__;}
    int len(){return __str__.size();}
    str operator+(const str& val) {
        return str(__str__ + val.__str__);
    }
};

template<typename T> 
struct list{
    private:
        vector<T> data;
    public:
        list(){}
        list(vector<T> data_){data = data_;}
        list(const list& ls){data = ls.data;}
        void add(T val){
            data.push_back(val);
        }
        T read(int index){
            return data[index];
        }
        T operator[](int index){
            return data[index];
        }
        int len(){
            return data.size();
        }
};

void print(int val){
    printf("%d\n",val);
}
void print(float val){
    printf("%f\n",val);
}
void print(double val){
    printf("%lf\n",val);
}
void print(i32 val){
    print(val.data);
}
void print(f64 val){
    print(val.data);
}
void print(str val){
    printf("%s\n",val.__str__.c_str());
}

void print(list<i32> val){
    printf("{ ");
    for(int i = 0;i<val.len();i++){
        printf("%d, ",val[i].data);
    }
    printf(" }\n");
}
void print(list<i64> val){
    printf("{ ");
    for(int i = 0;i<val.len();i++){
        printf("%lld, ",val[i].data);
    }
    printf(" }\n");
}
void print(list<f64> val){
    printf("{ ");
    for(int i = 0;i<val.len();i++){
        printf("%lf, ",val[i].data);
    }
    printf(" }\n");
}
#endif // BUILTINS_CSQ4_2
