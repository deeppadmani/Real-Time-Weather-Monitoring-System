/*DelayDriver.c*/

#include"header.h"

void delay_ms(u16 ms)    	
{
    int i,j;
     for(i=0;i<ms;i++)
     	for(j=0;j<112;j++);
}
