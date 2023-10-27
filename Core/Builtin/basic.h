#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include "codes.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void print(const Cell& cell) {
    switch (cell.type) {
        case Type::INT:
            std::cout << cell.intVal;
            break;
        case Type::FLOAT:
            std::cout <<  cell.floatVal;
            break;
        case Type::STRING:
            std::cout << *cell.stringVal;
            break;
        case Type::COMPOUND:
            std::cout << "[ ";
            for (const Cell& item : *cell.vectorVal) {
                print(item);
                std::cout << " ";
            }
            std::cout << "]";
            break;
        default:
            std::cout << "Unknown type";
            break;
    }printf("\n");
}

bool _cond_(bool state){
    return state;
}

Cell len(Cell arr){
    return Cell(int(arr.vectorVal->size()));
}

Cell object(Cell name){
    Cell obj;
    obj.__class__ = name.stringVal;
    obj.type = Type::CUSTYPE;
    return obj;
}


#endif // basic_H
