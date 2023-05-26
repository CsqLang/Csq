#if !defined(JIT_CSQ4)
#define JIT_CSQ4
#include "core.h"
/*
We already defined that Csq4 is compiled to native machine code but
in the hood it use C++ as intermediate language and then converted into machine code.
So what is this JIT?
JIT -> Just in time compiler is a body in Csq which combines large operations into a simple operation like:

a = 2+58 
it's not directly used as 2+58 instead it is interpreter into 
60 which is easier to use for the memory.
*/

//This returns the value by doing the operations:
double eval(TokenStream tokens){
    double total;
    string last_sym = "";
    for(Token token : tokens){
        switch(token.type){
            case VALUE:{
                    if(last_sym == "+")
                        total += stod(token.token);
                    else if(last_sym == ""){
                        total += stod(token.token);
                    }
                    else if(last_sym == "-")
                        total -= stod(token.token);
                    else if(last_sym == "/")
                        if(token.token != "0")
                            total /= stod(token.token);
                        else
                            RuntimeError("couldn't divide by 0.");
                    else if(last_sym == "*")
                        total *= stod(token.token);
                    else if(last_sym == "==")
                        total = (total == stod(token.token));
                    else if(last_sym == "!=")
                        total = (total != stod(token.token));
                    else
                        RuntimeError("invalid binary operator " + last_sym + ".");
                break;
            }
            default:{
                last_sym = token.token;
            }
        }
    }
    return total;
}


#endif // JIT_CSQ4
