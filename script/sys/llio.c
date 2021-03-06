/*
*Copyright 2016 Deepankar Sinha
*
*/
#ifndef LLIO_H
#define LLIO_H
#include "keyboard_map.h"
#include "system.h"
#include <stddef.h>
#include <stdint.h>
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C

char* kscan();
void terminal_putchar(char);
void scroll();
void moveCursorRight();
void moveCursorLeft();
void backspace();
void clearScreen();
/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

 
void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	size_t y=0;
	size_t x=0;
	while(y<VGA_HEIGHT){
		x=0;
		while(x<VGA_WIDTH){
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			x++;
		}
		y++;
	}
	/*for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}*/
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void nextline(){
	if (++terminal_row >= VGA_HEIGHT) {
		terminal_row = VGA_HEIGHT-1;
		scroll();
	}
	terminal_column=0;
}

void scroll(){
	size_t y=0;
	size_t x=0;
	int i=0;
	while(y<VGA_HEIGHT-1){
		x=0;
		while(x<VGA_WIDTH){
			const size_t index1 = y * VGA_WIDTH + x;
			const size_t index2 = (y+1) * VGA_WIDTH + x;
			terminal_buffer[index1] = terminal_buffer[index2];
			terminal_buffer[index2] = make_vgaentry(' ', terminal_color);
			x++;
		}
		y++;
	}
	/*terminal_column=0;
	while(i++<VGA_WIDTH)
		terminal_putchar(' ');
	terminal_column=0;*/
}
 
void terminal_putchar(char c) {
	if(c=='\n')
		nextline();
	else if(c == '\b')
		backspace();
	else{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column >= VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row >= VGA_HEIGHT) {
				terminal_row = VGA_HEIGHT-1;
				scroll();
			}
		}
	}
}
 
void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	size_t i=0;
	while(i<datalen){
		terminal_putchar(data[i]);
		i++;
	}
	/*for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);*/
}

void moveCursorLeft(){
	if(terminal_column>0)
		terminal_column--;
}

void moveCursorRight(){
	if(terminal_column<VGA_WIDTH-1)
		terminal_column++;
}

void backspace(){
	moveCursorLeft();
	terminal_putchar(' ');
	moveCursorLeft();
}

void clearScreen(){
	size_t y=0;
	size_t x=0;
	while(y<VGA_HEIGHT){
		x=0;
		while(x<VGA_WIDTH){
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			x++;
		}
		y++;
	}
	terminal_column=0;
	terminal_row=0;
}

//IO functions


char getScancode(){
	char c=0;
	unsigned char status;
	
	while(1){
		status = inportb(KEYBOARD_STATUS_PORT);
		if (status & 0x01) {
			c = inportb(KEYBOARD_DATA_PORT);
			if(c >= 0)
				return;
	
			if(c == ENTER_KEY_CODE) {
				nextline();
				return;
			}
				
		}	
	}
}
char getcode(){
	int code=getScancode();
	return keyboard_map[(unsigned char)code];
}
#endif
