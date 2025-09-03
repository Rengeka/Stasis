//
// Created by stasi on 14.07.2025.
//

char read_scancode()
{
    return in_byte(DATA_PORT);
}

void flush_keyboard_buffer() {
    while (in_byte(STATUS_PORT) & 1) {
        in_byte(DATA_PORT);
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