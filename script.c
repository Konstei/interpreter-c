#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    system("gcc -o build/obj/string.o -c string/string.c");
    system("gcc -o build/obj/lexer.o -c interpreter/lexer.c");
    system("gcc -o build/obj/memory.o -c memory/memory.c");
    system("gcc -o build/obj/main.o -c main.c");
    system("gcc -o build/main.exe build/obj/string.o build/obj/lexer.o build/obj/memory.o build/obj/main.o");
    long int size = argc - 1 + strlen("./build/main.exe");
    for (unsigned int i=1; i<argc; i++) size += strlen(argv[i]);
    char command[size];
    strcpy(command, "./build/main.exe");
    for (unsigned int i=1; i<argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    system(command);
    return 0;
}