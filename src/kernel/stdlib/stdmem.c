//
// Created by stasi on 14.07.2025.
//

#include "../../../include/kernel/stdlib/stdmem.h"
#include "../../../include/kernel/stdlib/stdbool.h"

void* std_malloc(unsigned int size) {
    if (heap_used + sizeof(memory_block_header) + size > HEAP_SIZE) {
        return NULL;
    }

    memory_block_header* header = (memory_block_header*)(heap + heap_used);
    header->size = size;
    header->is_garbage = false;

    void* ptr = (void*)(heap + heap_used + sizeof(memory_block_header));
    heap_used += sizeof(memory_block_header) + size;

    return ptr;
}

void* std_free(void* ptr){
    memory_block_header* header = (memory_block_header*)((char*)ptr - sizeof(memory_block_header));

    header->is_garbage = true;
}

void* memcpy(void* dest, const void* src, unsigned int n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;

    for (unsigned int i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}