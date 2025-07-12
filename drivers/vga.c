//
// Created by stasi on 07.07.2025.
//

#include "../include/drivers/vga.h"

#define VGA_TEXT_MODE_ADDR 0xB8000

volatile char* const video_ptr = (volatile char*)VGA_TEXT_MODE_ADDR;
volatile char* last_char = (volatile char*)VGA_TEXT_MODE_ADDR;

void new_line();

void clear_video() {
    volatile char* video = video_ptr;

    for (int i = 0; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }

    last_char = (volatile char*)VGA_TEXT_MODE_ADDR;
}

void print_char(char c)
{
    if (c == '\n') {
        new_line();
        return;
    }

    if (c == '\b') {
        if (last_char > video_ptr) {
            last_char -= 2;
            last_char[0] = ' ';
            last_char[1] = 0x07;
        }
        return;
    }

    last_char[0] = c;
    last_char[1] = 0x07;
    last_char += 2;
}

void print_string(char* string) {
    int i = 0;

    while (string[i] != '\0') {
        print_char(string[i]);
        i++;
    }
}

void scroll_up() {
    for (int row = 1; row < 25; row++) {
        for (int col = 0; col < 80; col++) {
            int src = (row * 80 + col) * 2;
            int dst = ((row - 1) * 80 + col) * 2;
            video_ptr[dst] = video_ptr[src];
            video_ptr[dst + 1] = video_ptr[src + 1];
        }
    }

    for (int col = 0; col < 80; col++) {
        int offset = ((24 * 80) + col) * 2;
        video_ptr[offset] = ' ';
        video_ptr[offset + 1] = 0x07;
    }

    last_char = video_ptr + 24 * 160;
}

void scroll_down() {
    for (int row = 23; row >= 0; row--) {
        for (int col = 0; col < 80; col++) {
            int src = (row * 80 + col) * 2;
            int dst = ((row + 1) * 80 + col) * 2;
            video_ptr[dst] = video_ptr[src];
            video_ptr[dst + 1] = video_ptr[src + 1];
        }
    }

    for (int col = 0; col < 80; col++) {
        int offset = col * 2;
        video_ptr[offset] = ' ';
        video_ptr[offset + 1] = 0x07;
    }

    last_char = video_ptr;
}

void new_line() {
    unsigned int offset = last_char - video_ptr;
    unsigned int row = offset / 160;

    if (row >= 24) {
        scroll_up();
    } else {
        row++;
        last_char = video_ptr + row * 160;
    }
}


/*
 * TODO add more complex rendering
 *
void render_screen() {
    volatile char* vmem = (volatile char*)0xB8000;

    for (int row = 0; row < SCREEN_HEIGHT; row++) {
        int history_index = scroll_offset + row;
        for (int col = 0; col < SCREEN_WIDTH; col++) {
            char ch = screen_history[history_index][col];
            vmem[(row * SCREEN_WIDTH + col) * 2] = ch ? ch : ' ';
            vmem[(row * SCREEN_WIDTH + col) * 2 + 1] = 0x07;
        }
    }
}
*/
