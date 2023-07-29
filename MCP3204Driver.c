#include"header.h"
/*--FOR MCP3204 ADC--*/
sbit clk=P1^0;
sbit din=P1^1;
sbit dout=P1^2;
sbit cs=P1^3;

u16 Adc_Read(u8 channel)
{
	u16 temp=0x00;
	s8 i,d0,d1;
	if(channel==0)
	{
		d0=0;d1=0;
	}
	else if(channel==1)
	{
		 d0=1;d1=0;
	}
	else if(channel==2)
	{
		 d0=0;d1=1;
	}
	else if(channel==3)
	{
		 d0=1;d1=1;
	}
	cs=0;  					//adc start communication
	clk=0;din=1;clk=1;		//start bit
	clk=0;din=1;clk=1;		//single enabled

	clk=0;din=1;clk=1;			//d2 don,t care	  for that refer datasheet of MCP3204 
	clk=0;din=d1;clk=1;			//d1    (CH0)
	clk=0;din=d0;clk=1;			//d0	 (CH0)

	clk=0;din=1;clk=1;		//stop sampling 
	clk=0;din=1;clk=1;		 // null bit

	for(i=11;i>=0;i--)
	{
		clk=0;
		if(dout==1)
			temp |=(1<<i);
		clk=1;
	}
	cs=1;		//ADC stop
	return temp;

}

	