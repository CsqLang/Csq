#include <iostream>
#include "../AST/ast.h"
#include "Parser/parser.h"
int main() {
    auto tokens = Tokenizer("def hello():\n 2+8\n2+8\ndef df():\n 2=4\n33+3");
    ParseLines(tokens);
    cout << ParseStatements() << "\n";
}
