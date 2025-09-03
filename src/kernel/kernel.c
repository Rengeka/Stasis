//
// Created by stasi on 14.07.2025.
//

__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
        0x1BADB002,
        0x00000003,
        0xE4524FFB
};

#include "../../include/kernel/drivers/vga.h"
#include "../../include/kernel/thread/process.h"
#include "../../include/kernel/stdlib/stdmem.h"
#include "../../include/kernel/stdlib/stdstring.h"
#include "../../include/kernel/cpu/cpu.h"
#include "../../include/kernel/shell/shell.h"

#define VIDEO_MEMORY (char*)0xB8000
#define SCREEN_WIDTH 80

void kernel_main() {
    shell* sh = shell_ctor(true);
    process* proc = create_shell_process();
    proc->entry_point((void*)sh);
}