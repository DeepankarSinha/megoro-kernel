/*
*Copyright 2016 Deepankar Sinha
*
*/

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include "sys/system.h"
#include "terminal.h"
#include "multiboot.h"
extern void enter_pmode();
void kernel_main(multiboot_info_t* mbd,unsigned int magic) {
	/* Initialization */
	terminal_initialize();
	kprint("Kernel Loading...\nInitializing GDT......");
 	gdt_install();
	kprint("DONE\nInitializing IDT......");
	idt_install();
	kprint("DONE\n");
	
	enter_pmode();	
	
}
