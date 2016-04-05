/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "cmdclear.h"
#include "cmdhelp.h"
#include "cmdcount.h"
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
		
	}
	return ret;
}
