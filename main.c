#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string/string.h"
#include "vector/vector.h"


DEFINE_VECTOR(String);

int main(int argc, char *argv[]) {
    Vector(String) *v = vectorCreate(String, 0, (String[]){});
    vectorPush(String, v, *stringCreate("Hello"));
    vectorPush(String, v, *stringCreate("World"));
    for (unsigned int i = 0; i < v->size; i++)
        printf("%s ", v->data[i].str);
    vectorFree(String, v);
    printf("\n");
    return 0;
}