
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
#include "drivers/fdc.c"
#include "drivers/net/ne2000.c"
#include "memory/memory.c"
#include "misc/defs.c"
#include "misc/panic.c"

#define PANIC_ON_NO_ATA 0
#define ATA_ENABLED 1
#define INSTALL_IF_POS_NOT_DETECTED 1

const char* loadedMsg = "POS Loaded Successfully.\n";

static u8* atabuf[512] = {0};

void install(void) {

}
void installQuestion(void) { // wip
	kprint("POS not detected :(\nWould you like to install it?\nY/N\n");
}
void installer_keyboard_callback(char keycode) { // wip
	char key = keyboard_map[(unsigned char) keycode];
	if (key == 'y') { // install
		install();
	} else if (key == 'n') { // no install
		kprint("\n$");
		keyboard_switch_kernel_mode();
	}
	return;
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

	setAppModeCallback(&installer_keyboard_callback);
	keyboard_switch_app_mode();

	// readSect();
	if (ATA_ENABLED) {

		// try to identify ata drive, doesnt work for me however every other ata function does??
		if(identify() != 0) {
			kprint("No ata drive found, this might be a problem.\nIf everything still works properly feel free to ignore this message.\n\n");
			if (PANIC_ON_NO_ATA) panic();
		}

		if (INSTALL_IF_POS_NOT_DETECTED) {

			ata_pio_read28(1, 1, sectBuffer); // using 24 bit for some backwards compatability,
							// i think this may be slower but i am only reading one sector

			if(sectBuffer[0] != "P" || sectBuffer != "S") { // os may be not installed or corrupted
				installQuestion();
			}
		}

	}


	while(1) {
		// kernel does pretty much nothing after initializing
		// because hardware interrupts handle pretty much everything.
	}
}
