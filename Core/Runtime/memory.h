#if !defined(MEMORY_CSQ4)
#define MEMORY_CSQ4

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>

using namespace std;

enum class Type {
    INT,
    FLOAT,
    STRING,
    COMPOUND,
    CUSTYPE,
};

struct Cell {
    Type type;
    union {
        int intVal;
        double floatVal;
        string* stringVal;
        vector<Cell>* vectorVal;
        
    };
    string __class__;
    // Constructors
    inline Cell() : type(Type::INT), intVal(0) {}

    inline Cell(int val) : type(Type::INT), intVal(val) {}

    inline Cell(double val) : type(Type::FLOAT), floatVal(val) {}

    inline Cell(const string& val) : type(Type::STRING), stringVal(new string(val)) {}

    inline Cell(const vector<Cell>& val) : type(Type::COMPOUND), vectorVal(new vector<Cell>(val)) {}
    inline Cell(initializer_list<Cell> val){
        vector<Cell> v;
        for(Cell c : val){
            v.push_back(c);
        }
        vectorVal = new vector<Cell>(v);
        type = Type::COMPOUND;
    }
    ~Cell() {
    switch (type) {
        case Type::STRING:
            if (stringVal != nullptr) {
                delete stringVal;
            }
            break;
        case Type::COMPOUND:
            if (vectorVal != nullptr) {
                delete vectorVal;
            }
            break;
        // Add cases for other types as needed
    }
}
    // Copy Constructor
    inline Cell(const Cell& other) : type(other.type) {
        switch (other.type) {
            case Type::INT:
                intVal = other.intVal;
                break;
            case Type::FLOAT:
                floatVal = other.floatVal;
                break;
            case Type::STRING:
                stringVal = new string(*other.stringVal);
                break;
            case Type::COMPOUND:
                vectorVal = new vector<Cell>(*other.vectorVal);
                break;
            case Type::CUSTYPE:
                __class__ = (other.__class__);
                break;
        }
    }

    // Move Constructor
    inline Cell(Cell&& other) : type(other.type) {
        switch (other.type) {
            case Type::INT:
                intVal = other.intVal;
                break;
            case Type::FLOAT:
                floatVal = other.floatVal;
                break;
            case Type::STRING:
                stringVal = other.stringVal;
                other.stringVal = nullptr;
                break;
            case Type::COMPOUND:
                vectorVal = other.vectorVal;
                other.vectorVal = nullptr;
                break;
            default:
                break;
        }
    }

    // Assignment Operator
    inline Cell& operator=(const Cell& other) {
        if (this != &other) {
            if (type == other.type) {
                switch (type) {
                    case Type::INT:
                        intVal = other.intVal;
                        break;
                    case Type::FLOAT:
                        floatVal = other.floatVal;
                        break;
                    case Type::STRING:
                        *stringVal = *other.stringVal;
                        break;
                    case Type::COMPOUND:
                        *vectorVal = *other.vectorVal;
                        break;
                    default:
                        break;
                }
            } else {
                // this->~Cell();
                new (this) Cell(other);
            }
        }
        return *this;
    }

    // Move Assignment Operator
    inline Cell& operator=(Cell&& other) {
        if (this != &other) {
            // this->~Cell();
            new (this) Cell(std::move(other));
        }
        return *this;
    }

    const Cell& operator[](const Cell& index) const{
        return (*vectorVal)[index.intVal];
    }

    inline Cell operator+(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal + other.intVal);
        } else if(type == Type::STRING){
            return Cell((*stringVal) + (*other.stringVal));
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal + other.floatVal);
        } else if(type == Type::FLOAT && other.type == Type::INT){
            return Cell(floatVal + float(other.intVal));
        } else if(type == Type::INT && other.type == Type::FLOAT){
            return Cell(float(intVal) + (other.floatVal));
        }
        return Cell(); // Default case
    }

    inline Cell operator-(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal - other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal - other.floatVal);
        } else if(type == Type::FLOAT && other.type == Type::INT){
            return Cell(floatVal - float(other.intVal));
        } else if(type == Type::INT && other.type == Type::FLOAT){
            return Cell(float(intVal) - (other.floatVal));
        }
        return Cell(); // Default case
    }

    inline Cell operator*(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal * other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal * other.floatVal);
        } else if(type == Type::FLOAT && other.type == Type::INT){
            return Cell(floatVal * float(other.intVal));
        } else if(type == Type::INT && other.type == Type::FLOAT){
            return Cell(float(intVal) * (other.floatVal));
        }
        return Cell(); // Default case
    }

    inline Cell operator/(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT && other.intVal != 0) {
            return Cell(intVal / other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT && other.floatVal != 0.0f) {
            return Cell(floatVal / other.floatVal);
        } else if(type == Type::FLOAT && other.type == Type::INT){
            return Cell(floatVal / float(other.intVal));
        } else if(type == Type::INT && other.type == Type::FLOAT){
            return Cell(float(intVal) / (other.floatVal));
        }
        return Cell(); // Default case
    }

    inline bool operator==(const Cell& other) const {
            switch (type) {
                case Type::INT:
                    if(other.type == Type::FLOAT){
                        return intVal == int(other.floatVal);
                    }
                    else if(other.type == Type::INT){
                        return intVal == other.intVal;
                    }else{
                        //Throw runtime error
                        switch(other.type){
                            case Type::STRING:{
                                printf("%s\n", string("Csq TypeError: couldn't compare the values of type int and string").c_str());
                                return 0;
                            }
                            case Type::COMPOUND:{
                                printf("%s\n", string("Csq TypeError: couldn't compare the values of type int and compound").c_str());
                                return 0;
                            }default:{
                                return 0;
                            }
                        }
                    }
                case Type::FLOAT:
                    if(other.type == Type::FLOAT){
                        return floatVal == int(other.floatVal);
                    }
                    else if(other.type == Type::INT){
                        return floatVal == float(other.intVal);
                    }else{
                        //Throw runtime error
                        switch(other.type){
                            case Type::STRING:{
                                printf("%s\n", string("Csq TypeError: couldn't compare the values of type float and string").c_str());
                                return 0;
                            }
                            case Type::COMPOUND:{
                                printf("%s\n", string("Csq TypeError: couldn't compare the values of type float and compound").c_str());
                                return 0;
                            }default:{
                                return 0;
                            }
                        }
                    }
                case Type::STRING:
                    return *stringVal == *other.stringVal;
                case Type::COMPOUND:
                    return *vectorVal == *other.vectorVal; // Implement proper comparison for vectors
                default:
                    return false;
            }
        return false;
    }

    inline bool operator!=(const Cell& other) const {
        return !(*this == other);
    }

    inline bool operator>=(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return intVal >= other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal >= other.floatVal;
        }
        return false;
    }

    inline bool operator>(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return intVal > other.intVal;
                break;
            case Type::FLOAT:
                return floatVal > other.floatVal;
                break;
            default:
                return false; // Default case
                break;
        }
    }

    inline bool operator<(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return intVal < other.intVal;
                break;
            case Type::FLOAT:
                return floatVal < other.floatVal;
                break;
            default:
                return false; // Default case
        }
    }

    inline bool operator<=(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return intVal <= other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal <= other.floatVal;
        }
        return false;
    }
};


// map<int, Cell> memory;
// Collection for values
vector<Cell> memory;
inline void freeMemory() {
    memory.clear();
}


#endif // MEMORY_CSQ4
