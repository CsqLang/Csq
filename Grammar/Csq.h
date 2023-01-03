#if !defined(Csq_Grammar_h)
#define Csq_Grammar_h
#include "../libs/utils/stringlib.h"
#include "../libs/utils/dict.h"
//Patterns for Typical Csq4 code
//Pattern for identifiers.
str identifier = "^[a-zA-Z_][a-zA-Z0-9_]*$";
//Pattern for integers
str integers = "[0-9]";
str negative_integers = "-[0-9]";
//Pattern for floating point values:
str negative_floats = "-.[0-9]";
str positive_floats = ".[0-9]";
/////////////////////////////////
dict<str,str> Grammar = {
{"(",")","[","]",":",",",";","+","-","*","/",
"|","&","&&","||","<",">","=",".","%","{","}","==",
"!=","<=",">=","~","+=","-=","*=","/=","%=","&=",
"++","--"},
{"LPAR","RPAR","LSQB","RSQB","COLON","COMMA","SEMI",
"PLUS","MINUS","STAR","SLASH","VBAR","AMPER","AND",
"OR","LESS","GREATER","EQUAL","DOT","PERCENT","LBRACE",
"RBRACE","EQEQUAL","NOTEQUAL","LESSEQUAL","GREATEREQUAL",
"TILDE","POW","PLUSEQUAL","MINEQUAL","STAREQUAL","SLASHEQUAL",
"PERCENTEQUAL","AMPEREQUAL","INCREMENT","DECREMENT"}
};
//////////////////////////////////
// Reserved Tokens
dict<str,str> ReservedTokens = {
{"if","else","elif","def","class","const","meth","public","private","inherit","ends","for","delete",
"new","import","in"
},
{"IF","ELSE","ELIF","DEF","CLASS","const","DEF","public:","private:",":","ENDS","FOR","delete",
"new","import","IN"
}
};
#endif // Csq_Grammar_h
