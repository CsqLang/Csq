#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include "codes.h"
#include <iostream>

void print(Cell arg)
{
    if (arg.type == STRING)
    {
        printf("%s\n", arg.sval.c_str());
    }
    else if (arg.type == COMPOUND)
    {
        for (Cell c : arg.array)
        {
            print(c);
            printf(" ");
        }
        printf("\n");
    }
    else if (arg.type == FLOAT)
    {
        printf("%lf\n", arg.fval);
    }
    else
    {
        printf("%d\n", arg.ival);
    }
}

Cell range(Cell lim)
{
    Cell vals;
    vals.type = COMPOUND;
    for (int i = 0; i < lim.ival; i++)
        vals.array.push_back(i_val(i));
    return vals;
}

bool _cond_(Cell arg)
{
    if (arg.type == FLOAT)
    {
        return arg.fval;
    }
    else if (arg.type == INT)
    {
        return arg.ival;
    }
    else
    {
        printf("Error: couldn't use a string value as condition.\n");
        exit(0);
    }
}

Cell len(Cell arg)
{
    Cell c;
    c.type = INT;
    if (arg.type == STRING)
    {
        c.ival = arg.sval.size();
    }
    else if (arg.type == COMPOUND)
    {
        c.ival = arg.array.size();
    }
    return c;
}

Cell type(Cell arg)
{
    Cell c;
    c.type = STRING;
    if (arg.type == STRING)
    {
        c.sval = "string";
    }
    else if (arg.type == COMPOUND)
    {
        c.sval = "compound";
    }
    else if (arg.type == FLOAT)
    {
        c.sval = "float";
    }
    else
    {
        c.sval = c.__class__;
    }
    return c;
}

Cell input(Cell prompt)
{
    Cell c;
    c.type = STRING;
    print(prompt);
    cin >> c.sval;
    return c;
}

Cell push(Cell array_, Cell value)
{
    Cell arr;
    arr.array = array_.array;
    arr.array.push_back(value);
    arr.type = COMPOUND;
    return arr;
}

#endif // basic_H
