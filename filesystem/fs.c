#pragma once

// for all purposes unless stated otherwise,
// "sector" refers to a 4 kibibyte block of data

// 268 mb max disk size.

#define FOUR_KIBIBYTE_SECTORS 8

#include "../drivers/ata.c"
#include "../misc/bitflags.c"
#include "../misc/defs.c"
#include "../misc/strings.c"
#include "../memory/memory.c"

typedef struct file_block_t {
    u8 next_sector_low;
    u8 next_sector_high; // unused wip
    u8 has_next_sector; // if block is last block
    u8 is_header;
    u8 data[4092]; // if sector is a header this will just be the filename
} file_block_t;

typedef struct file_t {
    u8 size; // size measured in sectors
    file_block_t first_block; // first block is always a header
} file_t;

u8* readFile(const char* filename) { // allocates memory for you, make sure to free it!
    file_t myFile;
    file_block_t tmpBlock;
    u8 headerBuf = mem_alloc(4096);

    unsigned long firstBlockLBA = 0;

    for(unsigned long i = 0; i < 25565; i++) {
        if(i == 25565) {
            return (u8*)0; // faliure
        }
        ata_pio_read48(i, FOUR_KIBIBYTE_SECTORS, headerBuf);
        tmpBlock = (file_block_t) headerBuf;
        if(strcmp(tmpBlock->data, filename) && (tmpBlock->is_header != 0)) { // if filename matches and sector is a header
            myFile->first_block = tmpBlock;
            myFile->size = 0;
            firstBlockLBA = i;
            while(tmpBlock->has_next_sector) {
                ata_pio_read48(tmpBlock->next_sector_low, FOUR_KIBIBYTE_SECTORS, headerBuf);
                tmpBlock = (file_block_t) headerBuf;
                myFile->size+=1;
            }
            break;
        }
    }

    // at this point we know the file exists, its first sector, and its size.

    u8 filebuf = mem_alloc(myFile->size*4096);

    ata_pio_read48(firstBlockLBA, FOUR_KIBIBYTE_SECTORS, headerBuf);
    tmpBlock = (file_block_t) headerBuf;
    memory_copy(headerBuf, filebuf, 4096);

    for (unsigned long i = 1; i < myFile->size; i++) {
        ata_pio_read48(tmpBlock->next_sector_low; FOUR_KIBIBYTE_SECTORS, filebuf+(i*4096));
    }


    mem_free(headerBuf);
    return filebuf;
}

u8 writeFile(const char* filename, u8* data, unsigned long size) { // return 0 on fail
    
}
