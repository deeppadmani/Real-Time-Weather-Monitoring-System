#include "header.h"
#include <stdio.h>
main()
{
	u16 temp;
	u8 buf[10];
	uart_init(9600);
	uart_tx_string("MCP3204 12BIT ADC DEMO\r\n");
	while(1)
	{
		temp=read_adc();
		sprintf(buf,"%d\r\n",temp);//convert integer to string
		uart_tx_string(buf);
		delay_ms(500);
	}
}