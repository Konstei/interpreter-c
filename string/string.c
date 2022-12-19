#include "string.h"
#include <string.h>

String *stringCreate(char *data) {
    String *string = malloc(sizeof(String));
    string->length = strlen(data);
    string->data = malloc(string->length + 1);
    strcpy(string->data, data);
    return string;
}

void stringAssign(String *string, char *data) {
    string->length = strlen(data);
    string->data = realloc(string->data, string->length + 1);
    strcpy(string->data, data);
}

void stringAppend(String *string, char *data) {
    string->length += strlen(data);
    string->data = realloc(string->data, string->length + 1);
    strcat(string->data, data);
}

void stringFree(String *string) {
    free(string->data);
    free(string);
}
