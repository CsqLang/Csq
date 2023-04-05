#include "../AST/ast.h"
#include "parser.h"


void testFunction(){

    string code = "def fun1():\n print('inside fun1')";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    printf("%s\n",ParseStatements().c_str());
}
void testIfElseInFunction(){

    string code = "def fun1():\n if 3 > 2:\n  print('3 > 2')\n elif 1:\n  print('else')\n elif 1:\n  print('else')";
    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    ParseStatements();
    printf("%s\n",Functions[0].c_str());
}


void testIfElseLadder(){

    string code = "if 1 == 2:\n print('Your math is wrong')\nelif 1>2:\n print('1>2')\nelse:\n print('Your math is correct')";

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

void StatementsLeak(){
    string code = "def fun1():\n if 3 > 2:\n  print('3 > 2')\n elif 1:\n  print('else')\n elif 1:\n  print('else')";
    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    for(Statement st : Statements){
        printf("(%s indent : %d type : %d line : %d)\n",st.statement.c_str(),st.indent_level,st.type,st.number);
    }
}

void testExprsInFunction(){
    string code = "def fun1():\n print('inside fun1')\n a = 50\n b = 49\n c = a + b\n return c";

    auto tokens = Tokenizer(code);
    ParseLines(tokens);
    ParseStatements();
    printf("%s\n",Functions[0].c_str());
}
void clear(){
    system("clear");
}
