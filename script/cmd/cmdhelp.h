/*
*Copyright 2016 Deepankar Sinha
*
*Syntax: help -cmd
*/
#ifndef CMDHELP_H
#define CMDHELP_H
#include "help.h"
#include "../sys/system.h" 
int showHelp(char *cmdline){
	char arg[200];
	int i,cmdno,flag=0;
	do{
		if(*cmdline=='-'){
			flag++;
			i=0;
			do{
				arg[i]=*++cmdline;
				i++;
				if(*cmdline == ' ' || *cmdline == '\0')
					break;
			}while(1);
			arg[i]='\0';
			
			cmdno=isvalidcmd(&arg);
			if(cmdno>0){	
				kprint(helplist[cmdno-1]);kpc('\n');
			}else{
				kprint("No help found for command ");kps(arg);kpc('\n');
			}
		}
		
	}while(*cmdline++ != '\0');
	
	if(flag==0){
		kprint(helplist[0]);kpc('\n');
	}
	
	return 1;
}
#endif
