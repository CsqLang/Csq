#if !defined(FUNCTIONS_CSQ4)
#define FUNCTIONS_CSQ4
#include "../Grammar/grammar.h"
#include "../Tokenizer/tokenizer.h"
struct Function{
    string name;
    vector<string> arguments;
    string body;
    bool closed = false;
};

Function FunctionDefination(vector<Token> tokens){
    Function function;
    bool name = false;
    bool arg = false;
    bool body = false;
    int pos = 0;
    string currentArgument;
    for(Token token : tokens){
        if(token.type == KEYWORD && token.token == "def")
            name = true;
        else if(token.type == IDENTIFIER && name == true){
            name = false;
            function.name = token.token;
            arg = true;
        }
        else if(arg && token.type == SYMBOL && token.token == "(")
            ignore;
        else if(arg && token.type == IDENTIFIER && token.token != function.name){
            currentArgument += token.token;
        }
        else if(arg && token.type == SYMBOL && token.token == ","){
            function.arguments.push_back(currentArgument);
            currentArgument = "";
        }
        else if(arg && token.type == SYMBOL && token.token == ")"){
            function.arguments.push_back(currentArgument);
            currentArgument = "";
            arg = false;
            body = true;
        }
        else if(body && token.token == function.name){
            if(tokens[pos+1].type == KEYWORD && tokens[pos+1].token == "ends"){
                function.closed = true;
                break;
            }
            function.body += token.token;
        }
        pos++;
    }

    return function;
}


#endif // FUNCTIONS_CSQ4
