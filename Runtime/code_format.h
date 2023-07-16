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

vector<TokenStream> toTokens(string code) {
    vector<TokenStream> tokens;
    vector<string> statements = split(code);
    
    for (string stmt : statements) {
        try {
            TokenStream tokenStream = tokenize(stmt);
            tokens.push_back(tokenStream);
        } catch (const std::exception& e) {
            printf("Error: %s\n", e.what());
        }
    }

    // traverseTokenStreams(tokens);
    tokens.push_back(TokenStream({tokenize("ignore")}));
    return tokens;
}



void writeCode(string code, string path){
    ofstream fobj(path);
    fobj << code << "\n";
}





#endif // CF_CSQ4
