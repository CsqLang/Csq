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
};

struct Cell {
    Type type;
    union {
        int intVal;
        float floatVal;
        std::string* stringVal;
        std::vector<Cell>* vectorVal;
    };
    
    alignas(float) char smallBuffer[sizeof(std::string)];  // Size of float for alignment
    
    Cell() : type(Type::INT), intVal(0) {}
    
    explicit Cell(int val) : type(Type::INT), intVal(val) {}
    explicit Cell(float val) : type(Type::FLOAT), floatVal(val) {}
    Cell(const std::string& val) : type(Type::STRING) {
        stringVal = new (smallBuffer) std::string(val);
    }
    Cell(const std::vector<Cell>& val) : type(Type::COMPOUND) {
        vectorVal = new std::vector<Cell>(val);
    }
    
    ~Cell() {
        if (type == Type::STRING) {
            stringVal->~basic_string();
        }
        else if (type == Type::COMPOUND) {
            delete vectorVal;
        }
    }
    
    Cell(const Cell& other) : type(other.type) {
        switch (other.type) {
            case Type::INT:
                intVal = other.intVal;
                break;
            case Type::FLOAT:
                floatVal = other.floatVal;
                break;
            case Type::STRING:
                stringVal = new (smallBuffer) std::string(*other.stringVal);
                break;
            case Type::COMPOUND:
                vectorVal = new std::vector<Cell>(*other.vectorVal);
                break;
        }
    }

    // Move constructor
    Cell(Cell&& other) : type(other.type) {
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
    Cell& operator=(const Cell& other) {
        if (this != &other) {
            if (this->type == other.type) {
                // Same type, directly copy the values
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
                this->~Cell();  // Destroy current data
                new (this) Cell(other);  // Copy construct
            }
        }
        return *this;
    }

    // Move assignment operator
    Cell& operator=(Cell&& other) {
        if (this != &other) {
            this->~Cell();  // Destroy current data
            new (this) Cell(std::move(other));  // Move construct
        }
        return *this;
    }

    Cell& operator[](size_t index) {
        if (type == Type::COMPOUND && vectorVal != nullptr && index < vectorVal->size()) {
            return (*vectorVal)[index];
        } else {
            // Handle the case where the cell is not a vector or the index is out of bounds.
            // You can return a default value or handle this case as needed.
            return *this; // Return the current cell, you can change this to a default value if needed.
        }
    }

    // Overload the + operator
    Cell operator+(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal + other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal + other.floatVal);
        }
        return Cell(); // Default case
    }

    // Overload the - operator
    Cell operator-(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal - other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal - other.floatVal);
        }
        return Cell(); // Default case
    }

    // Member function to overload the * operator for multiplication
    Cell operator*(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            return Cell(intVal * other.intVal);
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return Cell(floatVal * other.floatVal);
        }
        return Cell(); // Default case
    }

    // Overload the / operator
    Cell operator/(const Cell& other) const {
        if (type == Type::INT && other.type == Type::INT) {
            if (other.intVal != 0) {
                return Cell(intVal / other.intVal);
            } else {
                // Handle division by zero error here
                // You can return a specific value or throw an exception.
                return Cell(); // Default case
            }
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            if (other.floatVal != 0.0f) {
                return Cell(floatVal / other.floatVal);
            } else {
                // Handle division by zero error here
                // You can return a specific value or throw an exception.
                return Cell(); // Default case
            }
        }
        return Cell(); // Default case
    }

    // Overload the == operator
    bool operator==(const Cell& other) const {
        // Define your equality comparison logic based on the types
        if (type == other.type) {
            switch (type) {
                case Type::INT:
                    return intVal == other.intVal;
                case Type::FLOAT:
                    return floatVal == other.floatVal;
                case Type::STRING:
                    return (*stringVal) == (*other.stringVal);
                case Type::COMPOUND:
                    // Define equality comparison for compound types
                    // You may need to iterate through the vectors, comparing elements.
                    return false; // Default case
                default:
                    return false; // Default case
            }
        }
        return false; // Default case
    }

    // Overload the != operator
    bool operator!=(const Cell& other) const {
        // Define your inequality comparison logic here based on the types
        return !(*this == other);
    }

    // Overload the >= operator
    bool operator>=(const Cell& other) const {
        // Define your greater than or equal to comparison logic here based on the types
        if (type == Type::INT && other.type == Type::INT) {
            return intVal >= other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal >= other.floatVal;
        }
        return false; // Default case
    }

    // Overload the > operator
    bool operator>(const Cell& other) const {
        // Define your greater than comparison logic here based on the types
        if (type == Type::INT && other.type == Type::INT) {
            return intVal > other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal > other.floatVal;
        }
        return false; // Default case
    }

    // Overload the < operator
    bool operator<(const Cell& other) const {
        // Define your less than comparison logic here based on the types
        if (type == Type::INT && other.type == Type::INT) {
            return intVal < other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal < other.floatVal;
        }
        return false; // Default case
    }

    // Overload the <= operator
    bool operator<=(const Cell& other) const {
        // Define your less than or equal to comparison logic here based on the types
        if (type == Type::INT && other.type == Type::INT) {
            return intVal <= other.intVal;
        } else if (type == Type::FLOAT && other.type == Type::FLOAT) {
            return floatVal <= other.floatVal;
        }
        return false; // Default case
    }
};

//Storing overall programs memory
vector<Cell> memory;

#endif // MEMORY_CSQ4