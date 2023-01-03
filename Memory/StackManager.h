#if !defined(StackManager_H_Csq4)
#define StackManager_H_Csq4
//Importing Csq Stack
#include "Stack.h"
//This class includes all operations that makes working with Csq Stack easy.
class CsqStack{
    public:
        CsqStack(){}
        void addVariable(str name){
            Stack::Variables.add(name);
        }
        void popVariable(str name){
            Stack::Variables.erase(name);
        }
        void addFunction(str name, str code){
            Stack::Function.add(name, code);
        }
        void popFunction(){
            Stack::Function.pop();
        }
        bool VariablePresent(str name){
            return in(Stack::Variables,name);
        }
        bool FunctionPresent(str name){
            return in(Stack::Function.keys,name);
        }
        bool isImport(array<str> import){
            return in(import,"import");
        }
        void addImport(array<str> tok){
            str imp;
            for(auto s : tok){
                imp+=s;
            }
            Stack::Import.add(imp);            
        }
};

#endif // StackManager_H_Csq4