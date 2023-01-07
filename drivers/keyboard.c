#pragma once

#include "terminal.c"
#include "ports.c"

unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    11,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    11,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define ENTER_KEY_CODE 0x1C


void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21, 0xFD);
}

u8 termMode = 0; // term mode of 0 means term, term mode 1 means app handles it, anything else is undefined behavior.

void keyboard_switch_app_mode() {
  termMode = 0b10000000;
}
void keyboard_switch_kernel_mode() {
  termMode = 0b00000000;
}
// void (*appCallback)(char keycode);
void (*appCallback)(char);
void setAppModeCallback( void (*fun)(char) ) {
  appCallback=fun;
}
void keyboard_handler_main(void)
{
	unsigned char status;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0) // behaves buggy without this for some reason
			return;

    if (keyboard_map[(unsigned char) keycode] == 11) { // if control or alt
      termMode = ~termMode;
      termMode &= 0b10000000; // toggle between 1 and 0
      return;
    }
    
    if (termMode == 0b10000000) { // app mode WIP

      appCallback(keycode);

      return;

    } else { // term mode

      termHandleInput(keyboard_map[(unsigned char) keycode]);

      return;
    }
	}
}