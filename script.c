#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

int get_executable_path(char *return_path) {
    char exe_path[1024];
    int len = readlink("/proc/self/exe", exe_path, sizeof(exe_path)-1);
    if (len == -1) {
        printf("readlink() error");
        return 0;
    }
    exe_path[len] = '\0';
    strcpy(return_path, dirname(exe_path));
    return len;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("fatal error: no input files\n");
        return -1;
    }
    
    char path[1024];
    get_executable_path(path);
    
    char compile_command[1024];
    
    strcpy(compile_command, "mkdir -p ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj");
    system(compile_command);
    
    strcpy(compile_command, "gcc -o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/string.o -c src/string/string.c");
    system(compile_command);
    
    strcpy(compile_command, "gcc -o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/lexer.o -c src/interpreter/lexer.c");
    system(compile_command);
    
    strcpy(compile_command, "gcc -o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/memory.o -c src/memory/memory.c");
    system(compile_command);

    strcpy(compile_command, "gcc -o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/main.o -c src/main.c");
    system(compile_command);
    
    strcpy(compile_command, "gcc -o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/main.exe ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/string.o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/lexer.o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/memory.o ");
    strcat(compile_command, path);
    strcat(compile_command, "/build/obj/main.o");
    system(compile_command);

    size_t s=18;
    for (int i=1; i<argc; i++) s += strlen(argv[i]) + 1;
    char run_command[s];
    strcpy(run_command, "./build/main.exe");
    for (int i=1; i<argc; i++) {
        strcat(run_command, " ");
        strcat(run_command, argv[i]);
    }
    run_command[s-1] = '\0';

    system(run_command);
    
    return 0;
}