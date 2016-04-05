hlib1=$(wildcard lib/*.h)
hlib2=$(wildcard *.h)
hlib3=$(wildcard cmd/*.h)
all:
	cd sys; make
	make kc.o

kc.o: kernel.c prompt.c $(hlib1) $(hlib2) $(hlib3) 
	sudo gcc -m32 -c kernel.c -o ../kc.o -ffreestanding
	gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c prompt.c -o ../prompt.o -fno-exceptions -ffreestanding


