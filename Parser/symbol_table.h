/*
The implementation of symbol table for Csq classes , variables and functions
*/
#if !defined(SYMBOL_TABLE_CSQ)
#define SYMBOL_TABLE_CSQ

#include "../AST/ast.h"
#include <map>

//Parent directory:
string Pcurrent_dir;

typedef vector<Token> TokenStream;
typedef vector<Token> StringStream;
//Abstract type for all variables
struct Variable{
    string name;
    string type;
};
//Abstract type for all functions
struct Function{
    string name;
    string type;
    vector<Variable> params;
};

//Abstract type for all classes defined some predefined are int, float and str
struct Class{
    string name;
    string inherit_class;
    vector<Variable> variables;
    vector<Function> methods;
};


//Symbol table type
enum SymbolType{
    ST_FUNCTION,
    ST_VARIABLE,
    ST_CLASS,
};

//Symbol table
struct SymbolTable{
    map<string,Variable> variables;
    map<string,Class> classes;
    map<string,Function> functions;

    //Helper functions
    void addVariable(string name, Variable var){
        variables[name]=var;
    }
    void addFunction(string name, Function fun){
        functions[name]=fun;
    }
    void addVariable(string name, Class c){
        classes[name] = c;
    }

    bool isIdentifierDefined(string name){
        bool state = 0;
        for(pair<string,Variable> var : variables){
            if(var.first == name){
                state = 1;
            }
        }
        for(pair<string,Function> fun : functions){
            if(fun.first == name){
                state = 1;
            }
        }
        for(pair<string,Class> c : classes){
            if(c.first == name){
                state = 1;
            }
        }
        return state;
    }
    bool isClassDefined(string name){
        bool state = 0;
        for(pair<string,Class> c : classes){
            if(c.first == name){
                state = 1;
            }
        }
        return state;
    }
};SymbolTable table;



void load_builtins(){
    Function print;
    print.name = "print";
    print.type = "void";
    table.addFunction(print.name, print);
}

#endif // SYMBOL_TABLE_CSQ
