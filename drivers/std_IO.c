//
// Created by stasi on 07.07.2025.
//

const unsigned char DATA_PORT = 0x60;
const unsigned char STATUS_PORT = 0x64;

unsigned char in_byte(unsigned short port);
void flush_keyboard_buffer();

void IO_init() {
    flush_keyboard_buffer();
}

// Reading standard I/O system value on a port
unsigned char in_byte(unsigned short port)
{
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void out_byte(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned short in_word(unsigned short port) {
    unsigned short ret;
    __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void out_word(unsigned short port, unsigned short val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}


void flush_keyboard_buffer() {
    while (in_byte(STATUS_PORT) & 1) {
        in_byte(DATA_PORT);
    }
}

char read_scancode()
{
    return in_byte(DATA_PORT);
}

void reboot() {
    while (in_byte(0x64) & 0x02);

    out_byte(0x64, 0xFE);

    for (;;);
}