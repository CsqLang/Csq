#if !defined(EVAL_H)
#define EVAL_H

#include "core.h"

Cell f_val(double val) {
    Cell c;
    c.floatVal = val;
    c.type = Type::FLOAT;
    return c;
}

Cell i_val(int val) {
    return Cell(val);
}

Cell s_val(const std::string& val) {
    return Cell(val);
}

#endif // EVAL_H
