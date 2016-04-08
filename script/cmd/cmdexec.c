/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "command.h"

int exec(int cmdno,char * cmdline){
	int ret;
	switch(cmdno){
		case 1: ret=showHelp(cmdline);
			break;
		case 2:
			ret=clear();
			break;
		case 3:
			break;
		case 4: 
			ret=showCPUinfo();
			break; 
		case 5:
			ret=cpu_time();
			break;
		
	}
	return ret;
}
