cfile=$(wildcard *.c)
hfile=$(wildcard *.h)
progs=$(patsubst %.c,%,$(cfile))
all: $(progs)
%:%.c $(hfile)
	sudo gcc -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -c $< -o ../../$@.o -fno-exceptions -ffreestanding
