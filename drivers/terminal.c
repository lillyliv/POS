#pragma once
#include <stdint.h>
#include "../misc/defs.c"
#include "../misc/strings.c"
/* there are 25 lines each of 80 columns; each element takes 2 bytes */
#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

char termInputBuf[255] = { 0 };
u8 termInputBufPos = 0;

// https://wiki.osdev.org/Text_Mode_Cursor

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * COLUMNS_IN_LINE + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void prntnum(unsigned long num, int base, char sign, char *outbuf)
{

    int i = 12;
    int j = 0;

    do{
        outbuf[i] = "0123456789ABCDEF"[num % base];
        i--;
        num = num/base;
    }while( num > 0);

    if(sign != ' '){
        outbuf[0] = sign;
        ++j;
    }

    while( ++i < 13){
       outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;

}

/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char*)0xb8000;

void kprint_newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {

        if (str[i] == '\n') {
            kprint_newline();
            i++;
        } else {
            vidptr[current_loc++] = str[i++];
            vidptr[current_loc++] = 0x07;
        }
	}
}

void kprint_backspace(void) {
    current_loc-=2;
    kprint(" ");
    current_loc-=2;
}

void clear_screen()
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
    current_loc = 0;
}

void kprint_formatted(const char* string) { // wip doesnt work rn to print formatted strings

}

void termRunProgram(char* programName) {
    if(strcmp(programName, "install")) {
        installQuestion();
    }
    exit_program();
}

void termHandleInput(char key) {
    if (key == 0) return;
    if (key == '\n') {
        clear_screen();
        termRunProgram(termInputBuf);
        for(u8 i = 0; i < termInputBufPos; i++) {
            termInputBuf[i] = 0;
        }
        termInputBufPos = 0;
        return;
    } else if (key == '\b') {
        if (!termInputBufPos) return; // do nothing if trying to backspace empty command
        kprint_backspace();
        termInputBufPos--;
        return;
    } else {
        if (termInputBufPos >= 255) return; // do nothing if buffer is full
        termInputBuf[termInputBufPos] = key;
        termInputBufPos++;
        vidptr[current_loc++] = key;
        vidptr[current_loc++] = 0x07;
    }
}

void exit_program(void) {
    keyboard_switch_kernel_mode();
    clear_screen();
    kprint("$");
}