#if !defined(CodeGenCsq4)
#define CodeGenCsq4
#include <stdio.h>
#include <string.h>
//This function writes the text into the file.
auto write(const char* path,const char* data){
    FILE* file;
    file = fopen(path, "w") ;
    // Write the dataToBeWritten into the file
    fputs(data,file);
    fclose(file);
}
void writeBytecode(const char* path,const char* code);



#endif // CodeGenCsq4
