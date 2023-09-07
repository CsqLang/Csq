#if !defined(EVAL_H)
#define EVAL_H

#include "core.h"
//Boolean funtions to tell that are the cells having equal value?
// bool mem_areEqual(Cell c1, Cell c2){
//     string lval,rval;
//     switch(c1.type){
//         case FLOAT:{
//             lval = to_string(c1.fval);
//         }
//         case STR:{
//             lval = c1.sval;
//         }
//     }
//     switch(c2.type){
//         case FLOAT:{
//             lval = to_string(c2.fval);
//         }
//         case STR:{
//             lval = c2.sval;
//         }
//     }
//     return lval == rval;
// }

// bool mem_notEqual(Cell c1, Cell c2){
//     return !mem_areEqual(c1,c2);
// }

// //Function to throw memory based errors
// void mem_error(string msg){
//     printf("Error: Memory error, %s\n",msg.c_str());
//     exit(0);
// }
// /*
// If we are directly going to eval the exprs so it will develop an interpreter but we want a compiler.
// */
// bool eval_isEqual(Cell c1, Cell c2) {
//     return mem_areEqual(c1,c2);
// }

// bool eval_isGreater(Cell c1, Cell c2) {
//     string lval,rval;
//     switch(c1.type){
//         case FLOAT:{
//             lval = to_string(c1.fval);
//         }
//         case STR:{
//             lval = c1.sval;
//         }
//     }
//     switch(c2.type){
//         case FLOAT:{
//             lval = to_string(c2.fval);
//         }
//         case STR:{
//             lval = c2.sval;
//         }
//     }
//     return lval > rval;
// }

// bool isLesser(Cell c1, Cell c2){
//     string lval,rval;
//     switch(c1.type){
//         case FLOAT:{
//             lval = to_string(c1.fval);
//         }
//         case STR:{
//             lval = c1.sval;
//         }
//     }
//     switch(c2.type){
//         case FLOAT:{
//             lval = to_string(c2.fval);
//         }
//         case STR:{
//             lval = c2.sval;
//         }
//     }
//     return lval < rval;
// }

// bool isGreaterEqual(Cell c1, Cell c2){
//     string lval,rval;
//     switch(c1.type){
//         case FLOAT:{
//             lval = to_string(c1.fval);
//         }
//         case STR:{
//             lval = c1.sval;
//         }
//     }
//     switch(c2.type){
//         case FLOAT:{
//             lval = to_string(c2.fval);
//         }
//         case STR:{
//             lval = c2.sval;
//         }
//     }
//     return lval >= rval;
// }

// bool isLesserEqual(Cell c1, Cell c2){
//     string lval,rval;
//     switch(c1.type){
//         case FLOAT:{
//             lval = to_string(c1.fval);
//         }
//         case STR:{
//             lval = c1.sval;
//         }
//     }
//     switch(c2.type){
//         case FLOAT:{
//             lval = to_string(c2.fval);
//         }
//         case STR:{
//             lval = c2.sval;
//         }
//     }
//     return lval <= rval;
// }
//This creates a cell for the operations
Cell f_val(double val){
    Cell c;
    c.type = FLOAT;
    c.fval = val;
    return c;
}

Cell s_val(string val){
    Cell c;
    c.type = STRING;
    c.sval = val;
    return c;
}

#endif // EVAL_H
