#if !defined(bytecodeWrite_h_Csq4)
#define bytecodeWrite_h_Csq4
#include "../libs/utils/filehand.h"
#include "../libs/utils/stringlib.h"
void BytecodeWrite(array<str> codes, str path, str name,str compilerP){
    str imports = codes[0];
    str functions = codes[1];
    str nominal = codes[2];

    str combined_code = str("#include \"")+compilerP+str("/Bytecode/Instructions.h\"\n")+imports + str("\n") + functions + "MAIN\n";
    combined_code += nominal + "ENDMAIN";
    // str combined_code;
    // //First have to check if __main__ = true or not.
    // if(split(nominal,"\n")[0] == "__main__ = true"){
    //     combined_code = str("#include \"")+compilerP+str("/Bytecode/Instructions.h\"\n")+imports + str("\n") + functions + "MAIN\n";
    //     combined_code += nominal + "ENDMAIN";
    // }
    // else{
    //     combined_code = str("#include \"")+compilerP+str("/Bytecode/Instructions.h\"\n")+imports + str("\n") + functions;
    // }
    str loc = path+"/";
    loc += name+".csqm";
    write(loc, combined_code);
}

#endif // bytecodeWrite_h_Csq4
