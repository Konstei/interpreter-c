#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "string/string.h"
#include "interpreter/lexer.h"
#include "memory/memory.h"


int main(int argc, char *argv[]) {
    FILE *file;
    for (unsigned int i=1; i<argc; i++) {
        if (access(argv[i], F_OK) == -1) {
            errno = ENOENT;
            perror("");
            printf("Trying to access file: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
        file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Could not open file: '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        String *text = stringCreate("// test file to see if everything is working\nimport fs from \"fs\";\n\n/*\nclass Parent {\npublic:\n    Parent(string name, int age) {\n        this:name = name;\n        this:age = age;\n    }\n    ~Parent() = default;\n\n    static fn int get() {\n        return rand();\n    }\n\nprivate:\n    string name;\n    int age;\n}\n*/\n\nfn int sqare(int n) {\n    return n*n;\n}\n\nfn void main() {\n    // Parent p(\"John\", 23);\n    // print(\"%d\", Parent::get());\n    \n}\n\n\ntest_begin\nmo/*\nsmc//*/\nmos/*//\nmc*/\nmosmc/*//*/\ntest_end\n\na\n/**/\nb");
        String *code = commentsDelete(text);
        FILE *f = fopen("src/out.txt", "w");
        fprintf(f, "%s", code->str);
        // fseek(file, 0, SEEK_END);
        fclose(file);
    }
    return 0;
}