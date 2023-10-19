#if !defined(CLASSCSQ_H)
#define CLASSCSQ_H

#include <functional>
#include <map>
#include <any>
#include "memory.h"
using LambdaType = function<Cell(Cell)>;
/*
This in every case will be representing a class
*/
class Class {
public:
    string name;
    map<string, LambdaType> methods;
    map<string, Cell> members;
};

#endif // CLASSCSQ_H
