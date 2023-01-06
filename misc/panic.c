#pragma once

#include "../drivers/terminal.c"
extern void panic();
const char* kernelPanicMsg = "\n\nPDOS Kernel Panic!\nHalting CPU...\n";
void kpanic(void) {
	kprint(kernelPanicMsg);  // signal to the user that their computer just crashed
	// __asm__ volatile("cli"); // if we dont stop interrupts it might appear as if the os never halted
	// __asm__ volatile("hlt"); // halt everything but interrupts
    panic();
}