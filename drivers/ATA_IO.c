//
// Created by stasi on 12.07.2025.
//

#include "../include/drivers/std_IO.h"
#include "../include/drivers/vga.h"

#define ATA_DATA        0x1F0
#define ATA_ERROR       0x1F1
#define ATA_SECCOUNT0   0x1F2
#define ATA_LBA0        0x1F3
#define ATA_LBA1        0x1F4
#define ATA_LBA2        0x1F5
#define ATA_HDDEVSEL    0x1F6
#define ATA_COMMAND     0x1F7
#define ATA_STATUS      0x1F7


static void ata_wait() {
    while (in_byte(ATA_STATUS) & 0x80);
    while (!(in_byte(ATA_STATUS) & 0x08));
}

void ata_write_sector(short lba, const char* data) {

    out_byte(ATA_HDDEVSEL, 0xE0 | ((lba >> 24) & 0x0F));
    out_byte(ATA_SECCOUNT0, 1);
    out_byte(ATA_LBA0, lba & 0xFF);
    out_byte(ATA_LBA1, (lba >> 8) & 0xFF);
    out_byte(ATA_LBA2, 0);
    out_byte(ATA_COMMAND, 0x30);

    ata_wait();

    for (int i = 0; i < 256; i++) {
        unsigned short val = ((unsigned short)data[i * 2 + 1] << 8) | (unsigned char)data[i * 2];
        out_word(ATA_DATA, val);
    }
}

void ata_read_sector(short lba, char* data) {

    out_byte(ATA_HDDEVSEL, 0xE0 | ((lba >> 24) & 0x0F));
    out_byte(ATA_SECCOUNT0, 1);
    out_byte(ATA_LBA0, lba & 0xFF);
    out_byte(ATA_LBA1, (lba >> 8) & 0xFF);
    out_byte(ATA_LBA2, 0);
    out_byte(ATA_COMMAND, 0x20);

    ata_wait();

    for (int i = 0; i < 256; i++) {
        unsigned short val = in_word(ATA_DATA);
        data[i * 2]     = val & 0xFF;
        data[i * 2 + 1] = (val >> 8) & 0xFF;
    }
}