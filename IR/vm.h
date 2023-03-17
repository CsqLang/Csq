#if !defined(CSQ_VM_4)
#define CSQ_VM_4
#include "../Parser/parser.h"
#include "../AST/ast.h"

enum TARGET_LANGUAGE{
    C,
    CPP
};

enum TARGET_COMPILER{
    CLANG,
    GCC,
    CLANGPP,
    GPP,
};

void CompileToGPP(string path, string name){
    string command = "g++ " + path + " -o " + name;
    system(command.c_str());
}

void CompileToClangPP(string path, string name){
    string command = "clang++ " + path + " -o " + name;
    system(command.c_str());
}

void CompileToGCC(string path, string name){
    string command = "gcc " + path + " -o " + name;
    system(command.c_str());
}

void CompileToClang(string path, string name){
    string command = "gcc " + path + " -o " + name;
    system(command.c_str());
}

void RunExecutable(string path){
    string command = path;
    system(command.c_str());
}


#endif // CSQ_VM_4
