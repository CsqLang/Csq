#include "AST/ast.h"
#include "Parser/parser.h"


void testMultipleFunctions(){

    string code = "def fun1():\n print('inside fun1')\ndef fun2():\n print('inside fun2')\n";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testMultipleFunctions2(){

    string code = "def fun1():";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testIfElseLadder(){

    string code = "if 1 == 2:\n print('Your math is wrong')\nelse:\n print('Your math is correct')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testIfElseLadder2(){

    string code = "elif 1 == 2:\n print('Your math is wrong')\nelse:\n print('Your math is correct')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testnestedIfElseLadder(){

    string code = "if 1:\n if 2:\n  print('Hello')\n else:\n  if 2:\n   print('Hello')\n  print('do it')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

int main() {
    testIfElseLadder();
}
