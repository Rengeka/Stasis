//
// Created by stasi on 14.07.2025.
//

#ifndef STASISOS_SHELL_H
#define STASISOS_SHELL_H

#include "../../../include/kernel/stdlib/stdstring.h"
#include "../../../include/kernel/stdlib/stdbool.h"
#include "../../../include/kernel/thread/process.h"

#define MAX_HISTORY_LINES 256
#define MAX_COMMAND_LENGTH 256

#define SHELL_PROCESS_NAME "shell"

typedef struct {
    char commands[MAX_HISTORY_LINES][MAX_COMMAND_LENGTH];
    int (*count)(char[][MAX_COMMAND_LENGTH], int);
    int current_index;
    int count_commands_value;
} shell_history;

typedef struct {
    shell_history* history;

    bool is_running;
    bool echo_enabled;

    char input_buffer[MAX_COMMAND_LENGTH];
    int input_length;
    int cursor_position;
    int scroll_offset;
} shell;

int count_lines(char commands[][MAX_COMMAND_LENGTH], int max_commands);
shell_history* shell_history_ctor();
shell* shell_ctor(bool echo_enabled);
process* create_shell_process();

#endif //STASISOS_SHELL_H