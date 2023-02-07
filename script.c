#include <stdlib.h>
int main(void) {
    system("gcc -c string/string.c -o build/obj/string.o");
    system("gcc -c interpreter/lexer.c -o build/obj/lexer.o");
    system("gcc -c main.c -o build/obj/main.o");
    system("gcc build/obj/string.o build/obj/lexer.o build/obj/main.o -o build/main.exe");
    system("./build/main.exe");
    return 0;
}