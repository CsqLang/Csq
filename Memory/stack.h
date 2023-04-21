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

#endif // Stack_H
