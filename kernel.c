
// free software no license лилли 2023
// 2 megabytes memory required
// may work with slightly above 1 megabyte however
// bootloader not included for efficiency,
// however very easy to write your own in a day or two

#include "drivers/idt.c"
#include "drivers/terminal.c"
#include "drivers/keyboard.c"
#include "drivers/ports.c"
#include "drivers/ata.c"
#include "memory/memory.c"
#include "misc/defs.c"

#define PANIC_ON_NO_ATA 0

const char* loadedMsg = "PDOS Loaded Successfully.\n";
const char* kernelPanicMsg = "\n\nPDOS Kernel Panic!\nHalting CPU...\n";

static u8* atabuf[512] = {0};

void panic(void) {
	kprint(kernelPanicMsg);  // signal to the user that their computer just crashed
	__asm__ volatile("cli"); // if we dont stop interrupts it might appear as if the os never halted
	__asm__ volatile("hlt"); // halt everything but interrupts
}

void main(void)
{
	clear_screen(); // get rid of junk some bios may leave on the screen
	kprint(loadedMsg);

	idt_init();
	kb_init();
	disable_cursor(); // cursor position by default is a seemingly 
	// random spot on the left side of the screen 
	// and i didnt feel like writing a moving cursor so i just hide it

	// readSect();
	if(identify() != 0) {
		kprint("No ata drive found, this might be a problem.\nIf everything still works properly feel free to ignore this message.\n\n");
		if (PANIC_ON_NO_ATA) panic();
	}

	while(1) {
		// kernel does pretty much nothing after initializing
		// because hardware interrupts handle pretty much everything.
	}
}
