
gdt.o: gdt.c utility.c io.c llio.c integer.c system.h
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c integer.c -o ../../integer.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c io.c -o ../../io.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c llio.c -o ../../llio.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c utility.c -o ../../utility.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c gdt.c -o ../../gdt.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c idt.c -o ../../idt.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c isrs.c -o ../../isrs.o -fno-exceptions -ffreestanding
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c irq.c -o ../../irq.o -fno-exceptions -ffreestanding
