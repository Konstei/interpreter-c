#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "../vector/vector.h"
#include "../string/string.h"

String *commentsDelete(String *code) {
    if (code->length == 0) return code;
    String *newCode = stringCreate("");
    unsigned long long lineNumber = 1;
    int line = 0;
    int block = 0;
    unsigned int op = 0;
    if (code->str[0] == '/' && code->str[1] == '/') line = 1;
    else if (code->str[0] == '/' && code->str[1] == '*') block = 1;
    for (unsigned int i=(line > block ? line : block)+1; i<code->length; i++) {
        if (code->str[i] == '/' && code->str[i+1] == '*' && code->str[i-1] != '/' && !line) {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            block = 1;
            op = i;
            i++;
        } else if (code->str[i] == '*' && code->str[i+1] == '/' && op != i-1 && !line) {
            if (block) {
                if (code->str[i-1] == '\n') newCode = stringAppend(newCode, "\n");
                block = 0;
                i += 3;
            } else {
                printf("ERROR: at %s:%llu\nSyntaxError: Stray token, expected to find a '/*' to match the '*/' token\n", "main.k", lineNumber);
                exit(EXIT_FAILURE);
            }
        } else if (code->str[i] == '/' && code->str[i+1] == '/' && !block) {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            line = 1;
            i++;
        }
        if (!block && !line || code->str[i-1] == '\n') {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
        }
        if (line && code->str[i] == '\n') {
            line = 0;
        }
        if (code->str[i] == '\n') lineNumber++;
    }
    if (!block && !line || code->str[code->length-1] == '\n') {
        char sChar[2] = {code->str[code->length-1], '\0'};
        newCode = stringAppend(newCode, sChar);
    }
    if (block) {
        unsigned long long newLines = 0;
        for (unsigned int i=code->length-1; i>0; i--) {
            if (code->str[i-1] == '/' && code->str[i] == '*') break;
            if (code->str[i] == '\n') newLines++;
        }
        printf("ERROR: at %s:%llu\nSyntaxError: Unterminated comment, expected to find a '*/' to match the '/*' token\n", "main.k", stringCount(newCode, "\n", 0, newCode->length) - newLines + 1);
        exit(EXIT_FAILURE);
    }
    return newCode;
}
