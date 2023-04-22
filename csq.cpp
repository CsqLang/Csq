#include "AST/ast.h"
#include "AST/visitor.h"
#include "Parser/parser.h"
#include "Tokenizer/tokenizer.h"
#include "IR/instructions.h"
#include "IR/vm.h"

//The transpiler for Csq4.2
int main(int argc, char const *argv[])
{
        if(argc < 4){
            printf("Expected 3 args : <lang> <name> <current dir>\n");
        }
        else{
            load_builtins();
            compile(argv[1],argv[3],argv[2]);
            if(error_count == 0){
                
                RunExecutable(string(argv[3]) + "/" + argv[2]);
            }
        }
    return 0;
}
