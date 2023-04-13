#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "string/string.h"
#include "interpreter/lexer.h"
#include "memory/memory.h"


int main(int argc, char *argv[]) {
    FILE *src_file;
    for (unsigned int i=1; i<argc; i++) {
        if (access(argv[i], F_OK) == -1) {
            errno = ENOENT;
            perror("");
            printf("Trying to access file: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
        src_file = fopen(argv[i], "r");
        if (src_file == NULL) {
            printf("Could not open file: '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        // String *text = stringCreate("// test file to see if everything is working\nimport fs from \"fs\";\n\n/*\nclass Parent {\npublic:\n    Parent(string name, int age) {\n        this:name = name;\n        this:age = age;\n    }\n    ~Parent() = default;\n\n    static fn int get() {\n        return rand();\n    }\n\nprivate:\n    string name;\n    int age;\n}\n*/\n\nfn int sqare(int n) {\n    return n*n;\n}\n\nfn void main() {\n    // Parent p(\"John\", 23);\n    // print(\"%d\", Parent::get());\n    \"/*\";\n}\n\n\ntest_begin\nmo/*\nsmc//*/\nmos/*//\nmc*/\nmosmc/*//*/\ntest_end\n\na\n/**/\nb");
        String *text = stringCreate("// test file to see if everything is working\nimport fs from \"fs\";\n\n/*\nclass Parent {\npublic:\n    Parent(string name, int age) {\n        this:name = name;\n        this:age = age;\n    }\n    ~Parent() = default;\n\n    static fn int get() {\n        return rand();\n    }\n\nprivate:\n    string name;\n    int age;\n}\n*/\n\nfn int sqare(int n) {\n    return n*n;\n}\n\nfn void main() {\n    // Parent p(\"John\", 23);\n    // print(\"%d\", Parent::get());\n    \"\\\"/*\\\"\";\n}\n\n\ntest_begin\nmo/*\nsmc//*/\nmos/*//\nmc*/\nmosmc/*//*/\ntest_end\n\na\n/**/\nb");
        String *code = commentsDelete(text);

        char dest_file_path[1024] = "tests/out/";
        int tmplen = strlen(argv[i]);
        for (int j=tmplen-1; j>=0; j--) {
            if (argv[i][j] == '/') {
                strcat(dest_file_path, argv[i]+j+1);
                break;
            }
        }
        dest_file_path[strlen(dest_file_path)-1] = 't';
        strcat(dest_file_path, "xt");
        FILE *dest_file = fopen(dest_file_path, "w");
        fprintf(dest_file, "%s", code->str);
        stringFree(text);
        stringFree(code);
        fclose(dest_file);
    }
    fclose(src_file);
    return 0;
}