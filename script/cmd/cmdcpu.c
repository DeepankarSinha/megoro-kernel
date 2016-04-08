/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "../cpu/cpuid.h"
#include "command.h"

int showCPUinfo(){
	detect_cpu();
	return 1;
}
