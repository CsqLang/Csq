#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include "codes.h"
#include <iostream>
#include <iomanip>

void print(const Cell& cell) {
    switch (cell.type) {
        case Type::INT:
            std::cout << cell.intVal;
            break;
        case Type::FLOAT:
            std::cout << std::fixed << std::setprecision(6) << cell.floatVal; // Print floats with 6 decimal places
            break;
        case Type::STRING:
            std::cout << *cell.stringVal; // Assuming stringVal is a pointer to a std::string
            break;
        case Type::COMPOUND:
            std::cout << "[ ";
            for (const Cell& item : *cell.vectorVal) {
                print(item); // Recursively print elements of the compound type
                std::cout << " ";
            }
            std::cout << "]";
            break;
        default:
            std::cout << "Unknown type"; // Handle unknown types
            break;
    }
}

bool _cond_(bool state){
    return state;
}

#endif // basic_H
