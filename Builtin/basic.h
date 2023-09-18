#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"
#include <iostream>


void print(Cell arg){
    if(arg.type == STRING){
        printf("%s",arg.sval.c_str());
    }
    else if(arg.type == COMPOUND){
        for(Cell c : arg.array){
            print(c);
            printf(" ");
        }
        printf("\n");
    }
    else{
        printf("%lf",arg.fval);
    }
}

Cell range(Cell lim){
    Cell vals;
    vals.type = COMPOUND;
    for(int i = 0;i<lim.fval;i++)
        vals.array.push_back(f_val(i));
    return vals;
}

bool _cond_(Cell arg){
    if(arg.type == FLOAT){
        return arg.fval;
    }
    else{
        printf("Error: couldn't use a string value as condition.\n");
        exit(0);
    }
}

Cell len(Cell arg){
    Cell c;
    c.type = FLOAT;
    if(arg.type == STRING){
        c.fval = arg.sval.size();    
    }
    else if(arg.type == COMPOUND){
        c.fval = arg.array.size();    
    }
    return c;
}

Cell type(Cell arg){
    Cell c;
    c.type = STRING;
    if(arg.type == STRING){
        c.sval = "string";
    }
    else if(arg.type == COMPOUND){
        c.sval = "compound";
    }
    else if(arg.type == FLOAT){
        c.sval = "float";
    }
    return c;
}

Cell input(Cell prompt){
    Cell c;
    c.type = STRING;
    print(prompt);
    cin >> c.sval;
    return c;
}


#endif // basic_H
