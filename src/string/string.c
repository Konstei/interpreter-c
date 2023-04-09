#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DEFINE_VECTOR(String);

String *stringCreate(char *str) {
    String *string = (String*)malloc(sizeof(String));
    string->length = strlen(str);
    string->str = (char*)malloc(string->length + 1);
    strcpy(string->str, str);
    return string;
}

String *stringAppend(String *string, char *str) {
    unsigned long long newLength = string->length + strlen(str);
    char temp[newLength + 1];
    strcpy(temp, string->str);
    strcat(temp, str);
    String *newString = stringCreate(temp);
    return newString;
}

void stringFree(String *string) {
    free(string->str);
    free(string);
}

// this function gives weird stuff
String *stringSlice(String *string, unsigned long long start, unsigned long long end) {
    if (end - start <= 0) {
        return stringCreate("");
    }
    unsigned long long newLength = end - start;
    char temp[newLength + 1];
    strncpy(temp, string->str + start, newLength);
    temp[newLength] = '\0';
    String *newString = stringCreate(temp);
    return newString;
}

Vector(String) *stringSplit(String *string, char *separator) {
    Vector(String) *v = vectorCreate(String)(0, NULL);
    String *stringCopy = stringCreate(string->str);
    String *temp = stringCreate("");
    char *token = strtok(stringCopy->str, separator);
    while (token != NULL) {
        temp = stringCreate(token);
        vectorPush(String)(v, *temp);
        token = strtok(NULL, separator);
    }
    stringFree(temp);
    stringFree(stringCopy);
    return v;
}

String *stringJoin(Vector(String) *v, char *separator) {
    String *string = stringCreate(v->data[0].str);
    for (unsigned long long i=1; i<v->length; i++) {
        stringAppend(string, separator);
        stringAppend(string, v->data[i].str);
    }
    return string;
}

long long stringFind(String *string, char *str, unsigned long long start, unsigned long long end) {
    for (unsigned long long i=start; i<end; i++) {
        if (!strncmp(string->str+i, str, strlen(str))) return i;
    }
    return -1;
}

unsigned long long stringCount(String *string, char *str, unsigned long long start, unsigned long long end) {
    unsigned long long count = 0;
    char *token = strstr(string->str + start, str);
    while (token != NULL && token - string->str < end) {
        count++;
        token = strstr(token + 1, str);
    }
    return count;
}

String *stringTrim(String *str, int direction) {
    if (str->length == 0) return str;
    String *slice;
    *slice = *str;
    if (direction == -1) {
        while (slice->str[0] == ' ') slice = stringSlice(slice, 1, slice->length);
        return slice;
    }
    if (direction == 1) {
        while (slice->str[-1] == ' ') slice = stringSlice(slice, 0, slice->length-1);
        return slice;
    }
    printf("Invalid direction for trim function");
    exit(EXIT_FAILURE);
}

String *stringReverse(String *string) {
    char temp[string->length+1];
    for (unsigned long long i=string->length-1; i>=0; i--) {
        temp[string->length - i - 1] = string->str[i];
    }
    temp[string->length] = '\0';
    return stringCreate(temp);
}
