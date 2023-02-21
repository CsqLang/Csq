#if !defined(Csq4Exp)
#define Csq4Exp
#include<stdio.h>
#include<stdlib.h>
void Trackback(){
    exit(EXIT_FAILURE);
}

void MemoryOverflowException(){
    printf("Trackback:\n An object is trying to use memory which it doesn't owns.\n");
    Trackback();
}
void IndexError(){
    printf("Trackback:\n IndexError : An object is trying to access an memory which is out of index.\n");
    Trackback();
}
void KeyError(){
    printf("Trackback:\n KeyError : An object is trying to access key which is not present.\n");
}
void DivisonByZeroException(){
    printf("Trackback:\n Couldn't divide by zero.\n");
    Trackback();
}

void AssertionFailureException(int id_){
    printf("Trackback:\n Assertion Failure by assertion id : %d.\n",id_);
    Trackback();
}
#endif // 
