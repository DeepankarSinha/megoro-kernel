hlib1=$(wildcard lib/*.h)
hlib2=$(wildcard *.h)
hlib3=$(wildcard cmd/*.h)
kc.o: kernel.c $(hlib1) $(hlib2) $(hlib3) 
	sudo gcc -m32 -c kernel.c -o $(HOME)/Desktop/MerryGoRound/kc.o -ffreestanding

