//#include "../lib/types.h"
#ifndef VGA_H
#define VGA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VID_ADDRESS 0xb8000

#define MAX_COLS 25
#define MAX_ROWS 80

// VGA color codes 
// color = (COLOR << 4 ) | (COLOR)
#define VGA_BLACK               0x0  
#define VGA_BLUE                0x1
#define VGA_GREEN               0x2
#define VGA_CYAN                0x3
#define VGA_RED                 0x4
#define VGA_MAGNETA             0x5
#define VGA_BROWN               0x6
#define VGA_LIGHT_GREY          0x7
#define VGA_DARK_GREY           0x8
#define VGA_LIGHT_BLUE          0x9
#define VGA_LIGHT_GREEN         0x0A
#define VGA_LIGHT_CYAN          0x0B
#define VGA_LIGHT_RED           0x0C
#define VGA_LIGHT_MAGNETA       0x0D
#define VGA_LIGHT_BROWN         0x0E
#define VGA_WHITE               0x0F

// I/O device ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void draw_char(char character);
int get_screen_offset(int col, int row);
int get_row_from_offset(int offset);
int get_col_from_offset(int offset);
int get_cursor();
void set_cursor(int offset);
int handle_scrolling(int cursor_offset);
void print_char(char character, int col, int row, char  attribute_byte);
void print_at(char* msg, int col, int row);
void print(char* msg);
void clear_screen();
void printDec(uint32_t dec);
//void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
//void disable_cursor();
#endif // VGA_H
