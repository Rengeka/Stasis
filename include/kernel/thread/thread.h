#ifndef THREAD_H
#define THREAD_H

#include "../../../include/kernel/stdlib/stdbool.h"
#include "../../../include/kernel/thread/process.h"

typedef struct thread {
    int tid;
    process[] processes; 
} thread;

thread* create_thread();
thread* get_thread(int tid);
unsigned int get_thread_count();

#endif // THREAD_H