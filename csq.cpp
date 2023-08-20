#include "AST/ast.h"
#include "AST/visitor.h"
#include "Parser/parser.h"
#include "Runtime/code_format.h"
#include "Runtime/core.h"
#include "Runtime/memory.h"
#include "Tokenizer/tokenizer.h"
#include "wrapper.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Expected 1 or more args : <name>\n");
  } else {
    string name = argv[1];

    // Path to the file:
    //  Let the input file have the the extension as with
    //  other languages (with a few exceptions)
    string path_code = name + ".csq";
    // Read the file
    string raw_code = readCode(path_code);
    // Convert to tokens
    vector<TokenStream> code = toTokens(raw_code); // Error starts
    // traverseTokenStreams(code);
    // Now parse:
    // auto parsed = Parser(code);

    string _code = Compile(code);

    // Use the CSQ_INCLUDE env variable, can't say for sure the
    // effectiveness of this
    const char *pathValue = getenv("CSQ_INCLUDE");

    if (pathValue == nullptr)
      std::cout << "CSQ_PATH environment variable not found." << std::endl;

    string final_code = addBuiltin(pathValue) + "\n" + "int main(){\n" + _code +
                        "\nfreeMemory();\n}\n";
    writeCode(final_code, name + ".cpp");
    compile(name);
  }
  return 0;
}
