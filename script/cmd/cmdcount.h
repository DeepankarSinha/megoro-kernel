#include "../sys/system.h"

static int counter; 

void startCount()
{
	counter=0;
	do{
		counter++;
	}while(1);
}

int showCounter(){
	kprint(itoca(counter));kpc('\n');
	return 1;
}
