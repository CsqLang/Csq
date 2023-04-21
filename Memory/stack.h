#if !defined(Stack_H)
#define Stack_H
#include "../Grammar/grammar.h"

vector<string> Variables;
vector<string> Functions;
vector<string> Group_stack;


struct MemberVarProperty{
    string name;
    string type;
};
struct MethodProperty{
    string name;
    string type;
    vector<string> params;
};
struct ClassProp{
    string name;
    string inheritted_class;
    vector<MemberVarProperty> member_vars;
    vector<MethodProperty> methods;
};
vector<MethodProperty> methods_prop;
vector<MemberVarProperty> variables_prop;
vector<ClassProp> Classes;
//Predefining some because they are already defined and encapsulated in headerfile
vector<string> Identifiers = {"print","range","i32","i64","f64","list","int","double"};

void addIdentifier(string identifier){
    Identifiers.push_back(identifier);
}

void load_builtins(){
    //Print function
    MethodProperty print;
    print.name = "print";
    print.params = {"val"};
    print.type = "NONE";
    methods_prop.push_back(print);
    //Range function
    MethodProperty range;
    range.name = "range";
    range.type = "NONE";
    methods_prop.push_back(range);
}

#endif // Stack_H
