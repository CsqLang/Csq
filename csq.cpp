#include "CodeGen/writeBytecodes.h"
#include "CodeGen/compile.h"
#include "Parser/parser.h"
#include "Parser/lexer.h"


int main(int argc, char const *argv[])
{
    if(argc != 4){
        printf("Expected 3 parameters : <name> <current-directory> <Csq-directory>\n");
    }
    else{
        //Expected parameters : name,current_directory, Csq path
        ///////////////////////////////////////////////////////////////////
        // Reading code:
        str name = argv[1];
        str currentpath = argv[2];
        currDir = currentpath;
        str compiler_path = argv[3];
        str code = read(currentpath+str("/")+name+".csq");
        ///////////////////////////////////////////////////////////////////
        //Getting tokens
        array<array<str>> tokens;
        array<str> lines = split(code,"\n");
        
        for(auto c : lines){
            Lexer lx(c);
            tokens.add(lx.GetTokens());
        }
        //Parsing the code
        Parser parser;
        auto parsed = parser.Parse(tokens);
        //Generating bytecodes
        BytecodeWrite(parsed,currentpath,name,argv[3]);
        //Compiling the bytecodes
        compile_IR(currentpath,currentpath+str("/")+name+".csqm",name);
        //Running the executable
        system((str(currentpath+"/")+name).Str);
    }

    return 0;
}

