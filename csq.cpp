#include "AST/ast.h"
#include "AST/visitor.h"
#include "Parser/parser.h"
#include "Runtime/code_format.h"
#include "Runtime/core.h"
#include "Runtime/memory.h"
#include "Tokenizer/tokenizer.h"
#include "wrapper.h"
#include "Runtime/code_format.h"

#include <cstdlib>
#include<iostream>


int main(int argc, char const *argv[])
{
        if(argc == 4){
            string lang = argv[1];
            string name = argv[2];
            string currdir = argv[3];

            //Path to the file:
            string path_code = currdir + "/" + name + ".csq";
            curr_path = currdir + "/";
            //Read the file
            string raw_code = readCode(path_code);
            //Convert to tokens
            vector<TokenStream> code = toTokens(raw_code); //Error starts
            // traverseTokenStreams(code);
            //Now parse:
            // auto parsed = Parser(code);

            string _code = Compile(code);
            string final_code = addBuiltin(currdir + "/") + "\n" + "int main(){\n" + _code + "\nfreeMemory();\n}\n";
            writeCode(final_code, currdir + "/" + name + ".cpp");
            compile(currdir,name);

        }
        else if (argc == 2)
        {
            string name = argv[1];
            string extension = ".csq";

            // Calculate the position of the extension in the name
            size_t pos = name.rfind(extension);

            // If the extension is found at the end of the name, remove it
            if (pos != string::npos && pos == name.length() - extension.length()) {
                name.erase(pos, extension.length());
            }
            //Path to the file:
            string path_code = name + extension;
            //Read the file
            string raw_code = readCode(path_code);
            //Convert to tokens
            vector<TokenStream> code = toTokens(raw_code); //Error starts
            // auto parsed = Parser(code);

            string _code = Compile(code);


            const char* pathValue = getenv("CSQ_PATH");

            if (pathValue != nullptr) {
                // std::cout << "CSQ_PATH environment variable value: " << pathValue << std::endl;
            } else {
                std::cout << "CSQ_PATH environment variable not found." << std::endl;
            }

            string final_code = addBuiltin(pathValue) + "\n" + "int main(){\n" + _code + "\nfreeMemory();\n}\n";
            writeCode(final_code, name + ".cpp");
            compile(name);
        }

        else{
            printf("[Compile Code Instructions] \n\n");
            printf(" Expected 3 args : <lang> <name> <current dir>\n [Example : ./csq cpp hello 'current-directory'] \n\n OR \n\n");
            printf(" Expected 1 args : <name>\n [Example : csq hello ]\n");

        }
    return 0;
}
