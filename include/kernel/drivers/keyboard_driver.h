//
// Created by stasi on 14.07.2025.
//

#ifndef STASISOS_KEYBOARD_DRIVER_H
#define STASISOS_KEYBOARD_DRIVER_H

#include "../../cpu/ports.h"
#include "../../stdlib/stdtypes.h"

#define DATA_PORT 0x60
#define STATUS_PORT 0x64

#define KEY_ARROW_UP    1
#define KEY_ARROW_DOWN  2

extern char kbd_US[128];
extern char last_scancode;

char read_scancode();
void flush_keyboard_buffer();
char read_key();

#endif //STASISOS_KEYBOARD_DRIVER_H