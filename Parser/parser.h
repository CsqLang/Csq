#if !defined(Parser_Csq4)
#define Parser_Csq4
    #if !defined(Tokenizer_Csq4)
    // #define Tokenizer_Csq4
        #include "tokenizer.h"
    #endif // Tokenizer_Csq4
    #include "bytecode.h"
    //This is the one which is responsible for parsing in Csq4's code and it's conversion to Bytecodes.
    struct Parser{
        str code;
        array<str> lines;
        Parser(str code){
            lines = split(code,"\n");
        }
    };

#endif // Parser_Csq4
