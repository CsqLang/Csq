#include "AST/ast.h"
#include "Parser/parser.h"


void testMultipleFunctions(){

    string code = "def fun1():\n print('inside fun1')\ndef fun2():\n print('inside fun2')\n";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testMultipleFunctions2(){

    string code = "def fun1():\n print('inside fun1')\n if 1 == 1:\n  print('1 is 1')\n elif 2 == 3:\n  print('I think compiler has crashed')\ndef fun2():\n print('inside fun2')\n if 2==2:\n  print('2 is 2')\nprint('done')";

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


int main() {
    testMultipleFunctions2();
}
