#pragma once
#include "../misc/bitflags.c"
#include "../misc/defs.c"

// 1024 possible blocks allocated starting at 0x00007E00
// https://wiki.osdev.org/Memory_Map_(x86)
#define MMSIZE 128
#define BLOCKSIZE 8 // 8 bytes per block

u8 memmap[MMSIZE] = {0};

void memcpy() {

}

u8* lowMalloc(unsigned int size) { // returns pointer, if pointer is 0 then allocation failed.
    // find good spot to put the memory
    u8* returnPtr = (u8*)0;
    unsigned int i;
    size = roundUp(size, BLOCKSIZE);
    while (returnPtr == 0 || i <= MMSIZE*8) { // mmsize times 8 because each u8 can have 8 bitflags
        

        
        i++;
    }
    return (u8*)returnPtr + 0x00007e00;
}

u8 lowDealloc(void* ptr, u8 size) { // returns 0 on failure, 1 on success

}

u8 memRealloc(void* ptr, unsigned int oldSize, unsigned int newSize) { // allocates a bigger bit of memory for the same thing

}