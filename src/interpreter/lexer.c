#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "../containers/vector.h"
#include "../string/string.h"

String *commentsDelete(String *code) {
    if (code->length == 0) return code;
    String *newCode = stringCreate("");
    String *temp = newCode;
    unsigned long long lineNumber = 1;
    short line = 0;
    short block = 0;
    unsigned long long op = 0;
    short inString = 0;
    char stringType = '\0';
    if (code->str[0] == '/' && code->str[1] == '/') line = 1;
    else if (code->str[0] == '/' && code->str[1] == '*') block = 1;
    else if (code->str[0] == '"' || code->str[0] == '\'') {
        stringType = code->str[0];
        inString = 1;
    }
    for (unsigned long long i = (inString ? inString : (line > block ? line : block)+1); i<code->length; i++) {
        if (!line && !block) {
            if (stringType == '\0' && (code->str[i] == '"' || code->str[i] == '\'')) {
                stringType = code->str[i];
                inString = 1;
            } else if (inString && code->str[i] == stringType && code->str[i-1] != '\\') {
                stringType = '\0';
                inString = 0;
            }
            if (inString) {
                char sChar[2] = {code->str[i-1], '\0'};
                newCode = stringAppend(newCode, sChar);
                stringFree(temp);
                temp = newCode;
                continue;
            }
        }
        if (code->str[i] == '/' && code->str[i+1] == '*' && code->str[i-1] != '/' && !line) {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            stringFree(temp);
            temp = newCode;
            block = 1;
            op = i;
            i++;
        } else if (code->str[i] == '*' && code->str[i+1] == '/' && op != i-1 && !line) {
            if (block) {
                if (code->str[i-1] == '\n') {
                    newCode = stringAppend(newCode, "\n");
                    stringFree(temp);
                    temp = newCode;
                }
                block = 0;
                i += 3;
            } else {
                printf("ERROR: at %s:%llu\nSyntaxError: Stray token, expected to find a '/*' to match the '*/' token\n", "main.k", lineNumber);
                exit(EXIT_FAILURE);
            }
        } else if (code->str[i] == '/' && code->str[i+1] == '/' && !block) {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            stringFree(temp);
            temp = newCode;
            line = 1;
            i++;
        }
        if (!block && !line || code->str[i-1] == '\n') {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            stringFree(temp);
            temp = newCode;
        }
        if (line && code->str[i] == '\n') {
            line = 0;
        }
        if (code->str[i] == '\n') lineNumber++;
    }
    if (!block && !line || code->str[code->length-1] == '\n') {
        char sChar[2] = {code->str[code->length-1], '\0'};
        newCode = stringAppend(newCode, sChar);
        stringFree(temp);
        temp = newCode;
    }
    if (block) {
        unsigned long long newLines = 0;
        for (unsigned long long i=code->length-1; i>0; i--) {
            if (code->str[i-1] == '/' && code->str[i] == '*') break;
            if (code->str[i] == '\n') newLines++;
        }
        printf("ERROR: at %s:%llu\nSyntaxError: Unterminated comment, expected to find a '*/' to match the '/*' token\n", "main.k", stringCount(newCode, "\n", 0, newCode->length) - newLines + 1);
        exit(EXIT_FAILURE);
    }
    return newCode;
}
