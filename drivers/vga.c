// Screen driver
#include <drivers/vga.h>
#include <low_level.h>
#include <util.h>
//#include "../lib/types.h"

void draw_char(char character) {
  char* vidmem = (char*) VID_ADDRESS;

  *vidmem = character;
}

int get_screen_offset(int col, int row) {
	return (row * MAX_COLS + col)*2;
} 

int get_row_from_offset(int offset) {
  return offset / (2 * MAX_COLS);
}

// Get column from offset in memory
int get_col_from_offset(int offset) {
  return (offset - (get_row_from_offset(offset) * 2 * MAX_COLS)) / 2;
}

int get_cursor() {
	//reg 14 & 15
	outb(REG_SCREEN_CTRL, 14);
	int offset = inb(REG_SCREEN_DATA) << 8;
	outb(REG_SCREEN_CTRL, 15);
	offset += inb(REG_SCREEN_DATA);
	// convert charater to vga size
	return offset*2;
}

void set_cursor(int offset) {
	offset /= 2;
	outb(REG_SCREEN_CTRL, 14);
	outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	outb(REG_SCREEN_CTRL, 15);
	outb(REG_SCREEN_DATA, (unsigned char)(offset));
}

int handle_scrolling(int cursor_offset) {
	//if the cursor is within the screen
	if (cursor_offset < MAX_ROWS*MAX_COLS*2)
		return cursor_offset;
	//copy
	int i;
	for(i=0; i<MAX_ROWS; ++i){
		memcpy(get_screen_offset(0, i)+VID_ADDRESS, get_screen_offset(0, i-1)+VID_ADDRESS, MAX_COLS*2);
	}
	//blank the last line
	char* last_line = (char*)(get_screen_offset(0, MAX_ROWS-1)+VID_ADDRESS);
	for(i=0; i<MAX_COLS; ++i)
		last_line[i]=0;
	//Move offset back one row to the last line of the screen
	cursor_offset -= 2*MAX_COLS;
	return cursor_offset;
}

void print_char(char character, int col, int row, char attribute_byte) {
	unsigned char *vidmem = (unsigned char*)VID_ADDRESS;

	if(! attribute_byte) {
		 attribute_byte = (VGA_BLACK << 4) | (VGA_WHITE);
	}
	int offset;
	if(col >= 0 && row >=0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor();
	}
	// start from the new line
	if(character == '\n') {
		int row = offset / (2*MAX_COLS);
		offset = get_screen_offset(MAX_COLS-1, row);
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] =  attribute_byte;
	}
	// next char position
	offset += 2;
	offset = handle_scrolling(offset);
	//update cursor position
	set_cursor(offset);
}

void print_at(char* msg, int col, int row) {
	if(col >= 0 && row >= 0){
		set_cursor(get_screen_offset(col, row));
	}
	//FIX:wq
	int i = 0;
	while(msg[i] != '\0'){
		print_char(msg[i++], col, row, (VGA_BLACK << 4) | (VGA_WHITE));
	}
}

void print(char* msg) {
	print_at(msg, -1, -1);
}

void clear_screen () {
  int  row = 0;
  int  col = 0;
  /* Loop  through  video  memory  and  write  blank  characters. */
  for (row=0; row <MAX_ROWS; row++) {
    for (col=0; col <MAX_COLS; col++) {
      print_char(' ', col , row , (VGA_BLACK << 4) | (VGA_WHITE));
    }
  }
  // Move  the  cursor  back to the  top  left.
  set_cursor(get_screen_offset (0, 0));
}

void printDec(uint32_t dec) {
	if(dec == 0) {
		print('0');
		return;
	}

	uint32_t acc = dec;
	char c[32];
	int i = 0;
	while(acc > 0) {
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while(i >= 0) {
		c2[i--] = c[j++];
	}

	print(c2);
	
}
/*
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	port_byte_out(0x3D4, 0x0A);
	port_byte_out(0x3D5, (port_byte_in(0x3D5) & 0xC0) | cursor_start);

	port_byte_out(0x3D4, 0x0B);
	port_byte_out(0x3D5, (port_byte_in(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor() {
	port_byte_out(0x3D4, 0x0A);
	port_byte_out(0x3D5, 0x20);
}*/
