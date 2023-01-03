#if !defined(Parser_Csq4)
#define Parser_Csq4
    #if !defined(Tokenizer_Csq4)
    // #define Tokenizer_Csq4
        #include "tokenizer.h"
    #endif // Tokenizer_Csq4
    #include "bytecode.h"
    //This is the one which is responsible for parsing in Csq4's code and it's conversion to Bytecodes.
    //This is the one which is responsible for parsing in Csq4's code and it's conversion to Bytecodes.
    class Parser{
        public:
            array<str> token;
            void Parse(){
                for(auto i : token){
                    printf("%s",i.Str);
                }
            }
    };

#endif // Parser_Csq4
