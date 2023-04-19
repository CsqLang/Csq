#if !defined(TypeChecker_H)
#define TypeChecker_H

#include "../AST/ast.h"
#include "../AST/visitor.h"
#include "parser.h"
#include "../Memory/stack.h"


/*
a:i32 = 384
b:f64 = a //Error
*/

struct MemberTCInfo{
    string name;
    string type;
};

vector<MemberTCInfo> CollectTypes(string type){
    vector<MemberTCInfo> types;
    ClassProp target_type;
    for(ClassProp class_ : Classes){
        if(class_.name == type){
            target_type = class_;
            break;
        }
    }
    for(MemberVarProperty prop : target_type.member_vars){
        MemberTCInfo i;
        i.name = prop.name;
        i.type = prop.type;
        types.push_back(i);
    }
    for(MethodProperty prop : target_type.methods){
        MemberTCInfo i;
        i.name = prop.name;
        i.type = prop.type;
        types.push_back(i);
    }
    return types;
}
MemberTCInfo SearchIdentifierGetInfo(string identifier){
    MemberTCInfo prop;
    bool found = 0;
    for(MemberVarProperty p : variables_prop){
        if(p.name == identifier){
            prop.name = p.name;
            prop.type = p.type;
            found = 1;
            break;
        }
    }
    if(!found){
        for(MethodProperty p : methods_prop){
            if(p.name == identifier){
                prop.name = p.name;
                prop.type = p.type;
                found = 1;
                break;
            }
        }
    }
    return prop;
}

bool inTypeTable(vector<MemberTCInfo> typeTable, string type){
    bool s = 0;
    for(MemberTCInfo t : typeTable){
        if(t.type == type){
            s = 1;
            break;
        }
    }
    return s;
}

void TypeChecker(string op1, string op2, string op1type, string op2type)
{
    //Now it's also possible that a class is allowing different types to be stored so we have to factor them.
    vector<string> op1_type_list,op2_type_list;

}

#endif // TypeChecker_H
