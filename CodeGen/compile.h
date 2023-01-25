#if !defined(compile_csq4)
#define compile_csq4
#include "writeBytecodes.h"
//This function will compile IR code via g++ __
void compile_IR(str current_path, str path, str name){
    str code = read(path);
    write((current_path+name+".cpp").Str,code);
    str command = "cd ";
    command += current_path;
    command += " && g++ ";
    command += current_path+name+".cpp -o ";
    command += name;
    system(command.Str);
    // system((str("rm ")+current_path+name+".cpp").Str);
}

#endif // compile_csq4
