
#include "../../../include/kernel/stdlib/stdstring.h"
#include "../../../include/kernel/stdlib/stdbool.h"
#include "../../../include/kernel/shell/shell.h"
#include "../../../include/kernel/thread/process.h"
#include "../../../include/kernel/stdlib/stdmem.h"
#include "../../../include/kernel/drivers/vga.h"

#define VIDEO_MEMORY (char*)0xB8000
#define SCREEN_WIDTH 80

void render_vga(shell* sh);
void print_line(shell* sh, const char* line);
void scroll_up(shell* sh);

void shell_main(void* arg) {

    shell* sh = (shell*)arg;
    sh->is_running = true;

    clear_video();
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, WorldDDDDDDDDDD!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, WorldDDDDDDDDDD!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");
    print_line(sh, "Hello, World!");

    scroll_up(sh);
    scroll_up(sh);

    while (sh->is_running) {

    }
}

void render_vga(shell* sh) {
    clear_video();

    shell_history* history = sh->history;
    int total = history->count_commands_value;
    int lines_to_show = 24;

    int max_scroll = total > lines_to_show ? total - lines_to_show : 0;
    if (sh->scroll_offset > max_scroll) {
        sh->scroll_offset = max_scroll;
    }

    int start = max_scroll - sh->scroll_offset;

    for (int i = 0; i < lines_to_show && (start + i) < MAX_HISTORY_LINES; i++) {
        const char* line = history->commands[start + i];
        vga_print_at(0, i, line);
    }

    vga_print_at(0, 24, sh->input_buffer);
}

int count_lines(char commands[][MAX_COMMAND_LENGTH], int max_commands) {
    int count = 0;
    for (int i = 0; i < max_commands; i++) {
        if (commands[i][0] != '\0') {
            count++;
        }
    }
    return count;
}

shell_history* shell_history_ctor() {
    shell_history* history = (shell_history*)std_malloc(sizeof (shell_history));

    for (int i = 0; i < MAX_HISTORY_LINES; i++) {
        history->commands[i][0] = '\0';
    }

    history->count = count_lines;
    history->current_index = 0;
    history->count_commands_value = 0;

    return history;
}

shell* shell_ctor(bool echo_enabled) {
    shell* shell_instance = (shell*)std_malloc(sizeof(shell));

    shell_instance->history = shell_history_ctor();
    shell_instance->is_running = false;
    shell_instance->echo_enabled = echo_enabled;

    shell_instance->input_buffer[0] = '\0';
    shell_instance->input_length = 0;
    shell_instance->cursor_position = 0;
    shell_instance->scroll_offset = 0;

    return shell_instance;
}

process* create_shell_process() {
    return create_process(SHELL_PROCESS_NAME, shell_main);
}

void print_line(shell* sh, const char* line) {
    shell_history* history = sh->history;

    if (history->count_commands_value < MAX_HISTORY_LINES) {
        str_copy(history->commands[history->count_commands_value], line);
        history->count_commands_value++;
    } else {
        for (int i = 1; i < MAX_HISTORY_LINES; i++) {
            str_copy(history->commands[i - 1], history->commands[i]);
        }
        str_copy(history->commands[MAX_HISTORY_LINES - 1], line);
    }

    render_vga(sh);
}

void scroll_up(shell* sh) {
    if (sh->scroll_offset < sh->history->count_commands_value)
        sh->scroll_offset++;
    render_vga(sh);
}

void scroll_down(shell* sh) {
    if (sh->scroll_offset > 0)
        sh->scroll_offset--;
    render_vga(sh);
}