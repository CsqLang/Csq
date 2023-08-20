#if !defined(basic_H)
#define basic_H
#include "../Runtime/memory.h"
#include "../Runtime/core.h"

void print(Cell arg){
    if(arg.type == STRING){
        printf("%s\n",arg.sval.c_str());
    }
    else{
        printf("%lf\n",arg.fval);
    }
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


#endif // basic_H
