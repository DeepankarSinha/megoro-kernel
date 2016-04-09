/*
Copyright (C) 2015 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef MEMORY_H
#define MEMORY_H

typedef int   int32_t;
typedef short int16_t;
typedef char  int8_t;

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

//typedef uint8_t bool;

unsigned long total_memory;
extern void	memory_init();
extern void *	memory_alloc_page( uint8_t zeroit );
extern void	memory_free_page( void *addr );

#define PAGE_SIZE 4096
#define PAGE_BITS 12
#define PAGE_MASK 0xfffff000

#define KILO 1024
#define MEGA (KILO*KILO)
#define GIGA (KILO*KILO*KILO)



static inline uint16_t ntoh16( uint16_t x )
{
	return (x&0xff)<<8 | (x>>8);
}

static inline uint16_t hton16( uint16_t x )
{
	return (x&0xff)<<8 | (x>>8);
}

#endif
