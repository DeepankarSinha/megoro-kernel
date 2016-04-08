/*
*Copyright 2016 Deepankar Sinha
*
*/
#ifndef KSTRING_H
#define KSTRING_H
#include <stddef.h>
char* kstrcpy(char*,const char*);
int kstrlen(const char*);
char *kstrcat(char*,const char*);
char *kstrchr(const char*,int);
char *kstrsub(char*,int,int);
int kindexof(char *,char);

int kstrcmp(const char* str1,const char* str2){
	int s1;
	int s2;
	do{
		s1=*str1++;
		s2=*str2++;
		if(s1==0)
			break;
	}while(s1==s2);
	return(s1<s2)?-1:(s1>s2);
}

char* kstrcpy(char* s1,const char* s2){
	char *dst=s1;
	const char *src=s2;
	while((*dst++=*src++)!='\0');
	return s1;
}

int kstrlen(const char* s){
	const char *p = s;
	while(*p!='\0')
		p++;
	return (int)(p-s);
}

char *kstrcat(char *s1,const char *s2){
	char *s=s1;
	while(*s!='\0')
		s++;
	kstrcpy(s,s2);
	return s1;
}

char *kstrchr(const char *s,int c){
	while(*s !='\0' && *s != (char)c)
		s++;
	return ((*s == (char)c)?(char *)s:NULL);
}

char *kstrsub(char * s,int i,int len){
	static char p[1024*1024];
	int k=0;
	s+=i;

	if( len<0 || i<0 )
		return s;

	do{
		p[k++]=*s;
		s++;
	}while(k<len);
	p[k]='\0';
	return p;
}

int kindexof(char * s,char c){
	int i=0;
	while(++i<kstrlen(s))
		if(*s++==c)
			return i;
	return -1;
}
#endif
