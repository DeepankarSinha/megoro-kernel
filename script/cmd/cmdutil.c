/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "cmdlist.h"
#include "command.h"
//if command exist then return the command number else return 0 
int isvalidcmd(char * cmd){
	int i=0;
	while(i<list_size){
		
		if(kstrcmp(cmd,cmd_list[i])==0)
			return i+1;
	i++;
	}
	return 0;
}

char* getcmd(char* cmdline){
	static char cmd[10];
	int i=0,f=0;
	do{
		if(*cmdline!=' ')
			f=1;
		else if(f==1)
			break;
		cmd[i++]=*cmdline++;
		if(i==9)
			break;
	}while(1);
	cmd[i]='\0';
	return cmd;
}

	
