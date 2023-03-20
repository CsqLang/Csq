/*

This is the test to check whether tokenizer is working perfectly or not?

*/
#include <iostream>
#include "AST/ast.h"
#include "Parser/parser.h"

int main() {
    vector<TokenStream> tokens = {
        tokenize("for i in a:",1),
        tokenize("  print(\"hello\")",2),
        tokenize("print(\"hi\")",2),
    };
    int line_no = 1;
    for(TokenStream tokS : tokens){
        printf("Line[%d]\n",line_no);
        for(Token token : tokS){
            if(token.type == KEYWORD)
                cout << "(" << token.token << "," << "KEYWORD" << ")" << endl;
            else if(token.type == IDENTIFIER)
                cout << "(" << token.token << "," << "IDENTIFIER" << ")" << endl;
            else if(token.type == VALUE)
                cout << "(" << token.token << "," << "VALUE" << ")" << endl;
            else if(token.type == SYMBOL)
                cout << "(" << token.token << "," << "SYMBOL" << ")" << endl;
            else if(token.type == AROPERATOR)
                cout << "(" << token.token << "," << "AROPERATOR" << ")" << endl;
            else if(token.type == ASOPERATOR)
                cout << "(" << token.token << "," << "ASOPERATOR" << ")" << endl;
            else if(token.type == COPERATOR)
                cout << "(" << token.token << "," << "COPERATOR" << ")" << endl;
            else if(token.type == LOPERATOR)
                cout << "(" << token.token << "," << "LOPERATOR" << ")" << endl;
            else if(token.type == COMMENT)
                cout << "(" << token.token << "," << "COMMENT" << ")" << endl;
            else if(token.type == INDENT)
                cout << "(" << token.token << "," << "INDENT" << ")" << endl;
        }
        line_no++;
    }

    return 0;
}

/*
Output shall be : 
Line[1]
(for,KEYWORD)
(i,IDENTIFIER)
(in,KEYWORD)
(a,IDENTIFIER)
(:,SYMBOL)
Line[2]
( ,INDENT)
( ,INDENT)
(print,IDENTIFIER)
((,SYMBOL)
(),SYMBOL)
Line[3]
(print,IDENTIFIER)
((,SYMBOL)
(),SYMBOL)
*/
