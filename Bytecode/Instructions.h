#if !defined(Csq4_Instruction_H)
#define Csq4_Instruction_H
#include "../Grammar/Token_bytecode.h"
#include "../Memory/Reference_Counter.h"
#define FUNCTIONS(name,args,code) auto name args LBRACE code RBRACE SEMI
#define CALL(name, args) name args
#define REFERENCE(name,type, refr) SmartPointer<type> name = SmartPointer<type>(refr)
#define ID_REF(name) AMPER name
#define FOR for(
#define WHILE while(
#define DO ){
#define IF if(
#define ELIF else if(
#define ELSE else{
#define ENDS }
#define def auto
#define equals ==
#define is ==
#define noteq !=
#define gtequal >=
#define ltequal <=
#define modequal %=
#endif // Csq4_Instruction_H
