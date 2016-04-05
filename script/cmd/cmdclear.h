/*
*Copyright 2016 Deepankar Sinha
*
*/
#ifndef CMDCLEAR_H
#define CMDCLEAR_H
#include "../sys/system.h"

int clear(){
	clearScreen();
	return 1;//always success 
}
	

#endif
