#if !defined(EVAL_H)
#define EVAL_H

#include "core.h"

Cell f_val(double val){
    Cell c;
    c.type = FLOAT;
    c.fval = val;
    return c;
}

Cell s_val(string val){
    val.pop_back();
    Cell c;
    c.type = STRING;
    for(int i = 1;i<val.size();i++){
        c.sval.push_back(val[i]);
    }
    return c;
}

#endif // EVAL_H
