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

/* Instead of resolving and in turn making complicated program, let cpp handle
 * it*/
#include "include/files.hpp"

int main(int argc, char const *argv[]) {
  /* Check if the program is invoked without any argument*/
  if (argc < 2) {
    fprintf(stderr, "%s: fatal error: no input files\n",
            program_invocation_name);
    exit(EXIT_FAILURE);
  }

  int i = 1;

  /* If the program is invoked with arguments do something*/
  /* Since the program doesn't accept arguments yet, we can use the args we get
   * as filename(s)*/
  /* If the language is needed, then it can be added*/
  /* This one just compiles all of the files that it finds, they should contain
   * .csq extension. It can work though*/
  while (i < argc) {
    std::string file_name = argv[i];
    /* Check if file exists before doing anything to the file */

    if (!file_exists(file_name)) {
      std::cerr << program_invocation_name << ": error: " << file_name
                << " No such file or directory\n";
      continue;
    }

    std::string abs_filepath = abs_path(file_name);
    std::string name = remove_ext(file_name);

    /* Read the code */

    std::string raw_code = readCode(abs_filepath);

    /* Convert to tokens */
    vector<TokenStream> code = toTokens(raw_code); // Error starts
    // auto parsed = Parser(code);

    std::string _code = Compile(code);

    /* Use the env variable CSQ_INCLUDE for the include files */
    char *pathValue = getenv("CSQ_INCLUDE");

    /* Check if the variable was set, if it was not set, use the pwd */
    if (pathValue == nullptr)
      pathValue = getenv("PWD");

    /* If both didn't work, stop and exit the program */
    if (pathValue == nullptr) {
      std::cerr << program_invocation_name << " something went wrong\n";
      exit(EXIT_FAILURE);
    }

    string final_code = addBuiltin(pathValue) + "\n" + "int main(){\n" + _code +
                        "\nfreeMemory();\n}\n";
    writeCode(final_code, name + ".cpp");
    compile(name);
    i++;
  }

  return 0;
}
