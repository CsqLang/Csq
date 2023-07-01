/*
This headerfile contains every thing which is required to read source and generate output.
*/
#if !defined(CF_CSQ4)
#define CF_CSQ4

#include "core.h"
#include <fstream>

string readCode(string path){
    ifstream fout;
    string code,line;
    fout.open(path);
    while(getline (fout, line)){
        if(line == "")
            continue;
        // else if(line[0] == '#') continue;
        else
            code += line + "\n";
    }
    return code;
}

vector<string> split(const string& str)
{
    std::vector<std::string> tokens;
 
    stringstream ss(str);
    string token;
    while (getline(ss, token, '\n')) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<TokenStream> toTokens(string code){
    vector<TokenStream> tokens;
    for(string stmt : split(code)){
        tokens.push_back(tokenize (stmt));
    }
    return tokens;
}

void writeCode(string code, string path){
    ofstream fobj(path);
    fobj << code << "\n";
}





#endif // CF_CSQ4