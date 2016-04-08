/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "cmdlist.h"
#include "command.h"
#include "../sys/system.h"


int request(char* cmdline){
	int cmdno,chk;
	char *cmd;
	cmd=getcmd(cmdline);
	cmdno=isvalidcmd(cmd);
	
	if(cmdno){
		chk=exec(cmdno,cmdline);
		if(chk)
			return 1;//executed successfully
		else
			return -1;//execution failure
	}
	return 0;//wrong command
}
