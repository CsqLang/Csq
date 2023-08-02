/*
Now we have to set a wrapper which could build a communication between 
C/C++ code and the Csq Runtime because if there is no such medium
so how will our runtime be runned by C/C++
*/
#if !defined(WRAPPER_CSQ)
#define WRAPPER_CSQ4

//First we shall import all needed headerfiles to build the wrapper
#include "Runtime/memory.h"
#include "Runtime/core.h"
#include "Parser/parser.h"
#include "AST/visitor.h"

string addBuiltin(string pdir){
    return "#include \"" + pdir + "/Builtin/basic.h\"\n";
}
void RunExecutable(string path){
    string command = path;
    system((command).c_str());
}
void CompileToGPP(string path, string name,string curr){
    string command = "cd " + curr + " && g++ " + path + " -o " + name;
    system(command.c_str());
}
void compile(string currdir, string name){
    CompileToGPP(currdir + "/" + name + ".cpp",name, currdir);
}
#endif // WRAPPER_CS
