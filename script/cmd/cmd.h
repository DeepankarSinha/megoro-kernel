#include "cmdlist.h"
#include "cmdexec.h"
#include "../lib/kstring.h"
#include "../lib/io.h"
#include "../lib/integer.h"

int isvalidcmd(char *);
int request(char* cmd){
	int cmdno,chk;
	cmdno=isvalidcmd(cmd);
	
	if(cmdno){
		chk=exec(cmdno,cmd);
		if(chk)
			return 1;//executed successfully
		else
			return -1;//execution failure
	}
	return 0;//wrong command
}

//if command exist then return the command number else return 0 
int isvalidcmd(char * cmd){
	int i=0;
	while(i<listsize){
		
		if(kstrcmp(cmd,cmdlist[i])==0)
			return i+1;
	i++;
	}
	return 0;
}
