#include <reg51.h>
#include "header.h"
sbit clk =P1^0;
sbit din =P1^1;
sbit dout=P1^2;
sbit cs  =P1^3;
u16 read_adc()
{
		u16 temp=0x0;
		s8 i;
		cs=0; // chip/adc selected for commu
		clk=0;	din=1;	clk=1;//write start  bit
		clk=0;	din=1;	clk=1;//write single ended mode bit
		clk=0;	din=1;	clk=1;//write D2 bit
		clk=0;	din=0;	clk=1;//write D1 bit
		clk=0;	din=0;	clk=1;//write D0 bit
		clk=0;	din=1;	clk=1;//adc will start sampling
		clk=0;	din=1;	clk=1;//for null bit
		for(i=11;i>=0;i--)//reading 12bit digital data from ADC
		{
			clk=0;
				if(dout==1)
					temp|=(1<<i);
			clk=1;
		}
		cs=1;//stop adc commu
		return temp;
}