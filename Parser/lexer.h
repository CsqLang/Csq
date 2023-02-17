#if !defined(LEXER_CSQ4)
#define LEXER_CSQ4
#include "../Grammar/Csq.h"
/*
This is the class which will do lexial analysis of Csq4 code.
*/
class Lexer{
    public:
        //Some public members
        str code;
        //Constructors
        Lexer(str code){
            this->code = code;
        }
        //This function is stage one which will split everything on the basis of tokens
        array<str> SplitViaGrammar(str statement){
            for(auto t : BytecodeGrammar.keys){
                statement = replaceStr(statement.Str,t.Str,(" "+t+" ").Str);
            }
            return split(statement," \t");
        }
        //Reset function will clear all previous data inside token and code array to move on to next statement.
        void Reset(){
            code = "";
        }
        //This function will return tokens.
        array<str> GetTokens(){
            /*Work 1:
                Split the code into tokens via function SplitViaGrammar.
            */
            array<str> tokens = SplitViaGrammar(code);
            /*Work 2:
                Combine string literals.
            */
            array<str> ntok;
            bool strended = true;
            str strlat;
            for(auto t : tokens){
                if(t == "\"" && strended == true){
                    strlat = "\"";
                    strended = false;
                }
                else if(t == "\"" && strended == false){
                    if(strlat[strlat.len()-1] != '\"'){
                        strlat.pop_bk();
                        strlat += "\"";
                        ntok.add(strlat);
                        strended = true;
                    }
                    else{
                        strlat += "\"";
                        ntok.add(strlat);
                        strended = true;
                    }
                }
                else if(t != "\"" && strended == true){
                    ntok.add(t);
                }
                else if(t != "\"" && strended == false){
                    strlat +=  t + " ";
                }
            }
            return ntok;
        } 
};

/*
Motive of last edit: It was edited by Aniket Kumar on 9/feb/2023 to make Csq space sensative because in the previous lexer space was skipped
due to which it became space insensative so to make it sensative lexer was improved.
*/

#endif // LEXER_CSQ4
