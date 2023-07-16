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
#endif // basic_H
