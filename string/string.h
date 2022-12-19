#pragma once

typedef struct {
    unsigned int length;
    char *data;
} String;

String *stringCreate(char *data);

void stringAssign(String *string, char *data);

void stringAppend(String *string, char *data);

void stringFree(String *string);