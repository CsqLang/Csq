#include <iostream>
#include "AST/ast.h"
#include "Parser/parser.h"


void testMultipleFunctions(){

    string code = "def fun1():\n print('inside fun1')\ndef fun2():\n print('inside fun2')\n";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    cout << ParseStatements() << "\n";
}

void testIfElseLadder(){

    string code = "if 1 == 2:\n print('Your math is wrong')\nelse:\n print('Your math is correct')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    cout << ParseStatements() << "\n";
}


int main() {
    testIfElseLadder();
}
