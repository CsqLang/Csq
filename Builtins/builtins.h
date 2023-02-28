/*:::::::::::::::::::::::::::::::FEATURES SHALL BE THERE IN CSQ4:::::::::::::::::::::::::::::::::::::
 (1) REFERENCE COUNTING (DONE)
 (2) OBJECT ORIENTED PROGRAMMING (DONE)
 (3) FUNCTIONAL PROGRAMMING (DONE)
 (4) GENERATION OF EXECUTABLE BUT WILL BE RUNNED AT RUNTIME (PENDING, AND WILL BE DONE BY CODE GENERATOR)
 (5) IMPORTS (DONE)

    Source : @anchor https://www.github.com/CsqLang/Csq4
    Last modified by Aniket Kumar
 * **/
#if !defined(PARSER_CSQ4_H)
#define PARSER_CSQ4_H
#include "lexer.h"
#include "../libs/utils/filehand.h"
#include "../Memory/Stack.h"
//::::::::::::::::::::::::::::::::Some Utilities::::::::::::::::::::::::::::::::
//Exception counter::
int exception_counter = 0;
/*
Errors to be pushed when user has done any mistake.
*/
void ClassEndError(str class_name){
    printf("Error: class %s has not been ended to end use endc\n",class_name.Str);
}

void FunctionEndError(str fn_name){
    printf("Error: function/method %s has not been ended to end use %s ends\n",fn_name.Str,fn_name.Str);
}

void WrongFunctionEndError(str fn_name,int lineno){
    printf("Error: In statement at line %d function scope is done for function '%s' but it doesn't exists or already ended. \n",lineno,fn_name.Str);
}

void VariableValueError(str var_name, int lineno){
    printf("Error: In statement at line %d variable declaration is done for variable '%s' but value is not given \n",lineno,var_name.Str);
}

void VariableTypeError(str var_name, int lineno){
    printf("Error: In statement at line %d variable declaration is done for variable '%s' but type is not given \n",lineno,var_name.Str);
}

void RedefinationVariableError(str var_name, int lineno){
    printf("Error: In statement at line %d variable %s is redeclared.\n",lineno,var_name.Str);
}

void MissingError(str statement_, int lineno){
    printf("Error: At line %d expected a statement after %s.\n",lineno,statement_.Str);
}

void CustomError(str statement,int lineno){
    printf("Error: At line %d%s.\n",lineno,statement.Str);
}

void StopCompilation(){
    exit(0);
}


//Checking that curly brackets is correctly closed or not
void CurlyBracketCheck(array<str> tokens, int linenum){
    int lbrace = 0;
    int rbrace = 0;
    bool ended = false;
    str token_prev = tokens[0];
    for(auto token : tokens){
        if(token == "{"){
            lbrace++;
        }
        else if(token == "}" && rbrace!=lbrace){
            rbrace++;
        }
        else if(token == "}" && rbrace == lbrace){
            CustomError(str(", invalid close of curly bracket"),linenum);
            exception_counter++;
        }
    }
    if(rbrace == lbrace)
        ended = true;
    else
        ended = false;
    if(ended == false){
        CustomError(str(", statement hasn't ended properly expected ")+to_str(lbrace-rbrace)+" }",linenum);
        exception_counter++;
    }
}
//Checking that square brackets is correctly closed or not
void SquareBracketCheck(array<str> tokens, int linenum){
    int lbrac = 0;
    int rbrac = 0;
    bool ended = false;
    str token_prev = tokens[0];
    for(auto token : tokens){
        if(token == "["){
            lbrac++;
        }
        else if(token == "]" && rbrac!=lbrac){
            rbrac++;
        }
        else if(token == "]" && rbrac == lbrac){
            CustomError(str(", invalid close of square bracket"),linenum);
            exception_counter++;        
        }
    }
    if(rbrac == lbrac)
        ended = true;
    else
        ended = false;
    if(ended == false){
        CustomError(str(", statement hasn't ended properly expected ")+to_str(lbrac-rbrac)+" ]",linenum);
        exception_counter++;
    }
}
//Checking that parenthesis is correctly closed or not
void ParenthesisCheck(array<str> tokens, int linenum){
    int lparen = 0;
    int rparen = 0;
    bool ended = false;
    str token_prev = tokens[0];
    for(auto token : tokens){
        if(token == "("){
            lparen++;
        }
        else if(token == ")" && rparen!=lparen){
            rparen++;
        }
        else if(token == ")" && rparen == lparen){
            CustomError(str(", invalid close of parenthesis"),linenum);
            exception_counter++;
        }
    }
    if(rparen == lparen)
        ended = true;
    else
        ended = false;
    if(ended == false){
        CustomError(str(", statement hasn't ended properly expected ")+to_str(lparen-rparen)+" )",linenum);
        exception_counter++;
    }
}

/*
    To know that the folowing tokens are matching with any statement or not.
*/
bool CheckIF(array<str> tokens){
    return in(tokens,IF);
}
bool isIdentifier(str tok){
    return Regex(identifier,tok);
}
bool CheckElse(array<str> tokens){
    return in(tokens,ELSE);
}
bool CheckUse(array<str> tokens){
    return in(tokens,"use");
}
bool CheckTry(array<str> tokens){
    return in(tokens,"try");
}
bool CheckCatch(array<str> tokens){
    return in(tokens,"catch");
}
bool CheckAll(array<str> tokens){
    return in(tokens,"all");
}
bool CheckElif(array<str> tokens){
    return in(tokens,ELIF);
}
bool CheckFor(array<str> tokens){
    return in(tokens,FOR);
}
bool CheckWhile(array<str> tokens){
    return in(tokens,WHILE);
}
bool CheckFunctionDefination(array<str> tokens){
    return in(tokens,DEF);
}
bool CheckClassDefination(array<str> tokens){
    return in(tokens,CLASS);
}
bool CheckEnd(array<str> tokens){
    return in(tokens,ENDS);
}
bool CheckImport(array<str> tokens){
    return in(tokens,IMPORT);
}
bool CheckConstructor(array<str> tokens){
    return in(tokens,INIT);
}
bool CheckMacro(array<str> tokens){
    return in(tokens,MACRO);
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


str currDir;
array<str> ImportsManagement(array<str> tok, str base_path = "./") {
    /*
    Syntax: import <module>
    Sample tokens : {"import","test"}
    */
    str path = tok[1];
    array<str> tokens;
    if(path[0] == '/'){
        str name = split(path,"/")[split(path,"/").len()-1];
        str content = read(path+".csqm");
        str code = "namespace ";
        code += name + " LBRACE\n";
        code += content + "\n RBRACE";
        tokens.add(code);
    }
    else{
        path = base_path + path;
        str content = read(currDir+str("/")+path+".csqm");
        str name = split(path,"/")[split(path,"/").len()-1];
        str code = "namespace ";
        code += name + " LBRACE\n";
        code += content + "\n RBRACE";
        tokens.add(code);
    }
    
    return tokens;
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

array<str> MacroManagement(array<str> tok){
    array<str> newtokens;
    if(CheckMacro(tok)){
        for(auto e : tok)
            if(e == MACRO)
                newtokens.add("#define");
            else
                newtokens.add(e);
    }
    else
        newtokens = tok;
    return newtokens;
}
str Rep(str s){
    str code;
    code = replaceStr(s.Str," = = ","==");
    code = replaceStr(code.Str,"!s"," ");
    code = replaceStr(code.Str,"+ +","++");
    code = replaceStr(code.Str,"- -","--");
    code = replaceStr(code.Str,"+ =","+=");
    code = replaceStr(code.Str,"- =","-=");
    code = replaceStr(code.Str,"* =","*=");
    code = replaceStr(code.Str,"/ =","/=");
    code = replaceStr(code.Str,"! =","!=");
    code = replaceStr(code.Str,"> =",">=");
    code = replaceStr(code.Str,"< =","<=");
    code = replaceStr(code.Str,"- >","->");
    code = replaceStr(code.Str,"& &","&&");
    code = replaceStr(code.Str," . ",".");
    code = replaceStr(code.Str,": :","::");
    code = replaceStr(code.Str," ,",",");
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
    
    return array<str>({name,replaceStr(type.Str,",","COMMA"),assign});
}
// //Implementation of constructor
// auto Constructor(array<str> tok){

// }
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
    return array<str>({name,replaceStr(type.Str,",","COMMA"),assign});
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
        code = {"FOR FORREF(",n+",",t+") IN",a," DO"};
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
    str nominal_code, fn_code, imports, fn_name,class_name;
    bool fn_state = false;bool class_state = false;str main_state = "true";
    int line_no = 1;
    
    //Applying for range loop to get tokenized tokens present in each line.
    for(array<str> rawline : tokens){
        array<str> line = (WhileTokManagement(ForTokManagement(ElseTokManagement(ElifTokManagement(IfTokManagement(rawline))))));
        //Evaluting some error checks before conditions to prevent futher processing.
        ParenthesisCheck(line,line_no);
        CurlyBracketCheck(line,line_no);
        SquareBracketCheck(line,line_no);
        //Evalute when Variable assignment is there and it's not inside functions body.
        if(CheckVariableAssignment(line) == true and fn_state == false && CheckFunctionDefination(line) == false){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            if(in(Stack::Variables,name)){
                RedefinationVariableError(name,line_no);
                exception_counter++;
            };
            //Whether type is not defined
            if(type == ""){
                VariableTypeError(name,line_no);
                exception_counter++;
            }
            //Whether values are not NULL
            if(val == ""){
                VariableValueError(name,line_no);
                exception_counter++;
            }

            bytecode += type + ",";bytecode += type + str("(") + val + "))\n";
            //Adding the bytecode to the code string.
            nominal_code += bytecode;
            //Add the variable to stack.
            Stack::Variables.add(name);
        }
        else if(CheckMacro(line) == 1 && CheckFunctionDefination(line) == 0){
            auto tokens_ = MacroManagement(line);
            for(auto t : tokens_){
                nominal_code += t + " ";
            }nominal_code += "\n";
        }
        else if(tostr(line) == "main = false"){
            main_state = "false";
        }
        else if(CheckImport(line) == true){
            for(auto i : ImportsManagement(line)){
                imports+=i+"\n";
            }
        }
        else if(CheckClassDefination(line) == true){
            nominal_code += tostr(line) + " LBRACE\n";
            class_state = true;
            class_name = line[1];
        }
        else if(CheckUse(line) == true || CheckAll(line) == true){
            imports+=Rep(tostr(line))+";\n";
        }
        else if(CheckTry(line)){
            if(line.len()==1){
                MissingError("try",line_no);
            }
            else{
                for(auto token : line)
                    if(token == "try")
                        nominal_code += "TRY ";
                    else
                        nominal_code += token + " ";
                nominal_code += "\n";
            }
        }
        else if(CheckCatch(line)){
            if(line.len()==1){
                MissingError("catch",line_no);
            }
            else{
                for(auto token : line)
                    if(token == "catch")
                        nominal_code += "CATCH ";
                    else
                        nominal_code += token + " ";
                nominal_code += "\n";
            }
        }
        else if(class_state == true && CheckConstructor(line) == true){
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
                    //Whether type is not defined
                    if(t == ""){
                        VariableTypeError(n,line_no);
                        exception_counter++;
                    }
                    bytecode_arg += str("REFERENCE(") + n + str(",")+t+str(",")+e+"),";
                    // Stack::Variables.add(n);
                }bytecode_arg.pop_bk();
                
            }
            nominal_code += str("init ")+fn_name+str("(")+bytecode_arg+str(") LBRACE\n");
        }
        //Evalute when Variable assignment is there in the body of a function.
        else if(CheckVariableAssignment(line) == true and fn_state == true && CheckFunctionDefination(line) == false && class_state == false){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Whether type is not defined
            if(type == ""){
                VariableTypeError(name,line_no);
                exception_counter++;
            }
            //Whether values are not NULL
            if(val == ""){
                VariableValueError(name,line_no);
                exception_counter++;
            }
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            bytecode += type + ",";bytecode += type + str("(") + val + "))\n";
            //Adding the bytecode to the code string.
            fn_code += bytecode;
            //Add the variable to stack.
            // Stack::Variables.add(name);
        }
        //Evalute when Variable assignment is there in the body of a function.
        else if(CheckVariableAssignment(line) == true and fn_state == true && CheckFunctionDefination(line) == false && class_state == true){
            str name = TokenVariableAssignShuffle(line)[0];
            str type = TokenVariableAssignShuffle(line)[1];
            str val = TokenVariableAssignShuffle(line)[2];
            //Whether type is not defined
            if(type == ""){
                VariableTypeError(name,line_no);
                exception_counter++;
            }
            //Whether values are not NULL
            if(val == ""){
                VariableValueError(name,line_no);
                exception_counter++;
            }
            //Producing bytecodes.
            str bytecode = "REFERENCE(";bytecode += name + ",";
            bytecode += type + ",";bytecode += type + str("(") + val + "))\n";
            //Adding the bytecode to the code string.
            nominal_code += bytecode;
            //Add the variable to stack.
            // Stack::Variables.add(name);
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
                    if(in(Stack::Variables,n)){
                        RedefinationVariableError(n,line_no);
                        exception_counter++;
                    };
                    //Whether type is not defined
                    if(t == ""){
                        VariableTypeError(n,line_no);
                        exception_counter++;
                    }
                    bytecode_arg += str("PARAM(") + n + str(",")+t+str(",")+e+"),";
                    // Stack::Variables.add(n);
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
                    //Whether type is not defined
                    if(t == ""){
                        VariableTypeError(n,line_no);
                        exception_counter++;
                    }
                    bytecode_arg += str("PARAM(") + n + str(",")+t+str(",")+e+"),";
                    // Stack::Variables.add(n);
                }bytecode_arg.pop_bk();
            }
            nominal_code += str("def ")+fn_name+str("(")+bytecode_arg+str(") LBRACE\n");
        }
        else if(fn_state == true && tostr(line) != (fn_name + " ends") && class_state == false){
            fn_code += tostr(line)+"\n";
        }
        
        else if(fn_state == true && tostr(line) !=( fn_name + " ends" )&& class_state == true){
            nominal_code += tostr(line)+"\n";
            // nominal_code += "ENDS\n";
        }
        else if(tostr(line) == (fn_name + " ends") && (fn_state == true) && (class_state==false)){
            fn_code += "ENDS\n";
            fn_state = false;
            fn_name = "";
        }
        else if(tostr(line) == (fn_name + " ends") && (fn_state == true) && (class_state==true)){
            nominal_code += "ENDS\n";
            fn_state = false;
        }
        else if(tostr(line) == "endc"){nominal_code += "ENDCLASS\n";class_state = false;}
        //If none of the above condition matched with tokens.
        else if(fn_state == false){
            nominal_code += tostr(line) + "\n";
        }
        line_no++;
    }

    //Why checking these exceptions at the end
    /*
    becuase to check that any scope is ended or not.
    */
    if (class_state == true){
        ClassEndError(class_name);
        exception_counter++;
    }
    else if(fn_state == true){
        FunctionEndError(fn_name);
        exception_counter++;
    }

    //If encountered any error so stop the exection.
    if(exception_counter > 0){
        printf("Could not compile due to %d previous errors.\n",exception_counter);
        StopCompilation();
    }
    return array<str>({imports,addSemi(Rep(fn_code)),addSemi(Rep(nominal_code)),main_state});
}
#endif // PARSER_CSQ4_H
