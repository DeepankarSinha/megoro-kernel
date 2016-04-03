#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "lib/io.h"
#include "lib/kstring.h"
#include "prompt.h"
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	int i=0,x;
	char c;
	char* str;
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Since there is no support for newlines in terminal_putchar
         * yet, '\n' will produce some VGA specific character instead.
         * This is normal.
         */
	kprint("Project Merry Go Round\n");
	kprint("Kernel level. #DevelopingKernel\n");
	kprint("Version 0.0.0.1\n");
	promptmode();
}
