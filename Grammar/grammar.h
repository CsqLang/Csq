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
using std::string, std::vector;


//Identifiers lookup
string IDENTIFIERS = "^[a-zA-Z_][a-zA-Z0-9_]*$";

//Operators lookup
//Arithmetic operators
vector<string> ARITHMETIC_OPERATORS = {"+","-","*","/","%","^"};
//Logical operators
vector<string> LOGICAL_OPERATORS = {"or","and","not"};
//Comparison operators
vector<string> COMPARISON_OPERATORS = {"==","!=","<",">","<=",">="};
//Assignment operators
vector<string> ASSIGNMENT_OPERATORS = {"="};

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

#endif // Grammar_csq4
