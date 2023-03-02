#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "../vector/vector.h"
#include "../string/string.h"

String *commentsDelete(String *code) {
    printf("%lld\n", stringCount(code, "\n", 0 ,code->length));
    if (code->length == 0) return code;
    String *newCode = stringCreate("");
    int line = 0;
    int block = 0;
    int newLine = 0;
    if (code->str[0] == '/' && code->str[1] == '/') line = 1;
    else if (code->str[0] == '/' && code->str[1] == '*') block = 1;
    for (unsigned int i=(line > block ? line : block)+1; i<code->length; i++) {
        if (code->str[i] == '/' && code->str[i+1] == '*' && code->str[i-1] != '/' && !line) {
            char sChar[2] = {code->str[i-1], '\0'};
            newCode = stringAppend(newCode, sChar);
            block = 1;
            i++;
        } else if (code->str[i] == '*' && code->str[i+1] == '/' && !line) {
            if (block) {
                block = 0;
                i += 3;
            } else {
                printf("SyntaxError: Unbalanced comments, expected to find a '/*' to match the '*/' token\n");
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
    }
    if (!block && !line || code->str[code->length-1] == '\n') {
        char sChar[2] = {code->str[code->length-1], '\0'};
        newCode = stringAppend(newCode, sChar);
    }
    return newCode;
}
