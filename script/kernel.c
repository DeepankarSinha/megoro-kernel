/*
*Copyright 2016 Deepankar Sinha
*
*/

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include "sys/system.h"
#include "terminal.h"
void kernel_main() {
	/* Initialization */
	terminal_initialize();
	kprint("Kernel Loading...\nInitializing GDT......");
 	gdt_install();
	kprint("DONE\nInitializing IDT......");
	idt_install();
	kprint("DONE\nkInitializing ISRS......");
	isrs_install();
	kprint("DONE\nkInitializing IRQ......");
	irq_install();
	__asm__ __volatile__ ("sti");
	kprint("DONE\nInitializing Timer......");
	void timer_install();
	kprint("DONE\nInitializing Done......Kernel Ready\n\nMEGORO Terminal alpha ver--\n");
	promptmode();
	while(1);
	
}
