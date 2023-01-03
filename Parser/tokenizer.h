#define Tokenizer_Csq4
#include "../Grammar/Csq.h"
#include "../Memory/Stack.h"
//This function will split the operands on the basis of operators.
auto SplitOperators(str statement){
    for(auto t : Grammar.keys){
        statement = replaceStr(statement.Str,t.Str,(str(" ")+t+" ").Str);
    }
    return split(statement," ");
}
//This function generates token(bytecode tokens).
auto TokenGenerator(array<str> line){
    array<str> newline;
    array<str> meta_tok;
    for(auto e : line){
        if(in(Grammar.keys,e) == true){newline.add(Grammar[e]);}
        else{newline.add(e);}
    }
    return newline;
}
//Variable assignment shuffle function will produce 3 new tokens of name,type and assignment.
auto TokenVariableAssignShuffle(array<str> tokens){
    str type,name,assign;
    bool varname = true;
    bool typepos;
    bool valpos;
    //Example:
    /*
        a:int = 387
        ["a","COLON","int","EQUAL","387"]
    */
    //Getting positions of all main identities...
    for(int i=0;i<tokens.len();i++){
        if(varname == true && tokens[i] != "COLON"){
            name += tokens[i];
        }
        else if(tokens[i] == "COLON"){
            valpos = false;
            typepos = true;
            varname = false;
        }
        else if(tokens[i] == "EQUAL"){
            valpos = true;
            typepos = false;
            varname = false;
        }
        else if(typepos == true && valpos == false){
            type += tokens[i]+" ";
        }
        else if(valpos == true){
            assign += tokens[i]+" ";
        }
    }
    return array<str>({name,type,assign});
}