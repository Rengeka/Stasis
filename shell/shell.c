//
// Created by stasi on 07.07.2025.
//

#include "../include/drivers/std_IO.h"
#include "../include/drivers/vga.h"
#include "../include/lib/stdbool.h"
#include "../include/lib/stdstring.h"
#include "../include/drivers/ATA_IO.h"

#define KEY_ARROW_UP    0x80
#define KEY_ARROW_DOWN  0x81

int last_scancode = -1;
char kbd_US [128];

char read_key();
char* read_line(char* buffer, int max_len);
void apply_command(char* command);

void shell_start()
{
    while (1){
        char buffer [100];
        char* input = read_line(buffer,100);

        apply_command(input);
    }
}

char* read_line(char* buffer, int max_len)
{
    print_string(" >>> ");

    int idx = 0;
    while (1) {
        char c = read_key();
        if (c == 0x00) continue;

        // Add scrolling
        if (c == KEY_ARROW_UP) {
            scroll_up();
            continue;
        }

        if (c == KEY_ARROW_DOWN) {
            scroll_down();
            continue;
        }

        if (c == '\n' || c == 0x1C)
        {
            buffer[idx] = '\0';
            print_char('\n');
            return buffer;
        }
        else if (c == '\b' || c == 0x0E)
        {
            if (idx > 0)
            {
                idx--;

                print_char('\b');
                print_char(' ');
                print_char('\b');
            }
        }
        else {
            if (idx < max_len - 1)
            {
                buffer[idx++] = c;
                print_char(c);
            }
        }
    }
}

void apply_command(char* command)
{
    char tokens[10][100];
    int argc = split_string(command, tokens, 10);
    if (argc == 0) return;

    if (str_compare(tokens[0], "--help") || str_compare(tokens[0], "-h"))
    {
        print_string("     --help -h       -> print help notation\n");
        print_string("     --clear -clr    -> clear screen\n");
        print_string("     --reboot        -> reboot computer\n");
        print_string("     --version -v    -> show current OS version\n");
        print_string("     --write -w      -> write to sector\n");
        print_string("     --read  -r      -> read from sector\n");
    }
    else if (str_compare(tokens[0], "--reboot"))
    {
        print_string("Rebooting...\n");
        reboot();
    }
    else if (str_compare(command, "--clear") || str_compare(command, "-clr"))
    {
        clear_video();
    }
    else if (str_compare(tokens[0], "--version") || str_compare(tokens[0], "-v"))
    {
        print_string("      v.0.0.1 -> demo\n");
    }
    else if (str_compare(tokens[0], "--write") || str_compare(tokens[0], "-w"))  {
        if (argc < 3) {
            print_string("Usage: --write <sector> <text>\n");
            return;
        }

        short sector = (short)int_parse(tokens[1]);
        char data[512] = {0};
        str_copy(data, tokens[2]);

        ata_write_sector(sector, data);
        print_string("Wrote sector\n");
    }
    else if (str_compare(tokens[0], "--read") || str_compare(tokens[0], "-r"))  {
        if (argc < 2) {
            print_string("Usage: --read <sector>\n");
            return;
        }

        short sector = (short)int_parse(tokens[1]);
        char data[512];

        ata_read_sector(sector, data);
        print_string(data);
        print_string("\n");
    }
    else
    {
        print_string("  Unknown command\n");
        print_string("  type --help or -h to see all commands\n");
    }
}

char read_key()
{
    while (1)
    {
        unsigned char scancode = read_scancode();

        if (scancode == last_scancode) continue;

        if (scancode & 0x80) {
            last_scancode = -1;
            continue;
        }

        last_scancode = scancode;

        if (scancode == 0x48) return KEY_ARROW_UP;
        if (scancode == 0x50) return KEY_ARROW_DOWN;

        char ascii = kbd_US[scancode];
        if (ascii != 0x00) return ascii;
    }
}

char kbd_US [128] =
        {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
                '\t', /* <-- Tab */
                'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
                0, /* <-- control key */
                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
                '*',
                0,  /* Alt */
                ' ',  /* Space bar */
                0,  /* Caps lock */
                0,  /* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,  /* < ... F10 */
                0,  /* 69 - Num lock*/
                0,  /* Scroll Lock */
                0,  /* Home key */
                0,  /* Up Arrow */
                0,  /* Page Up */
                '-',
                0,  /* Left Arrow */
                0,
                0,  /* Right Arrow */
                '+',
                0,  /* 79 - End key*/
                0,  /* Down Arrow */
                0,  /* Page Down */
                0,  /* Insert Key */
                0,  /* Delete Key */
                0,   0,   0,
                0,  /* F11 Key */
                0,  /* F12 Key */
                0,  /* All other keys are undefined */
        };