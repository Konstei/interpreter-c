#include "string.h"
#include <string.h>
#include <stdlib.h>

String *stringCreate(char *str) {
    String *string = malloc(sizeof(String));
    string->length = strlen(str);
    string->str = malloc(string->length + 1);
    strcpy(string->str, str);
    return string;
}

String *stringAppend(String *string, char *str) {
    string->length += strlen(str);
    string->str = realloc(string->str, string->length + 1);
    strcat(string->str, str);
    return string;
}

void stringFree(String *string) {
    free(string->str);
    free(string);
}

String *stringSlice(String *string, unsigned int start, unsigned int end) {
    String *newString;
    newString->length = end - start;
    newString->str = malloc(newString->length + 1);
    for (unsigned int i=0; i<newString->length; i++) newString->str[i] = string->str[start + i];
    newString->str[newString->length] = '\0';
    return newString;
}
