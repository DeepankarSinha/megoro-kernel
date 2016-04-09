#ifndef MALLOC_H
#define MALLOC_H
#include "memory.h"
#include <stddef.h>
char memory[20000];
struct block{
	size_t size;
	int free;
	struct block *next;
};

struct block *freeList=(void*) memory;
#endif

