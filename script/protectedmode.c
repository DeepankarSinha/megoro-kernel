/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "sys/system.h"
#include "sys/rtc.h"
#include "terminal.h"

#include "mem/alloc.h"
#include "stddef.h"

void pmode(){
	kprint("Entered Protected Mode\nInitializing ISRS......");
	isrs_install();
	kprint("DONE\nInitializing IRQ......");
	irq_install();
	__asm__ __volatile__ ("sti");
	kprint("DONE\nInitializing Timer......");
	timer_install();
	kprint("DONE\nInitializing RTC......");
	rtc_install();
	kprint("DONE\n");
	promptmode();
	while(1);
}
