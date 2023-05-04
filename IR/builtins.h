#if !defined(BUILTINS_CSQ4_2)
#define BUILTINS_CSQ4_2
// #include "vm.h"
#include "instructions.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

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
    bool operator==(const str& val) {
        return __str__ == val.__str__;
    }
    bool operator!=(const str& val) {
        return __str__ != val.__str__;
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
        // Sort a vector in ascending order using std::sort
        void sort() {
            std::sort(data.begin(), data.end());
        }
        //Iterators for for each loop.
        T* begin() { return &this->data[0];}
        const T* begin() const { return &this->data[0];}
        T* end() { return &this->data[this->data.size()]; }
        const T* end() const { return &this->data[this->data.size()];}
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
void print(list<int> val){
    printf("{ ");
    for(int i = 0;i<val.len();i++){
        printf("%d, ",val[i]);
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
void print(initializer_list<int> ls){
    printf("{ ");
    for(int i : ls)
        printf("%d, ",i);
    printf(" }\n");
}

list<i32> range(i32 end_){
    list<i32> d;
    for(i32 i = 0;i< end_.data;i.data++){
        d.add(i);
    }
    return d;
}   

#include <numeric>

std::vector<int> range(int start, int end_) {
    std::vector<int> result(end_ - start);
    for(int i = start; i < end_; i++) {
        result[i - start] = i;
    }
    return result;
}


template <typename KeyType, typename ValueType>
class dict {
private:
    // Define a struct to hold key-value pairs
    struct Pair {
        KeyType key;
        ValueType value;

        // Define a comparison operator for pairs
        bool operator==(const Pair& other) const {
            return key == other.key && value == other.value;
        }
    };

    std::vector<Pair> pairs;

public:
    // Add a key-value pair to the map
    void insert(const KeyType& key, const ValueType& value) {
        // Check if the key already exists in the map
        for (auto& pair : pairs) {
            if (pair.key == key) {
                // If it does, update the value for that key
                pair.value = value;
                return;
            }
        }

        // If the key doesn't exist, add a new pair to the vector
        pairs.push_back({key, value});
    }

    // Retrieve the value for a given key
    ValueType& operator[](const KeyType& key) {
        // Search for the key in the vector
        for (auto& pair : pairs) {
            if (pair.key == key) {
                // If found, return the associated value
                return pair.value;
            }
        }

        // If not found, add a new pair to the vector with a default value
        pairs.push_back({key, ValueType()});
        return pairs.back().value;
    }

    // Define an equality operator for maps
    bool operator==(const dict& other) const {
        return pairs == other.pairs;
    }

    // Define a less-than operator for maps
    bool operator<(const dict& other) const {
        return pairs < other.pairs;
    }
};

void echo(str s){
    printf("%s", s.__str__.c_str());
}
void echo(int v){
    printf("%d", v);
}
void echo(i32 v){
    printf("%d", v.data);
}
void echo(i64 v){
    printf("%lld", v.data);
}
void echo(f64 s){
    printf("%lf", s.data);
}

#define type(p) typeid(p).name()


#endif // BUILTINS_CSQ4_2
