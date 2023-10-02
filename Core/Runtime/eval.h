#if !defined(EVAL_H)
#define EVAL_H

#include "core.h"

Cell f_val(double val){

    return {FLOAT, 0, 0, val};
}

Cell i_val(int val){
    return {INT, 0, val};
}

Cell s_val(string val){
    return {STRING, 0, 0, 0.0, val.substr(1, val.size() - 2)};
}

#endif // EVAL_H
