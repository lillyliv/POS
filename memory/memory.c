#pragma once
#include "../misc/bitflags.c"
#include "../misc/defs.c"

// 1024 possible blocks allocated starting at 0x00007E00
// https://wiki.osdev.org/Memory_Map_(x86)
#define MMSIZE 128
#define BLOCKSIZE 8 // 8 bytes per block

u8 memmap[MMSIZE] = {0}; // bitflag for each block of memory in physical order

void memcpy() {

}

void* lowMalloc(unsigned long size) { // returns pointer, if pointer is 0 then allocation failed.
    // // find good spot to put the memory
    // void* returnPtr = (void*)0;
    // unsigned int i;
    // size = roundUp(size, BLOCKSIZE);
    // u8 foundGoodConsecutiveBlock = 0;
    // while (returnPtr == 0 || i <= MMSIZE*8) { // mmsize times 8 because each u8 can have 8 bitflags
        
    //     for(unsigned int i = 0; i < size/8) {

    //     }

    //     if (!foundGoodConsecutiveBlock) return (void*)0;
        
    //     i++;
    // }
    // return (void*)returnPtr + 0x00007e00;
}

u8 lowDealloc(void* ptr, unsigned long size) { // returns 0 on failure, 1 on success

}

u8 memRealloc(void* ptr, unsigned long oldSize, unsigned long newSize) { // allocates a bigger or smaller bit of memory for the same thing

}