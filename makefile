all:
	make boot.o
	cd script; make
	make megoro.bin
	make iso

boot.o:boot.asm
	nasm -f elf32 boot.asm -o boot.o

megoro.bin: linker.ld
	ld -m elf_i386 -t linker.ld -o build/boot/megoro.bin boot.o kc.o

iso:
	sudo grub-mkrescue -o megoro.iso build
