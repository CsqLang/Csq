#if !defined(STR_H_UTILS)
#define STR_H_UTILS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Class str
class str
{
    // Prototype for '+'
    // operator overloading
    friend str operator+(
        const str &lhs,
        const str &rhs);

public:
    char *Str;
    // No arguments constructor
    str();
    // pop_back() function
    void pop_bk();

    // push_back() function
    void push_bk(char a);

    // To get the length
    int len();
    // This is used to store the result of concatination.
    auto operator+=(const str &rhs);
    // This is used to get the element at the given index.
    auto operator[](int index) { return Str[index]; }
    // This will return 1 if given str is equal to this->Str.
    // This will return 1 if given str is equal to this->Str.
    auto operator==(const str &s)
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
    auto operator!=(const str &s)
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
        return str(Str);
    }
    auto operator*(int s);
    // Function to copy the String
    // of length len from position pos
    void copy(char s[], int len, int pos);
    // Swap Strings function
    void swp(str &rhs);

    // ConStructor with 1 arguments
    str(char *val);
    str(const char *val);

    // Copy ConStructor
    str(const str &source);

    // Move ConStructor
    str(str &&source);

    // Overloading the assignment
    // operator
    str &operator=(
        const str &rhs);
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
    ~str() { delete Str; }
};

// Overloading the assignment operator
str &str::operator=(
    const str &rhs)
{
    if (this == &rhs)
        return *this;
    delete[] Str;
    Str = new char[strlen(rhs.Str) + 1];
    strcpy(Str, rhs.Str);
    return *this;
}

// Overloading the plus operator
str operator+(const str &lhs,
              const str &rhs)
{
    int length = strlen(lhs.Str) + strlen(rhs.Str);

    char *buff = new char[length + 1];

    // Copy the Strings to buff[]
    strcpy(buff, lhs.Str);
    strcat(buff, rhs.Str);
    buff[length] = '\0';

    // String temp
    str temp{buff};

    // delete the buff[]
    delete[] buff;

    // Return the concatenated String
    return temp;
}
auto str::operator+=(const str &rhs)
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
auto str::operator*(int s)
{
    str n;
    for (int i = 0; i < s; i++)
    {
        n += str(this->Str);
    }
    return n;
}
// Function to copy the String
void str::copy(char s[], int len,
               int pos)
{
    for (int i = 0; i < len; i++)
    {
        s[i] = Str[pos + i];
    }
    s[len] = '\0';
}

// Function to implement push_bk
void str::push_bk(char a)
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
    *this = str{buff};

    // Delete the temp buff[]
    delete[] buff;
}

// Function to implement pop_bk
void str::pop_bk()
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
    *this = str{buff};

    // delete the buff[]
    delete[] buff;
}

// Function to implement get_length
int str::len()
{
    return strlen(Str);
}

// Function to illuStrate ConStructor
// with no arguments
str::str()
    : Str{nullptr}
{
    Str = new char[1];
    Str[0] = '\0';
}

// Function to illuStrate ConStructor
// with one arguments
str::str(char *val)
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
str::str(const char *ch)
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
str::str(const str &source)
{
    Str = new char[strlen(source.Str) + 1];
    strcpy(Str, source.Str);
}
// Function to illuStrate
// Move ConStructor
str::str(str &&source)
{
    Str = source.Str;
    source.Str = nullptr;
}

// This function converts int to str.
auto to_str(int num)
{
    char *num_ = new char[2500];
    sprintf(num_, "%d", num);
    return str(num_);
}
// This function converts double to str.
auto to_str(double num)
{
    char *num_ = new char[20];
    sprintf(num_, "%lf", num);
    return str(num_);
}
// This function converts double to str.
auto to_str(long double num)
{
    char *num_ = new char[2000];
    sprintf(num_, "%Lf", num);
    return str(num_);
}
auto to_str(long unsigned int num)
{
    char *num_ = new char[2000];
    sprintf(num_, "%lu", num);
    return str(num_);
}
auto to_str(str s)
{
    return s;
}
auto to_double(str s)
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

void replace(char str[], char sub[], char nstr[])

{

    int strLen, subLen, nstrLen;

    int i = 0, j, k;

    int flag = 0, start, end;

    strLen = strlen(str);

    subLen = strlen(sub);

    nstrLen = strlen(nstr);

    for (i = 0; i < strLen; i++)

    {

        flag = 0;

        start = i;

        for (j = 0; str[i] == sub[j]; j++, i++)

            if (j == subLen - 1)

                flag = 1;

        end = i;

        if (flag == 0)

            i -= j;

        else
        {
            for (j = start; j < end; j++)

            {

                for (k = start; k < strLen; k++)

                    str[k] = str[k + 1];

                strLen--;

                i--;
            }

            for (j = start; j < start + nstrLen; j++)

            {

                for (k = strLen; k >= j; k--)

                    str[k + 1] = str[k];

                str[j] = nstr[j - start];

                strLen++;

                i++;
            }
        }
    }
}
str replaceStr(const char *s, const char *oldW,
               const char *newW)
{
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; (s[i] != '\0'); i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s)
    {
        // compare the substring with the result
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return str(result);
}

#endif // STR_H_UTILS