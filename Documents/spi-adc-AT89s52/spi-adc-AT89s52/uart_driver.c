/*uart_driver.c*/
#include <reg51.h>
#include "header.h"
void uart_init(u16 baud)
{
	TMOD|=0x20;
	SCON=0x50;
	switch(baud)
	{
		case 9600:  TH1=253; break;
		case 28800: TH1=255; break;
		case 56700: TH1=255; PCON|=0x80; break;
		default: TH1=253;
	}
	TR1=1;
}

void uart_tx(u8 ch)
{
	SBUF=ch;
	while(TI==0);//polling condition
	TI=0;
}

void uart_tx_string(s8 *s)
{
	while(*s)
	{
		SBUF=*s;
		while(TI==0);
		TI=0;
		s++;	
	}
}








