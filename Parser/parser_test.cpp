#include "AST/ast.h"
#include "Parser/parser.h"


void testFunction(){

    string code = "def fun1():\n print('inside fun1')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}
void testIfElseInFunction(){

    string code = "def fun1():\n if 3 > 2:\n  print('3 > 2')\n  else:\n  print('corrupted')";

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

void testForloop(){

    string code = "for i in ls:\n print(i)";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}

void testWhileloop(){

    string code = "i = 0\nwhile 1==i:\n print(i)\n i=i+1";

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
    testWhileloop();
}
