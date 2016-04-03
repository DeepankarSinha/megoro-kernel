#ifndef IO_H
#define IO_H
#include "llio.h"
#include "integer.h"

//function defined
char* kscan();
char kcscan();
void kprint(char*);
void kps(char*);
void kpc(char);
void kpi(int);

//read input from keyboard and return string when user press enter
char* kscan(){
	int i=0;
	const int max_limit=1024*1024;
	char c;
	static unsigned char buffer[1024*1024];
	
	do{
		c=getcode();
		if(c=='\b'){
			backspace();
			i=i>0?(i-1):0;
		}else if(c=='\n'){
			nextline();
			break;
		}else{
			terminal_putchar(c);
			if(i<max_limit)
				buffer[i++]=c;
			else
				break;
		}		
	}while(1);
	buffer[i]='\0';
	return buffer;
}

char kcscan(){
	return getcode();
}

//Prints string to the console
void kprint(char *str){
	terminal_writestring(str);
}

//Same as kprint but smaller in length for easy appending
void kps(char *str){
	kprint(str);
}

//Prints a single charachter
void kpc(char c){
	terminal_putchar(c);
}

//Prints integer
void kpi(int n){
	char *p=itoca(n);
	terminal_writestring(p);
}
#endif
