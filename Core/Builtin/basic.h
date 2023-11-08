#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include "codes.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

void print_(const Cell& cell) {
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
                print_(item);
                std::cout << " ";
            }
            std::cout << "]\n";
            break;
        default:
            std::cout << "Unknown type";
            break;
    }
}

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
                print_(item);
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

Cell type(Cell val){
    switch(val.type){
        case Type::INT:{
            return Cell("int");
            break;
        }
        case Type::FLOAT:{
            return Cell("float");
            break;
        }
        case Type::COMPOUND:{
            return Cell("compound");
            break;
        }
        case Type::STRING:{
            return Cell("string");
            break;
        }
        default:{
            return Cell("custype");
            break;
        }
    }
}

Cell _push_elem(Cell ls, Cell elem){
    ls.vectorVal->push_back(elem);
    return ls;
}

Cell _pop_elem(Cell ls){
    ls.vectorVal->pop_back();
    return ls;
}

Cell len(Cell arr){
    return Cell(int(arr.vectorVal->size()));
}

Cell object(Cell name){
    Cell obj;
    obj.__class__ = *(name.stringVal);
    cout << obj.__class__;
    obj.type = Type::CUSTYPE;
    return obj;
}


#endif // basic_H
