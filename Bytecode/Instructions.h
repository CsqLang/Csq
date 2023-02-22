#if !defined(Csq4_Instruction_H)
#define Csq4_Instruction_H
#include "../Grammar/Token_bytecode.h"
#include "../Memory/Reference_Counter.h"
#include "../Builtins/builtins.h"
#include <stdio.h>
#define FUNCTIONS(name,args,code) auto name args LBRACE code RBRACE SEMI
#define CALL(name, args) name args
#define REFERENCE(name,type, refr) ref<type> name = ref<type>(refr)
#define PARAM(name,type,refr) type name = type(refr)
#define FORREF(name,type) ref<type> name
#define ID_REF(name) AMPER name
#define from(classn) classn::
#define FOR for(
#define use using
#define WHILE while(
#define ends }
#define DO ){
#define IF if(
#define ELIF else if(
#define else else{
#define ENDS }
#define ENDCLASS };
#define def auto
#define equals ==
#define noteq !=
#define gtequal >=
#define ltequal <=
#define modequal %=
#define MAIN int main(int argc, char const *argv[]){
#define ENDMAIN ;return 0;}
#define init
#define inherits :
#define TRY try{
#define CATCH catch(
#define ASM asm
#define FINAL final

#endif // Csq4_Instruction_H
