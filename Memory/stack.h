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
    //i32 class
    ClassProp i32_;
    i32_.name = "i32";
    Classes.push_back(i32_);
    //str
    ClassProp str_;
    str_.name = "str";
    Classes.push_back(str_);
    MethodProperty len_;
    len_.name = "len";
    len_.type = "NONE";
    methods_prop.push_back(len_);
    //f64
    ClassProp f64_;
    f64_.name = "f64";
    Classes.push_back(f64_);
    //list
    ClassProp list_;
    list_.name = "list";
    Classes.push_back(list_);
    MethodProperty add_;
    add_.name = "add";
    add_.type = "NONE";
    methods_prop.push_back(add_);
    MethodProperty sort_;
    sort_.name = "sort";
    sort_.type = "NONE";
    methods_prop.push_back(sort_);
    MethodProperty read_;
    read_.name = "read";
    read_.type = "NONE";
    methods_prop.push_back(read_);
    //int
    ClassProp int_;
    int_.name = "int";
    Classes.push_back(int_);
    ClassProp map_;
    map_.name = "map";
    Classes.push_back(map_);
    ClassProp double_;
    double_.name = "double";
    Classes.push_back(double_);
    ClassProp heap_;
    heap_.name = "heap";
    Classes.push_back(heap_);
}

#endif // Stack_H
