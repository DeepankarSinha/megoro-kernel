/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "command.h"
#include "../sys/system.h"
#include "../lib/kstring.h"

int cpu_time()
{
	int funlen,tmp=5;
	long seci=get_CPU_time_in_seconds();
	char * secc=ltoca(seci);
	char c;
	kprint("CPU TIME since last boot: ");kps(secc);kps(" s\n");
	return 1;
}
