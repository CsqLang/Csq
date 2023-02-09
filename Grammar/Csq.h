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
//Types of operators
array<str> Arithmentic_Operators = {"+","-","*","/","%","^"};
array<str> Logical_Operators = {"or","and","not"};
array<str> Comparison_Operators = {"==","!=","<",">","<=","<"};
array<str> Assignment_Operators = {"=","+=","-=","*=","/="};
array<str> AllOperators = {"||","&&","==","!=","<=","<","+=","-=","*=","/="};
//////////////////////////////////
// Reserved Tokens | Keywords
dict<str,str> ReservedTokens = {
{"if","else","elif","def","class","const","meth","public","private","inherit","ends","for","delete",
"new","import","in"
},
{"IF","ELSE","ELIF","DEF","CLASS","const","DEF","public:","private:",":","ENDS","FOR","delete",
"new","import","IN"
}
};
//Bytecode grammar
dict<str,str> BytecodeGrammar = {
{"(",")","\"","[","]",":",",",";","+","-","*",
"|","&","&&","||","<",">","=",".","{","}","==",
"!=","<=",">=","~","+=","-=","*=","/=","%=","&=",
"++","--","\""},
{"LPAR","RPAR","LSQB","RSQB","COLON","COMMA","SEMI",
"PLUS","MINUS","STAR","VBAR","AMPER","AND",
"OR","LESS","GREATER","EQUAL","DOT","LBRACE",
"RBRACE","EQEQUAL","NOTEQUAL","LESSEQUAL","GREATEREQUAL",
"TILDE","POW","PLUSEQUAL","MINEQUAL","STAREQUAL","SLASHEQUAL",
"PERCENTEQUAL","AMPEREQUAL","INCREMENT","DECREMENT"}
};
str comment = "#";

/*Token's string reperesentation to increase readability*/
str COLON = ":";
str LBRACE = "{";
str RBRACE = "}";
str LPAR = "(";
str RPAR = "(";
str LSQB = "[";
str RSQB = "]";
str SEMI = ";";
str COMMA = ",";

/*Keyword's string reperesentation*/
str IF = "if";
str ELSE = "else";
str ELIF = "elif";
str FOR = "for";
str WHILE = "while";
str CLASS = "class";
str DEF = "def";
str ENDS = "ends";
str IN = "in";
str ENDC = "endc";
str INIT = "init";
str IMPORT = "import";
/*
#Functions in Csq Syntax
def <name>()
    ....
<name> ends
#Variables in Csq Syntax
<name>:<type> = <reference>
#Classes syntax
class <name>
    .....
endc
*/

#endif // Csq_Grammar_h
