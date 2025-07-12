
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
        0x1BADB002,
        0x00000003,
        0xE4524FFB
};

#include "../include/drivers/vga.h"
#include "../include/drivers/std_IO.h"
#include "../include/shell/shell.h"

void init();
void print_welcome_message();

void kernel_main()
{
    init();
    shell_start();
}

void init()
{
    clear_video();
    print_string("Initializing standard I/O system\n");
    IO_init();

    clear_video();
    print_welcome_message();
}

void print_welcome_message(){
    print_string("========================================\n");
    print_string("                 WELCOME!               \n");
    print_string("                                       \n");
    print_string("       |\\      _,,,---,,_                \n");
    print_string(" ZZZzz /,`.-'`'    -.  ;-;;,_            \n");
    print_string("      |,4-  ) )-,_. ,\\ (  `'--'          \n");
    print_string("     '---''(_/--'  `-'\\_)               \n");
    print_string("                                       \n");
    print_string("          STASIS.OS v0.1                \n");
    print_string("        experimental kernel             \n");
    print_string("\n");
    print_string("   Type `--help` or `-t` to start.\n");
    print_string("========================================\n");
}