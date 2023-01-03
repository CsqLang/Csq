#if !defined(UTIlS_stringLib_h)
#define UTIlS_stringLib_h
#include "str.h"
#include "array.h"
//This function will tokenize the string using strtok a built-in function in C.
auto split(str ln,str tok_ = ","){
    array<str> s;
    // ln+=", ";
    char * token = strtok(ln.Str, tok_.Str);
    while(token != NULL){
        s.add(str(token));
        token = strtok(NULL, tok_.Str);
    }
    return s;
}
// This function will fnd the occurence of substr in the main string.
int find_str(char *string, char *substring){
    int i, j, l1, l2;
    int count = 0;
    l1 = strlen(string);
    l2 = strlen(substring);
    for (i = 0; i < l1 - l2 + 1; i++){
        if (strstr(string + i, substring) == string + i){
            count++;
            i = i + l2 - 1;
        }
    }
    return count;
}
//This function will return the value which is assigned.
auto get_assign(str string) {
    str temp;
    int temp_index = 0;
    for(int i=0;i<string.len();i++){
        if(string[i] == '='){
            temp_index = i+1;
            break;
        }
    }
    for(int i=temp_index;i<string.len();i++){
        temp.push_bk(char(string[i]));
    }
    return temp;
}
#include <regex.h>
bool Regex(str pattern, str target){
    // Compile the regular expression
    regex_t regex;
    int rc = regcomp(&regex, pattern.Str, 0);
    if (rc != 0) {
        char error_message[100];
        regerror(rc, &regex, error_message, 100);
        printf("Error compiling regular expression: %s\n", error_message);
        return 1;
    }

    // Match the regular expression against a string
    const char* str_ = target.Str;
    int match = regexec(&regex, str_, 0, NULL, 0);
    bool state;
    if (match == 0) {
        // printf("Match found!\n");
        state = true;
    } else {
        // printf("Match not found.\n");
        state = false;
    }

    // Free the memory used by the compiled regular expression
    regfree(&regex);
    return state;
}
#endif // UTIlS_stringLib_h