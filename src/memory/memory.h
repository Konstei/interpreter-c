#pragma once

typedef unsigned char byte;

typedef struct {
    unsigned int totalSize;
    unsigned int usedSize;
    byte *data;
} StackMemory, HeapMemory;

typedef struct {
    StackMemory stack;
    HeapMemory heap;
} Memory;

/**
 * @brief 
 * @return Memory* 
 */
Memory *memoryCreate();

/**
 * @brief 
 * @param memory
 */
void memoryFree(Memory *memory);