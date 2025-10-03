#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_NAME_LEN 32
#define PROCESS_STACK_SIZE 4096

#include "../../../include/kernel/stdlib/stdbool.h"

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} process_state;

typedef struct process {
    int pid;
    char name[PROCESS_NAME_LEN];
    process_state state;

    void (*entry_point)(void*);
    void* stack;
    unsigned int stack_size;

    struct process* next;
} process;

process* create_process(const char* name, void (*entry_point)(void*));
process* get_process(int tid);
unsigned int get_process_count();
bool add_process(process* proc);

#endif // PROCESS_H