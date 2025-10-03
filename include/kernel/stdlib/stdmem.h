#ifndef STASISOS_STDMEM_H
#define STASISOS_STDMEM_H

#include "stdbool.h"

#define HEAP_START 0x20000
#define HEAP_SIZE  0x30000

#define NULL ((void*)0)

typedef struct {
    unsigned int size;
    bool is_garbage;
} memory_block_header;

static char* heap = (char*)HEAP_START;
static unsigned int heap_used = 0;

void* std_malloc(unsigned int size);
void* std_free(void* ptr);
void* memcpy(void* dest, const void* src, unsigned int n);

#endif //STASISOS_STDMEM_H