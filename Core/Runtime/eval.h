#if !defined(EVAL_H)
#define EVAL_H

#include "core.h"

Cell f_val(double val){

    return {val};
}

Cell i_val(int val){
    return {INT, val};
}

Cell s_val(string val){
    return {val.substr(1, val.size() - 2)};
}

#endif // EVAL_H
