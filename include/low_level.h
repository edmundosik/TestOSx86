#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

uint8_t inb(unsigned short port);                 // byte in
void outb(unsigned short port, unsigned char data);     // byte out
//uint8_t inw(unsigned short port);                // word in
void outw(unsigned short port, unsigned short data);   // word out

#endif