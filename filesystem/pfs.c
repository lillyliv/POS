//
// pos file system version 1 (2023)
//
#pragma once
#include "../drivers/ata.c"
#include "../misc/defs.c"
#include "../misc/bitflags.c"

// disk header
// sect 0: bootloader
// sect 1: bitmap of sectors that contain a file header (max disk size of a bit above 2 megs)
// sect 2-byte0-1: 16 bit value of drive size measured in 512 byte sectors
// sect 2-byte2: should be 0x23 to indicate a PFS formatted disk

// file header (1 sector)
// 0 - 100: filename (truncated if neccicary)
// 101: file permissions
// 102-105 (dword): file size (max filesize is slightly less than 4.3gb,
//                  files should never get this big considering memory 
//                  on a 32 bit system is limited to 4gb)
// 105-150: owner (not truncated as this may cause security issues)
// 151-154: "PFS", followed by null
// 155: version, this driver is version 1
// 156-511: 32 bit LBS values of file chunks(in order) (45k max file size)

unsigned long PFSgetFileSize(const char* filename) {

}

u8 PFSreserveFileSpace(unsigned long filesize) { // filesize max is 4gb(way more than filesystem supports as a max disk size)

    while(1) { // loop auto breaks

    }

    return 0; // 0 is error code

}


u8 PFSreadFile(const char* filename, u8* buf) { // please make sure your buffer is big enough
    for(;;) { // loop auto breaks

    }
}

u8 PFSwriteFile() {

}