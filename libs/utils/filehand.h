#if !defined(filehand_utils_Csq3)
#define filehand_utils_Csq3
    #include "str.h"
    #include <unistd.h>
    auto read(str filepath, int line_num = 10000){
        FILE * fo; 
        fo = fopen(filepath.Str,"r");
        str data;
        char ln[line_num];
        /*File is opened. Start reading the file line by line.*/
        while ( fgets ( ln, line_num, fo) != NULL ){
            data += str(ln);
        }
        fclose(fo);
        return data;
    }
    //This function writes the text into the file.
    auto write(str path,str data){
        FILE* file;
        file = fopen(path.Str, "w") ;
        // Write the dataToBeWritten into the file
        fputs(data.Str,file);
        fclose(file);
    }

#endif // filehand_utils_Csq3
