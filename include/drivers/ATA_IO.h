//
// Created by stasi on 12.07.2025.
//

#ifndef OS_ATA_IO_H
#define OS_ATA_IO_H

void ata_write_sector(short lba, const char* data);
void ata_read_sector(short lba, char* data);

#endif //OS_ATA_IO_H
