/*
*Copyright 2016 Deepankar Sinha
*
*/

#ifndef INTEGER_H
#define INTEGER_H
#include "system.h"
char *itoca(int n){
	int s,d,t,len;
	char dig[]="0123456789";
	static char p[30];
	t=n;
	len=0;
	if(n==0)
		return "0";
	while(t!=0){
		t=t/10;
		len++;
	}
	t=n;
	p[len]='\0';
	while(t!=0){
		d=t%10;
		p[--len]=dig[d];
		t=t/10;
	}
	//printf("\n%s \nend\n",q);
	return p;
}
#endif
