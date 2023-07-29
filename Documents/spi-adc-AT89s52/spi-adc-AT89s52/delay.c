/*delay.c*/
#include "header.h"

void delay_ms(u16 ms)
{
	u16 i;
	for(;ms>0;ms--)
	for(i=122;i>0;i--);
}