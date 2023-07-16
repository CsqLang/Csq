#include "AST/ast.h"
#include "AST/visitor.h"
#include "Parser/parser.h"
#include "Tokenizer/tokenizer.h"
#include "Runtime/memory.h"
#include "Runtime/core.h"
#include "wrapper.h"
#include "Runtime/code_format.h"



int main(int argc, char const *argv[])
{
        if(argc < 4){
            printf("Expected 3 args : <lang> <name> <current dir>\n");
        }
        else{
            string lang = argv[1];
            string name = argv[2];
            string currdir = argv[3];

            //Path to the file:
            string path_code = currdir + "/" + name + ".csq";
            //Read the file
            string raw_code = readCode(path_code);
            //Convert to tokens
            vector<TokenStream> code = toTokens(raw_code); //Error starts
            // traverseTokenStreams(code);
            //Now parse:
            // auto parsed = Parser(code);
            
            string _code = Compile(code);
            string final_code = addBuiltin(currdir + "/") + "\n" + "int main(){\n" + _code + "\n}\n";
            writeCode(final_code, currdir + "/" + name + ".cpp");
            compile(currdir,name);
        }
    return 0;
}
