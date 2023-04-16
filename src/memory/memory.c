#include "memory.h"
#include <stdlib.h>

Memory *memoryCreate() {
    Memory *memory = malloc(sizeof(Memory));
    memory->stack = (StackMemory) {
        1048576,
        0,
        malloc(1048576)   // too much?
    };
    memory->heap = (HeapMemory) {
        4194304,
        0,
        malloc(4194304)   // too much?
    };
    return memory;
}

void memoryFree(Memory *memory) {
    free(memory->stack.data);
    free(memory->heap.data);
    free(memory);
}
