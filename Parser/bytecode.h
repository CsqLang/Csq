#if !defined(PARSER_BYTECODE)
#define PARSER_BYTECODE
#include "../libs/utils/stringlib.h"

//This struct represents the bytecodes.
struct Bytecode{
    public:
        array<str> code;
        void Bytecode::addline(array<str> line){
            for(str w : line)
                code.add(w," ");
            code.add("\n");
        }
        //This function will just combine all instructions in the code array into a string.
        str Bytecode::combineAll(){
            str code;
            for(str op : this->code)
                code += op;
            return code;
        }
};
#endif // PARSER_BYTECODE