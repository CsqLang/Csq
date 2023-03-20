/*
    This is the grammar for Csq4 generally
    we defines it by using some frameworks such as Bison
    but we don't want to increase complexity here so we are defining it
    inside the code only which can be directly accessed by the C/C++ code.
*/
#if !defined(Grammar_csq4)
#define Grammar_csq4

//Necessary imports
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <regex>
using std::string;
using std::vector;
using std::regex;


//Identifiers lookup
string IDENTIFIERS = "^[a-zA-Z_][a-zA-Z0-9_]*$";
//Value lookup
string INTEGER = "[+-]?\\d+";
string DECIMAL = "[+-]?\\d+(\\.\\d+)?";

//Operators lookup
//Arithmetic operators
vector<string> ARITHMETIC_OPERATORS = {"+","-","*","/","%","^"};
//Logical operators
vector<string> LOGICAL_OPERATORS = {"or","and","not"};
//Comparison operators
vector<string> COMPARISON_OPERATORS = {"==","!=","<",">","<=",">="};
//Assignment operators
vector<string> ASSIGNMENT_OPERATORS = {"="};
//Symbols lookup
vector<string> SYMBOLS = {"{","}","(",")","[","]",",","~","@","$","&","!",":",";","."};

//Keyword lookup
vector<string> KEYWORDS_TABLE = 
{
"if",
"elif",
"else",
"def",
"for",
"while",
"ends",
"endc",
"macro",
"import",
"in",
"init",
"public",
"private",
"inherits",
"protected",
"class",
"use",
"all",
"as",
"module",
"try",
"catch",
"break",
"continue",
};


/*
----------------------------------------------------------GRAMMAR RULES-----------------------------------------------------
[1] Expr
Represents:
          | any value is called an expression it could be either binary expr or just values and identifiers
Example:
        |  (a+4), 3, (464+44/3+x)

[2] Variable declaration or assignment
Represents:
          | any identifier with = is considered as variable decl or assignemnt
            | If the identifier is not declared in variable stack so it's variable decl
            | Else it's variable assignment
Syntax:
    <identifier> = <Expr>
Example:
        |Decleration:
        | a = 59
        |Assignment
        | a = 49
[3] Function declaration 
Represents:
          | any statement starting with def keyword is function or method.
Syntax:
    def <identifier>(<param>):
    ___.......
Example:
        def mytest():
            a = 95
*/

#endif // Grammar_csq4
