#pragma once

#include <stdint.h>

#define outb write_port
#define inb read_port
#define outw write_port_word

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void write_port_word(unsigned short port, unsigned short data);

extern void insw(uint16_t port, void *addr, unsigned int count);
extern void outsw(uint16_t port, void *addr, unsigned int count);