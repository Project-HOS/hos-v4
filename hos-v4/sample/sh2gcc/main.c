#include <stdio.h>
#include "kernel.h"

#define PDIORL	((volatile unsigned short *)0xffff83a6)
#define PDDRL	((volatile unsigned short *)0xffff83a2)


void boot()
{
	*PDIORL = 0xffff;
}

void __main()
{
}

void exit()
{
}


int main()
{
	unsigned long a = 0;
	
	sta_hos();
	
	for ( ; ; )
	{
		a++;
		*PDDRL = ~(a / 256);
	}
	
	return 0;
}

