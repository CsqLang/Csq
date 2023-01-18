#if !defined(Builtins_CSQ4)
#define Builtins_CSQ4
///IMPORTS///
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/// @brief Integer types///////////////////////////////////////////////////////
class int64{
    public:
        int64_t val = 0;
        int64(){}
        int64(int64_t val){this->val = val;}
};
class int32{
    public:
        int32_t val = 0;
        int32(){}
        int32(int32_t val){this->val = val;}
};
class int16{
    public:
        int16_t val = 0;
        int16(){}
        int16(int16_t val){this->val = val;}
};
class int8{
    public:
        int8_t val = 0;
        int8(){}
        int8(int8_t val){this->val = val;}
};
/////////////////////////////////Float types//////////////////////////////
class float32{
    public:
        float val = 0;
        float32(){}
        float32(float val){this->val = val;}
};
class float64{
    public:
        double val = 0;
        float64(){}
        float64(double val){this->val = val;}
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
#include <bits/c++config.h>

    namespace std
    {
    /// initializer_list
    template<class _E>
        class initializer_list
        {
        public:
        typedef _E 		value_type;
        typedef const _E& 	reference;
        typedef const _E& 	const_reference;
        typedef size_t 		size_type;
        typedef const _E* 	iterator;
        typedef const _E* 	const_iterator;

        private:
        iterator			_M_array;
        size_type			_M_len;

        // The compiler can call a private constructor.
        constexpr initializer_list(const_iterator __a, size_type __l)
        : _M_array(__a), _M_len(__l) { }

        public:
        constexpr initializer_list() noexcept
        : _M_array(0), _M_len(0) { }

        // Number of elements.
        constexpr size_type
        size() const noexcept { return _M_len; }

        // First element.
        constexpr const_iterator
        begin() const noexcept { return _M_array; }

        // One past the last element.
        constexpr const_iterator
        end() const noexcept { return begin() + size(); }
        };

    /**
     *  @brief  Return an iterator pointing to the first element of
     *          the initializer_list.
     *  @param  __ils  Initializer list.
     */
    template<class _Tp>
        constexpr const _Tp*
        begin(initializer_list<_Tp> __ils) noexcept
        { return __ils.begin(); }

    /**
     *  @brief  Return an iterator pointing to one past the last element
     *          of the initializer_list.
     *  @param  __ils  Initializer list.
     */
    template<class _Tp>
        constexpr const _Tp*
        end(initializer_list<_Tp> __ils) noexcept
        { return __ils.end(); }
    }
    //This is the class which have the features of dynamic array.
    template<typename T>
    class basic_array{
         public:
            T* arr;
            // capacity is the total storage
            int capacity;
            // current is the number of elements
            int current;
         public:
            (basic_array)(){
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
            // ~basic_array(){delete[] arr;}
    };//basic_array
#endif // Builtins_CSQ4
