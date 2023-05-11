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
    map<int,map<string,Variable>> variables;
    map<int,map<string,Class>> classes;
    map<int,map<string,Function>> functions;

    //Helper functions
    void addVariable(int parent, int current_scope, Variable variable){
        variables[(1000*parent) + current_scope][variable.name] = variable;
    }
    void addFunction(int parent, int current_scope, Function function){
        functions[(1000*parent) + current_scope][function.name] = function;
    }
    void addClass(int parent, int current_scope, Class class_){
        classes[(1000*parent) + current_scope][class_.name] = class_;
    }
    //Checking certain symbol in the symbol table
    /*
    Now the main problem appears, when there are two different scopes with same indent level
    so there will be a conflict between their members so to solve it we could do encoding :
    scope1 : function fn level = 1
    symbol table key : 1001
    scope2 : function fn2 level = 1
    symbol table key : 2001

    def fn():  //Encoding : 1001
     ...        
    def fn2(): //Encoding : 2001
     if 1: //Encoding 2002
      a = 94

    */
    bool isPresent(int current_scope, string symbol, SymbolType type){
        if(type == ST_VARIABLE)
        {
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Variable> var : variables[i]){
                    if(var.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            if(!state){
                for(pair<string, Variable> var: variables[1000]){
                    if(var.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
        else if(type == ST_FUNCTION)
        {
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Function> fun : functions[i]){
                    if(fun.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            if(!state){
                for(pair<string, Function> fun : functions[1000]){
                    if(fun.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
        else{
            bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Class> c : classes[i]){
                    if(c.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            if(!state){
                for(pair<string, Class> c : classes[1000]){
                    if(c.first == symbol){
                        state = 1;
                        break;
                    }
                }
            }
            return state;
        }
    }
    Variable getVariable(string name, int current_index){
        return variables[current_index][name];
    }
    Class getClass(string name, int current_index){
        return classes[current_index][name];
    }
    bool isClassPresent(string name, int current_scope){
        bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Class> c : classes[i]){
                    if(c.first == name){
                        state = 1;
                        break;
                    }
                }
            }
        return state;
    }
    bool isVariablePresent(string name, int current_scope){
        bool state = 0;
            for(int i = int(current_scope/1000);i<=current_scope;i++){
                for(pair<string, Variable> var : variables[i]){
                    if(var.first == name){
                        state = 1;
                        break;
                    }
                }
            }
        return state;
    }
};SymbolTable table;

bool isIdentifierDefined(string identifier, int current_scope){
    bool state = false;

    if(table.isPresent(current_scope, identifier,ST_VARIABLE)){
        state = true;
    }
    else if(table.isPresent(current_scope, identifier,ST_FUNCTION)){
        state = true;
    }
    else if(table.isPresent(current_scope, identifier,ST_CLASS)){
        state = true;
    }
    return state;
}
bool MemberPresent(string var_name,string member, int indent_level, int parent){
    bool state = 0;
    Class class_ = table.getClass(table.getVariable(var_name, (parent*1000)+indent_level).type,(parent*1000)+indent_level);
    for(Function fn : class_.methods){
        if(fn.name == member){
            state = 1;
        }
    }
    for(Variable var : class_.variables){
        if(var.name == member){
            state = 1;
        }
    }
    return state;
}
bool MemberPresentOf(string type,string member, int indent_level, int parent){
    bool state = 0;
    Class class_ = table.getClass(type, (parent*1000)+indent_level);
    for(Function fn : class_.methods){
        if(fn.name == member){
            state = 1;
        }
    }
    for(Variable var : class_.variables){
        if(var.name == member){
            state = 1;
        }
    }
    return state;
}

//This function will load builtins since they are defined in C headerfile not in direct Csq module.
void load_builtins_to_table(){
    Function print;
    print.name = "print";
    print.type = "void";
    table.addFunction(1,0,print);
}

#endif // SYMBOL_TABLE_CSQ
