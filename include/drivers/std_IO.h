//
// Created by stasi on 07.07.2025.
//

#ifndef OS_STD_IO_H
#define OS_STD_IO_H

extern const unsigned char DATA_PORT;
extern const unsigned char STATUS_PORT;

char in_byte(unsigned short port);
void out_byte(unsigned short port, unsigned char val);

unsigned short in_word(unsigned short port);
void out_word(unsigned short port, unsigned short val);


void IO_init();
char read_scancode();
void reboot();

#endif //OS_STD_IO_H