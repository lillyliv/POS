
// for all purposes unless stated otherwise,
// "sector" refers to a 4 kibibyte block of data

#include "../drivers/ata.c"
#include "../misc/bitflags.c"
#include "../misc/defs.c"

//
// disk header
// sect 0: regular boot sector
// sect 1: 
//     0-1: disk size in sectors
//     2-5: ascii string "POS", followed by a null
//     6-4095: reserved
// sect 2: bitmap of used sectors
// sect 3: bitmap of sectors with a file header

// file header sector layout:
// 0-1: file size in sectors
// 2-102: file name
// 103: file perm bitflags (0: exe, 1: read only, 2:write only, 3-7: reserved)
// 104-4095: 32 bit unsigned integer list of sectors in order with data from this file (15 mb max file size currently)

u8 buf[4096] = {0};

u8 getFileSize(const char* filename) { // returns file size in sectors, 0 on error
    u8 sectorsInp = 0;
    for(unsigned long i = 104; i < 4095; i++) {
        for(int j = 0; j < 8; j++) {
            if (HasFlag(buf[i], 1<<j)) sectorsInp++;
        }
    }
}

u8 readFile(const char* filename, u8** buffer) { // 0 on error

}

u8 writeFile(const char* filename, u8** buffer) { // 0 on error

}
