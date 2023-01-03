#if !defined(Csq4_Instruction_H)
#define Csq4_Instruction_H
#include "../Grammar/Token_bytecode.h"
#include "../Memory/Reference_Counter.h"
#define FUNCTIONS(name,args,code) auto name args LBRACE code RBRACE SEMI
#define CALL(name, args) name args
#define REFERENCE(name,type, refr) SmartPointer<type> name = refr SEMI
#define ID_REF(name) AMPER name
#define FOR for(
#define WHILE while(
#define IF if(
#define ELIF else if(
#define ELSE else{
#define ends }
#define DEF auto
#define CLASS struct
#endif // Csq4_Instruction_H
