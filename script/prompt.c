/*
*Copyright 2016 Deepankar Sinha
*
*/
#include "sys/system.h"
#include "cmd/cmd.h"
#include "lib/kstring.h"
#include "terminal.h"

char *cscan();
void promptmode(){
	char *s;
	int ret;
	do{
		kprint("MEGORO:)");
		s=cscan();
		ret=request(s);
		if(ret){
			//TO-DO
			if(ret<0){
				//TO-DO
			}
		}else{
			kprint("MEGORO:( COULD NOT RECOGNISE THAT COMMAND!\n");
		}
		
	}while(1);
}

//This is the function where all the cursor related magic happens.
char *cscan(){
	int len=0,i=0,max=1024*1024;
	char c;
	static unsigned char buffer[1024*1024];
	kpc('_');
	do{
		
		c=kcscan();
		if(c=='\n'){
			kpc('\b');
			kpc(c);
			break;
		}
		else if(c=='\b'){
			if(len>0){
				len--;
				i--;
				//kps(itoca(len));
				kpc('\b');kpc('\b');kpc('_');
			}
		}else{
			len++;
			kpc('\b');kpc(c);
			kpc('_');
			if(i<max)
				buffer[i++]=c;
			else
				break;
		}
		
		
	}while(1);
	buffer[i]='\0';
	return buffer;
}	
		
	
