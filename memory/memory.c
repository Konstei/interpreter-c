#include "memory.h"

Memory *memoryCreate() {
    Memory *memory = calloc(sizeof(Memory));
    memory->stack = (StackMemory){
        1048576,
        0,
        malloc(1048576)
    };
    memory->heap = (HeapMemory){
        4194304,
        0,
        malloc(4194304)
    };
    return memory;
}

void memoryFree(Memory *memory) {
    free(memory->stack.data);
    free(memory->heap.data);
    free(memory);
}
