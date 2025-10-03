#include "../../../include/kernel/stdlib/stdbyte.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

#define VGA_TEXT_MODE 0x03
#define VGA_VIDEO_MODE 0x13

static volatile char* const vga_buffer = (volatile char*)VGA_ADDRESS;
static volatile byte vga_mode;

// Text mode 

void set_text_mode() {
    // Not implemented yet
}

void vga_print_at(int x, int y, const char* str) {
    // TODO Check if text mode is active

    int offset = (y * VGA_WIDTH + x) * 2;

    for (int i = 0; str[i] != '\0'; i++) {
        vga_buffer[offset++] = str[i];
        vga_buffer[offset++] = 0x07;
    }
}

void clear_video() {
    // TODO Check if text mode is active

    int total_chars = VGA_WIDTH * VGA_HEIGHT;
    for (int i = 0; i < total_chars; i++) {
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = 0x07;
    }
}

// Video mode 

void set_video_mode() {
    // Not implemented yet
}

void put_pixel() {
    // Not implemented yet
    // Check if video mode is active
}