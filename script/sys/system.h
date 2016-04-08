#ifndef __SYSTEM_H
#define __SYSTEM_H

extern void terminal_initialize();
extern char* kscan();
extern char kcscan();
extern void kprint(char*);
extern void kps(char*);
extern void kpc(char);
extern void kpi(int);
extern char *itoca(int n);
extern char *ltoca(long n);
extern void terminal_putchar(char);
extern void scroll();
extern void moveCursorRight();
extern void moveCursorLeft();
extern void backspace();
extern void clearScreen();
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern void gdt_install();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,unsigned char flags);
extern void idt_install();
/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically*/ 
};
extern void isrs_install();
extern void irq_install();
extern void timer_install();
extern void sleep(int ticks);
extern long get_CPU_time_in_seconds();
#endif
