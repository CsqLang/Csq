/***                FEATURES SHALL BE THERE IN CSQ4
 * REFERENCE COUNTING (DONE)
 * OBJECT ORIENTED PROGRAMMING (DONE)
 * FUNCTIONAL PROGRAMMING (DONE)
 * GENERATION OF EXECUTABLE BUT WILL BE RUNNED AT RUNTIME (DONE, AND WILL BE DONE BY CODE GENERATOR)
 * IMPORTS (DONE)
 * **/
#if !defined(PARSER_CSQ4_H)
#define PARSER_CSQ4_H
#include "lexer.h"
//Some Utilities
bool CheckIF(array<str> tokens){
    return in(tokens,"if");
}
bool isIdentifier(str tok){
    return Regex(identifier,tok);
}
bool CheckElse(array<str> tokens){
    return in(tokens,"else");
}
bool CheckElif(array<str> tokens){
    return in(tokens,"elif");
}
bool CheckFor(array<str> tokens){
    return in(tokens,"for");
}
bool CheckWhile(array<str> tokens){
    return in(tokens,"while");
}
bool CheckFunctionDefination(array<str> tokens){
    return in(tokens,"def");
}
bool CheckClassDefination(array<str> tokens){
    return in(tokens,"class");
}
bool CheckEnd(array<str> tokens){
    return in(tokens,"ends");
}
bool CheckImport(array<str> tokens){
    return in(tokens,"import");
}
bool file_exists(str filename){
    FILE *fp = fopen(filename.Str, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}


array<str> ImportsManagement(array<str> tok){
    /*Sample input: import m1.m2 m3
    Tokens: ['m1','.','m2']
    */
    array<str> imp;
    str s;
    bool dir = false;
    for(auto i : tok){
        if(i == "import"){}
        else{
            str name_module = split(i,"/")[split(i,"/").len()-1];
            imp.add(
                str("class ")+name_module+str("mod LBRACE\npublic:\n")+read(i+".csqm")+str("\nENDCLASS\n")+
                name_module + str("mod ")+name_module+";\n"
            );
        }
    }
    return imp;
}
array<str> IfTokManagement(array<str> tok){
    array<str> s;
    if(CheckIF(tok) == 1){
        for(auto i : tok)
            if(i == "if")
                s.add("IF");
            else
                s.add(i);
        s.add("DO");
    }
    else{
        s = tok;
    }
    return s;
}
array<str> ElifTokManagement(array<str> tok){
    array<str> s;
    if(CheckIF(tok) == 1){
        for(auto i : tok)
            if(i == "elif")
                s.add("ELIF");
            else
                s.add(i);
        s.add("DO");
    }
    else{
        s = tok;
    }
    return s;
}
array<str> ElseTokManagement(array<str> tok){
    array<str> s;
    if(CheckIF(tok) == 1){
        for(auto i : tok)
            if(i == "else")
                s.add("ELSE");
            else
                s.add(i);
    }
    else{
        s = tok;
    }
    return s;
}
// array<str> EndTokManagement(array<str> tok){
//     array<str> s;
//     if(CheckEnd(tok) == 1)
//         for(auto i : tok)
//             if(i == "ends")
//                 s.add("ENDS");
//             else
//                 s.add(i);
//     else
//         s = tok;
//     return s;
// }
str Rep(str s){
    str code;
    code = replaceStr(s.Str,"= =","==");
    code = replaceStr(code.Str,"+ +","++");
    code = replaceStr(code.Str,"- -","--");
    code = replaceStr(code.Str,"+ =","+=");
    code = replaceStr(code.Str,"- =","-=");
    code = replaceStr(code.Str,"* =","*=");
    code = replaceStr(code.Str,"/ =","/=");
    code = replaceStr(code.Str,"! =","!=");
    code = replaceStr(code.Str,"> =",">=");
    code = replaceStr(code.Str,"< =","<=");
    code = replaceStr(code.Str,"& &","&&");
    return code;
}
bool CheckVariableAssignment(array<str> tokens){
    bool colon, equal;
    for(auto op : tokens){
        if(op == ":"){
            colon = true;
        }
        else if(op == "="){
            equal = true;
        }
    }
    bool state = false;
    if(colon == true && equal == true){
        state = true;
    }
    return state;
}
#define ignore NULL;
//Variable call implementation
auto CheckVariableCall(array<str> instructions){
    array<str> newop;
    for(auto op : instructions){
        if(Regex(identifier,op) == true && in(Stack::Variables,op) == true && in(ReservedTokens.keys,op) == false){
            newop.add(str("* ")+op);
        }
        else{
            newop.add(op);
        }
    }
    return newop;
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
        if(varname == true && tokens[i] != ":"){
            name += tokens[i];
        }
        else if(tokens[i] == ":"){
            valpos = false;
            typepos = true;
            varname = false;
        }
        else if(tokens[i] == "="){
            valpos = true;
            typepos = false;
            varname = false;
        }
        else if(typepos == true && valpos == false){
            type += tokens[i]+" ";
        }
        else if(valpos == true && tokens[i] !=";"){
            assign += tokens[i]+" ";
        }
    }
    return array<str>({name,type,assign});
}
//Variable call implementation
auto VariableCall(array<str> instructions){
    array<str> newop;
    for(auto op : instructions){
        if(Regex(identifier,op) == true && in(Stack::Variables,op) == true && in(ReservedTokens.keys,op) == false){
            newop.add(str("*")+op);
        }
        else{
            newop.add(op);
        }
    }
    return newop;
}
auto SemiColanManagement(array<str> tok){
    array<str> newt;
    if(in(tok,"ends") == false && in(tok,"for") == false && in(tok,"def") == false && in(tok,"class") == false
    && in(tok,"if") == false && in(tok,"else") == false && in(tok,"elif") == false && in(tok,"import") == false){
        newt = tok;
        newt.add("SEMI");
    }
    else{
        newt = tok;
    }
    return newt;
}
//Variable assignment shuffle function will produce 3 new tokens of name,type and assignment.
auto TokenVariableInAssignShuffle(array<str> tokens){
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
    for(int i=1;i<tokens.len();i++){
        if(varname == true && tokens[i] != ":"){
            name += tokens[i];
        }
        else if(tokens[i] == ":"){
            valpos = false;
            typepos = true;
            varname = false;
        }
        else if(tokens[i] == "in"){
            valpos = true;
            typepos = false;
            varname = false;
        }
        else if(typepos == true && valpos == false){
            type += tokens[i]+" ";
        }
        else if(valpos == true && tokens[i] !=";"){
            assign += tokens[i]+" ";
        }
    }
    return array<str>({name,type,assign});
}
str addSemi(str s){
    array<str> lines = split(s,"\n");
    str r;
    for(auto l : lines){
        if(find_str(l.Str,str("def").Str) == 1 || find_str(l.Str,str("ends").Str)==1){
            r += l + "\n";
        }
        else{
            r += l + ";\n";
        }
    }return r;
}
array<str> ForTokManagement(array<str> tok){
    // array<str> t;
    array<str> code;
    if(CheckFor(tok) == true){
        str n = TokenVariableInAssignShuffle(tok)[0];
        str t = TokenVariableInAssignShuffle(tok)[1];
        str a = TokenVariableInAssignShuffle(tok)[2];
        code = {"FOR FORREF(",n+",",t+") IN",a+" DO"};
    }
    else{
        code = tok;
    }
    return code;
}
array<str> WhileTokManagement(array<str> tok){
    array<str> code;
    if(CheckWhile(tok) == 1){
        for(auto i : tok){
            if(i == "while"){
                code += "WHILE";
            }
            else{
                code += i;
            }
        }code += "DO";
    }else{
        code = tok;
    }
    return code;
}
/*This is the class which is basiclly the implementation of parser for Csq4.
How it will work:
input: tokens
output: Csq4 bytecodes instead of AST.
*/
class Parser{
    public:
        //Declaration of Parse function.
        auto Parse(array<array<str>> tokens);
};
//Defination of Parse function in Parser class
/*This function needs all tokens present in the code.*/
auto Parser::Parse(array<array<str>> tokens){
    //Declare states and some needed variables.
    str nominal_code, fn_code, imports, fn_name;
    bool fn_state = false;bool class_state = false;
    //Applying for range loop to get tokenized tokens present in each line.
    for(array<str> rawline : tokens){
        array<str> line = (WhileTokManagement(ForTokManagement(ElseTokManagement(ElifTokManagement(IfTokManagement(rawline))))));
        // printf("\n%s\n",tostr(line).Str);
        //Evalute when Variable assignment is there and it's not inside functions body.
        if(CheckVariableAssignment(line) == true and fn_state == false && CheckFunctionDefination(line) == false){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            bytecode += type + ",";bytecode += val + ")\n";
            //Adding the bytecode to the code string.
            nominal_code += bytecode;
            //Add the variable to stack.
            Stack::Variables.add(name);
        }
        else if(CheckImport(line) == true){
            for(auto i : ImportsManagement(line)){
                imports+=i+"\n";
            }
        }
        else if(CheckClassDefination(line) == true){
            nominal_code += tostr(line) + " LBRACE\n";
            class_state = true;
        }
        //Evalute when Variable assignment is there in the body of a function.
        else if(CheckVariableAssignment(line) == true and fn_state == true && CheckFunctionDefination(line) == false && class_state == false){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            bytecode += type + ",";bytecode += val + ")\n";
            //Adding the bytecode to the code string.
            fn_code += bytecode;
            //Add the variable to stack.
            Stack::Variables.add(name);
        }
        //Evalute when Variable assignment is there in the body of a function.
        else if(CheckVariableAssignment(line) == true and fn_state == true && CheckFunctionDefination(line) == false && class_state == true){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            bytecode += type + ",";bytecode += val + ")\n";
            //Adding the bytecode to the code string.
            nominal_code += bytecode;
            //Add the variable to stack.
            Stack::Variables.add(name);
        }
        //When function defination found so:
        else if(CheckFunctionDefination(line) == true and fn_state == false && class_state == false){
            //Some needed informations about function::
            str fnname,args,bytecode_arg;bool argstate = false;
            //Extracting name of the function and the arguments.
            for(int i = 0;i<line.len();i++){
                if(line[i] == "(")
                    argstate = true;
                // else if(line[i] == "def " && i==0){}
                else if(argstate == false && i>0)
                    fnname+=line[i]+" ";
                else if(argstate == true)
                    args += line[i];
            }args.pop_bk();
            fn_name = replaceStr(fnname.Str," ","");
            //Rechanging the state because the function is defined and it's body hasn't ended.
            fn_state = true;
            //Transform the function's arguments in bytecode representation.
            if(args == ""){bytecode_arg = "";}
            else{
                //Stage one split the arguments via ','
                auto splitted = split(args,",");
                //Apply for range loop over splitted arguments.
                for(auto i : splitted){
                    str n = TokenVariableAssignShuffle(Lexer(i).GetTokens())[0];
                    str t = TokenVariableAssignShuffle(Lexer(i).GetTokens())[1];
                    str e = TokenVariableAssignShuffle(Lexer(i).GetTokens())[2];
                    bytecode_arg += str("REFERENCE(") + n + str(",")+t+str(",")+e+"),";
                    Stack::Variables.add(n);
                }bytecode_arg.pop_bk();
            }
            fn_code += str("def ")+fn_name+str("(")+bytecode_arg+str(") LBRACE\n");
        }
        //When function defination found so:
        else if(CheckFunctionDefination(line) == true && class_state == true){
            //Some needed informations about function::
            str fnname,args,bytecode_arg;bool argstate = false;
            //Extracting name of the function and the arguments.
            for(int i = 0;i<line.len();i++){
                if(line[i] == "(")
                    argstate = true;
                // else if(line[i] == "def " && i==0){}
                else if(argstate == false && i>0)
                    fnname+=line[i]+" ";
                else if(argstate == true)
                    args += line[i];
            }args.pop_bk();
            fn_name = replaceStr(fnname.Str," ","");
            //Rechanging the state because the function is defined and it's body hasn't ended.
            fn_state = true;
            //Transform the function's arguments in bytecode representation.
            if(args == ""){bytecode_arg = "";}
            else{
                //Stage one split the arguments via ','
                auto splitted = split(args,",");
                //Apply for range loop over splitted arguments.
                for(auto i : splitted){
                    str n = TokenVariableAssignShuffle(Lexer(i).GetTokens())[0];
                    str t = TokenVariableAssignShuffle(Lexer(i).GetTokens())[1];
                    str e = TokenVariableAssignShuffle(Lexer(i).GetTokens())[2];
                    bytecode_arg += str("REFERENCE(") + n + str(",")+t+str(",")+e+"),";
                    Stack::Variables.add(n);
                }bytecode_arg.pop_bk();
            }
            nominal_code += str("def ")+fn_name+str("(")+bytecode_arg+str(") LBRACE\n");
        }
        else if(fn_state == true && tostr(line) != (fn_name + " ends") && class_state == false){
            fn_code += tostr(line)+"\n";
            // printf("TRIG : 1\n");
        }
        
        else if(fn_state == true && tostr(line) !=( fn_name + " ends" )&& class_state == true){
            nominal_code += tostr(line)+"\n";
            // nominal_code += "ENDS\n";
        }
        else if(tostr(line) == (fn_name + " ends") && (fn_state == true) && (class_state==false)){
            fn_code += "ENDS\n";
            fn_state = false;
        }
        else if(tostr(line) == (fn_name + " ends") && (fn_state == true) && (class_state==true)){
            nominal_code += "ENDS\n";
            fn_state = false;
        }
        else if(tostr(line) == "endc"){nominal_code += "ENDCLASS\n";}
        //If none of the above condition matched with tokens.
        else if(fn_state == false){
            nominal_code += tostr(line) + "\n";
        }
    }
    return array<str>({imports,addSemi(Rep(fn_code)),addSemi(Rep(nominal_code))});
}
#endif // PARSER_CSQ4_H
