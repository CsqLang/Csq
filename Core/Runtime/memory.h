#if !defined(MEMORY_CSQ4)
#define MEMORY_CSQ4
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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
        float floatVal;
        string* stringVal;
        vector<Cell>* vectorVal;
        string* __class__;
    };

    inline Cell() : type(Type::INT), intVal(0) {}

    inline explicit Cell(int val) : type(Type::INT), intVal(val) {}

    inline explicit Cell(float val) : type(Type::FLOAT), floatVal(val) {}

    inline Cell(const string& val) : type(Type::STRING) {
        stringVal = new string(val);
    }

    inline Cell(const vector<Cell>& val) : type(Type::COMPOUND) {
        vectorVal = new vector<Cell>(val);
    }

    inline ~Cell() {
        if (type == Type::STRING && stringVal) {
            delete stringVal;
        } else if (type == Type::COMPOUND) {
            delete vectorVal;
        }
    }

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
                __class__ = new string(*other.__class__);
                break;
        }
    }

    // Move constructor
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
        }
    }

    // Assignment operator
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
                }
            } else {
                this->~Cell();
                new (this) Cell(other);
            }
        }
        return *this;
    }

    // Move assignment operator
    inline Cell& operator=(Cell&& other) {
        if (this != &other) {
            this->~Cell();
            new (this) Cell(std::move(other));
        }
        return *this;
    }

    inline Cell& operator[](size_t index) {
        if (type == Type::COMPOUND && vectorVal && index < vectorVal->size()) {
            return (*vectorVal)[index];
        } else {
            return *this; // You can change this to return a default value if needed.
        }
    }

    inline Cell operator+(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return Cell(intVal + other.intVal);
            case Type::FLOAT:
                return Cell(floatVal + other.floatVal);
            default:
                return Cell(); // Default case
        }
    }

    inline Cell operator-(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return Cell(intVal - other.intVal);
            case Type::FLOAT:
                return Cell(floatVal - other.floatVal);
            default:
                return Cell(); // Default case
        }
    }

    inline Cell operator*(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return Cell(intVal * other.intVal);
            case Type::FLOAT:
                return Cell(floatVal * other.floatVal);
            default:
                return Cell(); // Default case
        }
    }

    inline Cell operator/(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            if (other.intVal != 0) {
                return Cell(intVal / other.intVal);
            } else {
                return Cell(); // Handle division by zero error.
            }
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            if (other.floatVal != 0.0f) {
                return Cell(floatVal / other.floatVal);
            } else {
                return Cell(); // Handle division by zero error.
            }
        }
        return Cell(); // Default case
    }

    inline bool operator==(const Cell& other) const {
        if (type == other.type) {
            switch (type) {
                case Type::INT:
                    return intVal == other.intVal;
                case Type::FLOAT:
                    return floatVal == other.floatVal;
                case Type::STRING:
                    return *stringVal == *other.stringVal;
                case Type::COMPOUND:
                    return *vectorVal == *other.vectorVal; // Implement proper comparison for vectors
                default:
                    return false;
            }
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
            case Type::FLOAT:
                return floatVal > other.floatVal;
            default:
                return false; // Default case
        }
    }

    inline bool operator<(const Cell& other) const {
        switch(other.type) {
            case Type::INT:
                return intVal < other.intVal;
            case Type::FLOAT:
                return floatVal < other.floatVal;
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

vector<Cell> memory;

inline void freeMemory() {
    memory = {};
}

#endif // MEMORY_CSQ4
