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

void stringAssign(String *string, char *str) {
    string->length = strlen(str);
    string->str = realloc(string->str, string->length + 1);
    strcpy(string->str, str);
}

void stringAppend(String *string, char *str) {
    string->length += strlen(str);
    string->str = realloc(string->str, string->length + 1);
    strcat(string->str, str);
}

void stringFree(String *string) {
    free(string->str);
    free(string);
}
