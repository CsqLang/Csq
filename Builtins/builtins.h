#if !defined(builtins_csq4)
#define builtins_csq4
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Memory/Reference_Counter.h"
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
class i128{
    public:
        __int128_t val;
        i128(){}
        i128(SmartPointer<__int128_t> v){this->val=(*v);}
        i128(SmartPointer<i128> v){this->val =(v->val);}
        i128(const i128& v){this->val =(v.val);}
        i128(const __int128_t& v){this->val =v;}
        auto operator+(SmartPointer<i128> v){
            return SmartPointer<i128>(v->val + this->val);
        }
        auto operator-(SmartPointer<i128> v){
            return SmartPointer<i128>(v->val - this->val);
        }
        auto operator*(SmartPointer<i128> v){
            return SmartPointer<i128>(v->val * this->val);
        }
        auto operator/(SmartPointer<i128> v){
            return SmartPointer<i128>(v->val / this->val);
        }
        auto operator=(SmartPointer<i128> v){
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

class ui32{
    public:
        u_int32_t val;
        ui32(){}
        ui32(SmartPointer<u_int32_t> v){this->val=(*v);}
        ui32(SmartPointer<ui32> v){this->val =(v->val);}
        ui32(const ui32& v){this->val =(v.val);}
        ui32(const u_int32_t& v){this->val =v;}
        auto operator+(SmartPointer<ui32> v){
            return SmartPointer<ui32>(v->val + this->val);
        }
        auto operator-(SmartPointer<ui32> v){
            return SmartPointer<ui32>(v->val - this->val);
        }
        auto operator*(SmartPointer<ui32> v){
            return SmartPointer<ui32>(v->val * this->val);
        }
        auto operator/(SmartPointer<ui32> v){
            return SmartPointer<ui32>(v->val / this->val);
        }
        auto operator=(SmartPointer<ui32> v){
            this->val = v->val;
        }
};

class ui64{
    public:
        u_int64_t val;
        ui64(){}
        ui64(SmartPointer<u_int64_t> v){this->val=(*v);}
        ui64(SmartPointer<ui64> v){this->val =(v->val);}
        ui64(const ui64& v){this->val =(v.val);}
        ui64(const u_int64_t& v){this->val =v;}
        auto operator+(SmartPointer<ui64> v){
            return SmartPointer<ui64>(v->val + this->val);
        }
        auto operator-(SmartPointer<ui64> v){
            return SmartPointer<ui64>(v->val - this->val);
        }
        auto operator*(SmartPointer<ui64> v){
            return SmartPointer<ui64>(v->val * this->val);
        }
        auto operator/(SmartPointer<ui64> v){
            return SmartPointer<ui64>(v->val / this->val);
        }
        auto operator=(SmartPointer<ui64> v){
            this->val = v->val;
        }
};
class ui16{
    public:
        u_int16_t val;
        ui16(){}
        ui16(SmartPointer<u_int16_t> v){this->val=(*v);}
        ui16(SmartPointer<ui16> v){this->val =(v->val);}
        ui16(const ui16& v){this->val =(v.val);}
        ui16(const u_int16_t& v){this->val =v;}
        auto operator+(SmartPointer<ui16> v){
            return SmartPointer<ui16>(v->val + this->val);
        }
        auto operator-(SmartPointer<ui16> v){
            return SmartPointer<ui16>(v->val - this->val);
        }
        auto operator*(SmartPointer<ui16> v){
            return SmartPointer<ui16>(v->val * this->val);
        }
        auto operator/(SmartPointer<ui16> v){
            return SmartPointer<ui16>(v->val / this->val);
        }
        auto operator=(SmartPointer<ui16> v){
            this->val = v->val;
        }
};
class ui8{
    public:
        u_int8_t val;
        ui8(){}
        ui8(SmartPointer<u_int8_t> v){this->val=(*v);}
        ui8(SmartPointer<ui8> v){this->val =(v->val);}
        ui8(const ui8& v){this->val =(v.val);}
        ui8(const u_int8_t& v){this->val =v;}
        auto operator+(SmartPointer<ui8> v){
            return SmartPointer<ui8>(v->val + this->val);
        }
        auto operator-(SmartPointer<ui8> v){
            return SmartPointer<ui8>(v->val - this->val);
        }
        auto operator*(SmartPointer<ui8> v){
            return SmartPointer<ui8>(v->val * this->val);
        }
        auto operator/(SmartPointer<ui8> v){
            return SmartPointer<ui8>(v->val / this->val);
        }
        auto operator=(SmartPointer<ui8> v){
            this->val = v->val;
        }
};
class f32{
    public:
        _Float32 val;
        f32(){}
        f32(SmartPointer<_Float32> v){this->val=(*v);}
        f32(SmartPointer<f32> v){this->val =(v->val);}
        f32(const f32& v){this->val =(v.val);}
        f32(const _Float32& v){this->val =v;}
        auto operator+(SmartPointer<f32> v){
            return SmartPointer<f32>(v->val + this->val);
        }
        auto operator-(SmartPointer<f32> v){
            return SmartPointer<f32>(v->val - this->val);
        }
        auto operator*(SmartPointer<f32> v){
            return SmartPointer<f32>(v->val * this->val);
        }
        auto operator/(SmartPointer<f32> v){
            return SmartPointer<f32>(v->val / this->val);
        }
        auto operator=(SmartPointer<f32> v){
            this->val = v->val;
        }
};
class f64{
    public:
        double val;
        f64(){}
        f64(SmartPointer<_Float64> v){this->val=(*v);}
        f64(SmartPointer<f64> v){this->val =(v->val);}
        f64(const f64& v){this->val =(v.val);}
        f64(const double& v){this->val =v;}
        auto operator+(SmartPointer<f64> v){
            return SmartPointer<f64>(v->val + this->val);
        }
        auto operator-(SmartPointer<f64> v){
            return SmartPointer<f64>(v->val - this->val);
        }
        auto operator*(SmartPointer<f64> v){
            return SmartPointer<f64>(v->val * this->val);
        }
        auto operator/(SmartPointer<f64> v){
            return SmartPointer<f64>(v->val / this->val);
        }
        auto operator=(SmartPointer<f64> v){
            this->val = v->val;
        }
};


/////////////////////////////////////////////////////////////////////////////////////
// Class str
class Bytes
{
    // Prototype for '+'
    // operator overloading
    friend Bytes operator+(
        const Bytes &lhs,
        const Bytes &rhs);

public:
    char *Str;
    // No arguments constructor
    Bytes();
    // pop_back() function
    void pop_bk();

    // push_back() function
    void push_bk(char a);

    // To get the length
    int len();
    // This is used to store the result of concatination.
    auto operator+=(const Bytes &rhs);
    // This is used to get the element at the given index.
    auto operator[](int index) { return Str[index]; }
    // This will return 1 if given str is equal to this->Str.
    // This will return 1 if given str is equal to this->Str.
    auto operator==(const Bytes &s)
    {
        bool state = 1;
        for (int i = 0; i < strlen(Str); i++)
        {
            if (this->Str[i] != s.Str[i])
            {
                state = 0;
                break;
            }
        }
        if(strlen(s.Str) != this->len()){
            state = 0;
        }
        return state;
    }
    // This will return 1 if given str is equal to this->Str.
    auto operator!=(const Bytes &s)
    {
        bool state = 0;
        for (int i = 0; i < strlen(Str); i++)
        {
            if (this->Str[i] != s.Str[i])
            {
                state = 1;
                break;
            }
        }
        return state;
    }
    auto operator!()
    {
        return Bytes(Str);
    }
    auto operator*(int s);
    // Function to copy the String
    // of length len from position pos
    void copy(char s[], int len, int pos);
    // Swap Strings function
    void swp(Bytes &rhs);

    // ConStructor with 1 arguments
    Bytes(char *val);
    Bytes(const char *val);

    // Copy ConStructor
    Bytes(const Bytes &source);

    // Move ConStructor
    Bytes(Bytes &&source);

    // Overloading the assignment
    // operator
    Bytes &operator=(
        const Bytes &rhs);
    // This method converts the str into double.
    auto todouble()
    {
        char *ptr;
        double ret;
        ret = strtod(Str, &ptr);
        return ret;
    }
    auto replace(char sub[], char new_str[])
    {
        char *Str = this->Str;
        int stringLen, subLen, newLen;
        int i = 0, j, k;
        int flag = 0, start, end;
        stringLen = strlen(Str);
        subLen = strlen(sub);
        newLen = strlen(new_str);

        for (i = 0; i < stringLen; i++)
        {
            flag = 0;
            start = i;
            for (j = 0; Str[i] == sub[j]; j++, i++)
                if (j == subLen - 1)
                    flag = 1;
            end = i;
            if (flag == 0)
                i -= j;
            else
            {
                for (j = start; j < end; j++)
                {
                    for (k = start; k < stringLen; k++)
                        Str[k] = Str[k + 1];
                    stringLen--;
                    i--;
                }

                for (j = start; j < start + newLen; j++)
                {
                    for (k = stringLen; k >= j; k--)
                        Str[k + 1] = Str[k];
                    Str[j] = new_str[j - start];
                    stringLen++;
                    i++;
                }
            }
        }
        return Str;
    }
    // DeStructor
    ~Bytes() { delete Str; }
};

// Overloading the assignment operator
Bytes &Bytes::operator=(
    const Bytes &rhs)
{
    if (this == &rhs)
        return *this;
    delete[] Str;
    Str = new char[strlen(rhs.Str) + 1];
    strcpy(Str, rhs.Str);
    return *this;
}

// Overloading the plus operator
Bytes operator+(const Bytes &lhs,
              const Bytes &rhs)
{
    int length = strlen(lhs.Str) + strlen(rhs.Str);

    char *buff = new char[length + 1];

    // Copy the Strings to buff[]
    strcpy(buff, lhs.Str);
    strcat(buff, rhs.Str);
    buff[length] = '\0';

    // String temp
    Bytes temp{buff};

    // delete the buff[]
    delete[] buff;

    // Return the concatenated String
    return temp;
}
auto Bytes::operator+=(const Bytes &rhs)
{
    int length = strlen(this->Str) + strlen(rhs.Str);

    char *buff = new char[length + 1];

    // Copy the Strings to buff[]
    strcpy(buff, this->Str);
    strcat(buff, rhs.Str);
    buff[length] = '\0';

    // String temp
    // str temp{ buff };
    delete Str;
    Str = new char[length + 1];
    strcpy(Str, buff);
}
auto Bytes::operator*(int s)
{
    Bytes n;
    for (int i = 0; i < s; i++)
    {
        n += Bytes(this->Str);
    }
    return n;
}
// Function to copy the String
void Bytes::copy(char s[], int len,
               int pos)
{
    for (int i = 0; i < len; i++)
    {
        s[i] = Str[pos + i];
    }
    s[len] = '\0';
}

// Function to implement push_bk
void Bytes::push_bk(char a)
{
    // Find length of String
    int length = strlen(Str);

    char *buff = new char[length + 2];

    // Copy character from Str
    // to buff[]
    for (int i = 0; i < length; i++)
    {
        buff[i] = Str[i];
    }
    buff[length] = a;
    buff[length + 1] = '\0';

    // Assign the new String with
    // char a to String Str
    *this = Bytes{buff};

    // Delete the temp buff[]
    delete[] buff;
}

// Function to implement pop_bk
void Bytes::pop_bk()
{
    int length = strlen(Str);
    char *buff = new char[length];

    // Copy character from Str
    // to buff[]
    for (int i = 0; i < length - 1; i++)
        buff[i] = Str[i];
    buff[length - 1] = '\0';

    // Assign the new String with
    // char a to String Str
    *this = Bytes{buff};

    // delete the buff[]
    delete[] buff;
}

// Function to implement get_length
int Bytes::len()
{
    return strlen(Str);
}

// Function to illuStrate ConStructor
// with no arguments
Bytes::Bytes()
    : Str{nullptr}
{
    Str = new char[1];
    Str[0] = '\0';
}

// Function to illuStrate ConStructor
// with one arguments
Bytes::Bytes(char *val)
{
    if (val == nullptr)
    {
        Str = new char[1];
        Str[0] = '\0';
    }

    else
    {

        Str = new char[strlen(val) + 1];

        // Copy character of val[]
        // using strcpy
        strcpy(Str, val);
        Str[strlen(val)] = '\0';
    }
}
Bytes::Bytes(const char *ch)
{
    if (ch == nullptr)
    {
        Str = new char[1];
        Str[0] = '\0';
    }

    else
    {

        Str = new char[strlen(ch) + 1];

        // Copy character of val[]
        // using strcpy
        strcpy(Str, ch);
        Str[strlen(ch)] = '\0';
    }
}
// Function to illuStrate
// Copy ConStructor
Bytes::Bytes(const Bytes &source)
{
    Str = new char[strlen(source.Str) + 1];
    strcpy(Str, source.Str);
}
// Function to illuStrate
// Move ConStructor
Bytes::Bytes(Bytes &&source)
{
    Str = source.Str;
    source.Str = nullptr;
}

// This function converts int to str.
auto to_str(int num)
{
    char *num_ = new char[2500];
    sprintf(num_, "%d", num);
    return Bytes(num_);
}
// This function converts double to str.
auto to_str(double num)
{
    char *num_ = new char[20];
    sprintf(num_, "%lf", num);
    return Bytes(num_);
}
// This function converts double to str.
auto to_str(long double num)
{
    char *num_ = new char[2000];
    sprintf(num_, "%Lf", num);
    return Bytes(num_);
}
auto to_str(long unsigned int num)
{
    char *num_ = new char[2000];
    sprintf(num_, "%lu", num);
    return Bytes(num_);
}
auto to_str(Bytes s)
{
    return s;
}
auto to_double(Bytes s)
{
    // char* ptr; 
    double d = atof(s.Str);
    // delete[] ptr;
    return d;
}
auto to_double(int i)
{
    return double(i);
}

//This is the class which have the features of dynamic sequence.
template<typename T>
class DynamicSequence{
     public:
        T* arr;
        // capacity is the total storage
        int capacity;
        // current is the number of elements
        int current;
     public:
        (DynamicSequence)(){
            arr = new T[1];
            capacity = 1;
            current = 0;
        }
        auto update(int index, T value){
            arr[index] = value;
        }
        auto push(T data){
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
            arr[current] = data;
            current++;
        }
        auto operator[](int index){
            return this->arr[index];
        }
        auto erase(T e){
            int i;
            for (i=0; i<this->current; i++)
                if (this->arr[i] == e)
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
template<typename T>
class StaticSequence{
    public:
        T* seq;
        i32 current = 0;
        StaticSequence(){}
        StaticSequence(int size){
            seq = new T[size];
        }
        void push(T element){
            seq[current] = element;
            current = current+1;
        }
        void pop(){
            seq[current-1] = T();
        }
        T* begin() { return &this->seq[0];}
        const T* begin() const { return &this->seq[0];}
        T* end() { return &this->seq[this->current]; }
        const T* end() const { return &this->seq[this->current];}
};


#endif // builtins_csq4
