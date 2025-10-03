#ifndef STASISOS_STDIO_H
#define STASISOS_STDIO_H

unsigned char in_byte(unsigned short port);
void out_byte(unsigned short port, unsigned char val);

unsigned short in_word(unsigned short port);
void out_word(unsigned short port, unsigned short val);

unsigned int in_long(unsigned short port);
void out_long(unsigned short port, unsigned int val);

void io_wait(void);

#endif //STASISOS_STDIO_H