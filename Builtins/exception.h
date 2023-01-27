#if !defined(Csq4Exp)
#define Csq4Exp
#include<stdio.h>
#include<stdlib.h>
void Trackback(){
    exit(EXIT_FAILURE);
}

void MemoryOverflowException(){
    printf("Trackback:\n an object is trying to use memory which it doesn't owns\n");
    Trackback();
}

#endif // 
