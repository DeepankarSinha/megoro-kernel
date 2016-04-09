#include <stddef.h>
#include "../sys/system.h"
#include "malloc.h"
#include "alloc.h"
#include "memory.h"
#ifndef NULL
#define NULL 0
#endif
void initialize(){
	freeList->size=total_memory-sizeof(struct block);
	freeList->free=1;
	freeList->next=NULL;
}

void split(struct block *fitting_slot, size_t size){
	struct block *new=(void*)((void*)fitting_slot+size+sizeof(struct block));
	new->size=(fitting_slot->size)-size-sizeof(struct block);
	new->free=1;
	new->next=fitting_slot->next;
	fitting_slot->size=size;
	fitting_slot->free=0;
	fitting_slot->next=new;
}
void *malloc(size_t noOfBytes){
	struct block *curr,*prev;
	int timeout=2;
	void *result;
	if(!(freeList->size)){
		initialize();
		kprint("\nMALLOC DEBUG: Memory Initialize");
	}
	curr=freeList;
	
	kprint("\nMALLOC DEBUG: curr->size: ");kpi(curr->size);	
	
	if(noOfBytes==0)
	{
		kprint("\nMALLOC DEBUG: 0 byte requested. Returning NULL.");
		return NULL;
	}
	
	do{
	
	while( (((curr->size)<noOfBytes)||((curr->free)==0)) && (curr->next!=NULL)){
		prev=curr;
		curr=curr->next;
		kprint("\nMALLOC DEBUG: One Block Checked");
	}
	
	if((curr->size)==noOfBytes){
		curr->free=0;
		result=(void*)(++curr);
		kprint("\nMALLOC DEBUG: Exact Fitting Block Allocated");
		return result;
	}
	else if((curr->size)>(noOfBytes+sizeof(struct block))){
		split(curr,noOfBytes);
		result=(void*)(++curr);
		kprint("\nMALLOC DEBUG: Fitting Block Allocated using Split");
		return result;
	}
	else{
		timeout--;
		kprint("\nMALLOC DEBUG: No Memory Found. Starting Merge.");
		merge();
		
	}

	}while(timeout>0);
	
	result=NULL;
	kprint("\nMALLOC DEBUG: OUT OF MEMORY");
	return result;
}

void merge(){
	struct block *curr, *prev;
	curr=freeList;
	while((curr->next)!=NULL){
		if((curr->free)&&(curr->next->free)){
			curr->size+=(curr->next->size)+sizeof(struct block);
			curr->next=curr->next->next;
		}
		prev=curr;
		curr=curr->next;
	}
}

void free(void* ptr){
	if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+total_memory))){
		struct block *curr=ptr;
		--curr;
		curr->free=1;
		merge();
	}
	else kprint("\nMALLOC DEBUG: Not In Valid Range");
} 
	

