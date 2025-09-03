//
// Created by stasi on 14.07.2025.
//

#ifndef STASISOS_ATAIO_H
#define STASISOS_ATAIO_H

static void ata_wait();
void ata_write_sector(short lba, const char* data);
void ata_read_sector(short lba, char* data);

#endif //STASISOS_ATAIO_H