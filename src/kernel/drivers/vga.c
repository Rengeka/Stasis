//
// Created by stasi on 14.07.2025.
//

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

volatile char* const vga_buffer = (volatile char*)VGA_ADDRESS;

void vga_print_at(int x, int y, const char* str) {
    int offset = (y * VGA_WIDTH + x) * 2;

    for (int i = 0; str[i] != '\0'; i++) {
        vga_buffer[offset++] = str[i];
        vga_buffer[offset++] = 0x07;
    }
}

void clear_video() {
    int total_chars = VGA_WIDTH * VGA_HEIGHT;
    for (int i = 0; i < total_chars; i++) {
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = 0x07;
    }
}