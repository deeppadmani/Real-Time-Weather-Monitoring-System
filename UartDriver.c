

#include"header.h"

void uart_init(u16 baud)
{
	TMOD |=0x20;
	SCON |=0x50;
	switch(baud)
	{
		case 7200:TH1=252;break;
		case 9600:TH1=253;break;    //TH1=(256-(2^smod) *XTAL)/(12*36*BaudRate)   //smod=1 for double the baudrate
		case 28800:TH1=255;	break;
		case 57600:TH1=255;PCON|=0x80;break;	//enable smod
	   	default:TH1=253;
	}
	TR1=1; //start timer1 
}

void uart_tx(u8 byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
}

/*u8 uart_rx()
{	
	while(RI==0);
	RI=0;
	return SBUF;
}	  */

void uart_string(s8 *ptr)
{
	int i;
	for(i=0;ptr[i];i++)
	{	
		SBUF=ptr[i];
		while(TI==0);
		TI=0;
	}
}

/*void uart_rx_string(s8 *buf,u8 MaxSize)
{
	u8 i;
	for(i=0;i<MaxSize;i++)
	{
		buf[i]=uart_rx();
		if(buf[i]=='\r')
			break;
	}
	buf[i]=0;
} */

void uart_int(s16 temp)
{
	u16 i,sum=0,c=0;
	if(temp==0)
		uart_tx('0');
	if(temp<0)
	{
		uart_tx('-');
		i=-temp;
	}
	else
		i=temp;
	for(c=0;i;i=i/10)
	{
		 sum=sum*10+i%10;
		 c++;
	}
	for(i=sum;i;i=i/10)
	{
		 uart_tx((i%10)+48);
		 c--;
	}
	while(c)
	{
		  uart_tx('0');
		  c--;
	}
}

void uart_float(s32_f n)
{
	int n1;
	float n2;
	n1=n;
	n2=n-n1;
	n2=n2*100;
	if(n2<0)
		n2=-n2;
	
	uart_int(n1);
	uart_tx('.');
	if(n2<10)
		uart_tx('0');
	uart_int(n2);
}

/*void uart_hex(s16 number)
{
   	  u8 hex[10],c;
	  s8 i;
	  uart_string("0x");
	  c=0;
	  while(number>0)
      {
        switch(number%16)
        {
           case 10:
                hex[c]='A'; break;
            case 11:
                hex[c]='B'; break;
            case 12:
                hex[c]='C'; break;
            case 13:
                hex[c]='D'; break;
            case 14:
                hex[c]='E'; break;
            case 15:
                hex[c]='F'; break;
            default:
                hex[c]=(number%16)+0x30;
        }
        number=number/16;
		c++;
   	 }
	 hex[c]='\0';
	 for(i=c-1;i>=0;i--)
	 {
	 	uart_tx(hex[i]);
	}
}	  */