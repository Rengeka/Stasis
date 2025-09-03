#include "../../../include/kernel/thread/process.h"
#include "../../../include/kernel/stdlib/stdstring.h"
#include "../../../include/kernel/stdlib/stdbool.h"
#include "../../../include/kernel/stdlib/stdmem.h"

#define MAX_PROCESSES 64

static unsigned int next_id = 0;
static process* process_table[MAX_PROCESSES];
static int process_count = 0;

bool add_process(process* proc) {
    if (process_count >= MAX_PROCESSES) return false;

    process_table[process_count++] = proc;
    return true;
}

process* create_process(const char* name, void (*entry_point)(void*)) {
    process* proc = (process*)std_malloc(sizeof(process));
    if (!proc) return NULL;

    str_copy_to(proc->name, name, 0);
    proc->name[PROCESS_NAME_LEN - 1] = '\0';
    proc->pid = next_id++;
    proc->state = PROCESS_READY;
    proc->entry_point = entry_point;

    proc->stack = std_malloc(PROCESS_STACK_SIZE);
    proc->stack_size = PROCESS_STACK_SIZE;
    proc->next = NULL;

    add_process(proc);
    return proc;
}

process* get_process(int index) {
    if (index < 0 || index >= process_count) return NULL;
    return process_table[index];
}

int get_process_count() {
    return process_count;
}